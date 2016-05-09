#include "../protocol/protocol.h"
#include "../protocol/application.h"
#include "../protocol/common.h"
#include "../protocol/network.h"
#include "../plugin_system/list.h"

#include <stdio.h>
#include <unistd.h>

#include <getopt.h>



#define   TRANS_APPID            "TRANS###"
#define   TRANS_CONTENT_MAX      463
#define   TRANS_NUM_MESS(size)   \
  (size / TRANS_CONTENT_MAX + (size % TRANS_CONTENT_MAX == 0 ? 0 : 1))


typedef struct transfert_data {
  char *filename;
  FILE *f;
  long nummess;
  long nextnum;
} transfert_data;


typedef struct request_data {
  int nrequest;
} request_data;


static int request_file(const char *filename);
static int action_sen(char *message, char *content, int lookup_flag);
static int action_rok(char *message, char *content, int lookup_flag);
static int action_req(char *message, char *content, int lookup_flag);
static int begin_transfert(FILE *f, const char *filename, const char *size_filename,
    const char *id_trans);
static void free_transfert_data(transfert_data *t);
static void usage(char *argv0);
static void help(char *argv0);


static list requested;
static list transfert;



void init_trans_app() {
  requested = new_list();
  transfert = new_list(); 
}




#define   OPT_HELP    'h'
#define   OPTL_HELP   "help"

#define   OPT_STRING  "h"

static struct option longopts[] = {
  {OPTL_HELP,   no_argument,         0,   OPT_HELP},
  {0,           0,                   0,   0}
};



int cmd_trans(int argc, char **argv)
{
  if (argc == 1) {
    usage(argv[0]);
    return 0;
  }
  int c, indexptr;
  optind = 0;
  while ((c = getopt_long(argc, argv, OPT_STRING,
          longopts, &indexptr)) != -1) {
    switch (c) {
      case OPT_HELP:
        help(argv[0]);
        return 0;
      default:
        usage(argv[0]);
        return 1;
    }
  }
  for (int i = 1; i < argc; ++i) {
    request_file(argv[i]);
  }
  return 0;
}



int action_trans(char *message, char *content, int lookup_flag)
{
  if (strncmp(content, "REQ ", 4) == 0)
    return action_req(message, content + 4, lookup_flag);
  else if (strncmp(content, "ROK ", 4) == 0)
    return action_rok(message, content + 4, lookup_flag);
  else if (strncmp(content, "SEN ", 4) == 0)
    return action_sen(message, content + 4, lookup_flag);
  else {
    debug("action_trans", "Message trans not following the protocol: %s", content);
    return 1;
  }
}



static int request_file(const char *filename)
{
  request_data *r = malloc(sizeof(request_data));
  r->nrequest = *ring_number+1;
  if (!insert_one(requested, filename, r)) {
    fprintf(stderr, "File %s already requested.\n", filename);
    return 0;
  }
  char fname_size[3];
  itoa(fname_size, 3, strlen(filename));
  sendappmessage_all(TRANS_APPID, "REQ %s %s", fname_size, filename);
  return 1;
}



static int action_req(char *message, char *content, int lookup_flag)
{
  if (content[2] != ' ' || !isnumericn(content, 2)) {
    debug("action_req", "request not valid: %s", content);
    return 1;
  }
  unsigned short size = atoi(content);
  if (lookup_flag) {  // file already requested
    request_data *r;
#ifdef DEBUG
    if (!
#endif
    findn((void**)&r, requested, content, size)
#ifdef DEBUG
    ) {
      debug("action_req", "req message already seen but not found in the requested list:\n%s",
          content);
      return 1;
    }
#endif
    ;
    if (--r->nrequest == 0) {
      char *filename = strndup(content+3, size);
      rm(requested, filename);
      verbose(RED "File %s not found on any rings. Transfer aborted.\n", filename);
      free(filename);
      return 0;
    }
  }
  else {
    char *filename = malloc(size);
    strncpy(filename, content + 3, size);
    filename[size] = 0;
    FILE *f = fopen(filename, "r");
    if (f) {  // File accessible
      char id_trans[9];
      strncpy(id_trans, message+5, 8);
      char filename_size[3];
      strncpy(filename_size, content, 2);
      begin_transfert(f, filename, filename_size, id_trans);
    }
    else {
      sendpacket_all(message);
    }

    free(filename);
    return 0;
  }
}



static int action_rok(char *message, char *content, int lookup_flag)
{
  char *id_trans = content, *filename_size = content + 9, *filename = content + 12;
  if (id_trans[8] != ' ' || filename_size[2] != ' ' || !isnumericn(filename_size, 2)) {
    debug("action_rok", "request confirmaion not valid: %s", content);
    return 1;
  }
  unsigned short fname_size = atoi(filename_size);
  char *nummess = filename + fname_size + 1;
  if (filename[fname_size] != ' ' || !isnumericn(nummess, 8)) {
    debug("action_rok", "request confirmation not valid: %s", content);
    return 1;
  }
  
  int r = 0;
  // look for an eventual request...
  if (rmn(requested, filename, fname_size)) {  // request found and deleted from requested
    // add transfert structure
    char *fname = strndup(filename, fname_size);
    // OVERWRITE EXISTING FILE
    FILE *f = fopen(fname, "w+"); 
    if (f) {
      transfert_data *t = malloc(sizeof(transfert_data));
      t->f = f;
      t->filename = fname;
      t->nummess  = letol(nummess);
      t->nextnum  = 0;
      char *idt = strndup(id_trans, 8);
      insert_noalloc(transfert, idt, t);
    }
    else {
      fprintf(stderr, "An error occurs while creating file %s, transfert aborted.\n", fname);
      r = 1;
      free(fname);
    }
    return r;
  }
  return 0;
}



static int action_sen(char *message, char *content, int lookup_flag)
{
  char *id_trans = content, *nomess = id_trans + 9, *size_content = nomess + 9,
       *fcontent = size_content + 4;
  if ( id_trans[8] != ' ' || nomess[8] != ' ' || size_content[3] != ' ' ||
      !isnumericn(nomess, 8) || !isnumericn(size_content, 3)) {
    debug("action_sen", "sen content not following the protocol: %s", content);
    return 1;
  }
  transfert_data *t;
  // search for an existing transfert...
  if (findn((void **)&t, transfert, id_trans, 8)) {
    long n = letol(nomess);
    if (n == t->nextnum) {
      int size = atoi(size_content);
      fwrite(fcontent, size, 1, t->f);
      if (++t->nextnum == t->nummess) {
        free_transfert_data(t);
        rmn(transfert, id_trans, 8);
        verbose("File %s downloaded.\n");
      }
    }
    else {
      free_transfert_data(t);
      rmn(transfert, id_trans, 8);
      verbose(RED "Transfert of %s aborted because a packet is missing.\n" RESET);
      return 1;
    }
  } 
  else {
    sendpacket_all(message);
  }
  return 0;
}


static int begin_transfert(FILE *f, const char *filename, const char *size_filename,
    const char *id_trans)
{
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  long nummess = TRANS_NUM_MESS(size);
  char nummess_str[9];
  ltole(nummess_str, nummess, 8);
  sendappmessage_all(TRANS_APPID, "ROK %s %s %s %s", id_trans, size_filename,
      filename, nummess_str);

  // beginning transfert
  fseek(f, 0, SEEK_SET);
  for (long i = 0; i < nummess; ++i) {
    char buff[464];
    int r = fread(buff, 464, 1, f);
    if (r > 0) {
      char no[9];
      ltole(no, i, 8);
      char sc[4];
      itoa(sc, 3, r);
      sendappmessage_all(TRANS_APPID, "SEN %s %s %s %s", id_trans, no, sc, buff); 
    }
    else {
      debug("begin_transfert", "fread error, ret: %d", r);
      return -1;
    }
  }
  return 0;
}


static void free_transfert_data(transfert_data *t) 
{
  free(t->filename);
  fclose(t->f);
  free(t);
}




static void usage(char *argv0)
{
  printf("Usage:\t%s [-h] <filename1> <filename2> ...\n", argv0);
}



static void help(char *argv0)
{
  usage(argv0);
}