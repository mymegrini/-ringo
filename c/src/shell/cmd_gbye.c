#include "cmd_gbye.h"
#include "../protocol/protocol.h"
#include "../protocol/message.h"
#include "../common.h"
#include "../protocol/network.h"
#include "../protocol/thread.h"

#include <readline/readline.h>
#include <getopt.h>

static struct goodbye_data 
{
  int wait;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} _data = { .wait = 0 };


static pthread_t wait_gbye_t[NRING];
static int waiting = 0;


static struct goodbye_data *gbye_data = &_data;



int action_gbye(char *message, char *content, int lookup_flag)
{
  debug("action_gbye", RED "entering function... lookup:%d", lookup_flag);
  // message already seen
  if (lookup_flag)
    return 0;
  // don't retransmit message
  if (content[15] != ' ' || content[20] != ' ' || content[36] != ' ') {
    debug("action_gbye", RED "space error");
    return 1;
  }
  char ip[16], port_str[5], ip_next[16], port_next[5];
  int r = sscanf(content, "%s %s %s %s", ip, port_str, ip_next, port_next);
  if (r != 4 ||
      !isip(ip) || !isport(port_str) || !isip(ip_next) || !isport(port_next)) {
    debug("action_gbye", RED "goodbye not valid");
    return 1;
  }
  int port = atoi(port_str);
  int i;
  verbose("looking for correspondance with current entity...\n");
  int fixed_nring = *ring_number;
  for (i = 0; i < fixed_nring + 1; ++i) {
    debug("action_gbye", RED "comparaison ring %d:\n"
        "%s == %s:%d\n"
        "%d == %d: %d", i, ip, ent->ip_next[i], 
        strcmp(ip, ent->ip_next[i]) == 0, 
        port, ent->port_next[i],
        port == ent->port_next[i]);
    if (strcmp(ip, ent->ip_next[i]) == 0 && port == ent->port_next[i]) {
      debug("action_gbye", RED "correspondance found");
      verbose("Preparing structure for receiver address...\n");
      char ipnz[16];
      ipnozeros(ipnz, ip);
      int port2 = atoi(port_next);
      struct sockaddr_in entity_leaving = _ent->receiver[i];
      struct sockaddr_in receiver;
      if (!getsockaddr_in(&receiver, ipnz, port2, 0)) {
        verbose("Can't get address of %s at port %s.\n", ipnz, port2);
        debug("aciont_gbye", RED "can't send goodbye because "
            "can't access to new next entity !");
        return 0;
      }
      _ent->receiver[i] = receiver;
      verbose("Structure prepared.\n");
      verbose("Replacing current structure...\n");
      // modifying entity
      verbose("Insertion server: modifying current entity...\n");
      char buff[400];
      verbose("Insertion server: current entity :\n%s\n", entitytostr(i, buff));
      ent->port_next[i] = port2;
      strcpy(ent->ip_next[i], ip_next);
      verbose("Insertion server: modified entity :\n%s\n", entitytostr(i, buff));
      sendmessage_sockaddr(&entity_leaving, "EYBG", "");
      return 0;
    }
  }
  // retransmit message
  sendpacket_all(message);
  return 0;
}



int action_eybg(char *message, char *content, int lookup_flag)
{
  // message already seen
  if (lookup_flag)
    return 0;
  // BUT why ?
  if (gbye_data->wait) {
    gbye_data->wait = 0;
    pthread_cond_signal(&gbye_data->cond);
  }
  else {
    debug("action_eybg", RED "entity received EYBG whereas not waiting for it.");
    sendpacket_all(message);
  }
  return 0;
}



/*
static void usage(char *argv0)
{
  printf("Usage:\t%s", argv0);
}
*/


typedef struct goodbye_args {
  int ring;
  void (*no_more_ring_action)(void);
} goodbye_args;



static void *gbye(void *arg)
{
  goodbye_args *args = (goodbye_args *)arg;
  int ring = args->ring;
  /* int ring = *(int *)arg; */
  /* free((int *)arg); */
  verbose("Quitting process for ring %d...\n", ring);
  // discard case of a solo ring
  if (ent->port_next[ring] != ent->udp || 
      strcmp(ent->ip_self, ent->ip_next[ring]) != 0)
  {
    char udp[5], port_next[5];
    itoa4(udp, ent->udp);
    itoa4(port_next, ent->port_next[ring]);

    rlock_entity();
    debug("gbye", "Entity locked to prevent insertion.");
    sendmessage_all("GBYE", "%s %s %s %s", ent->ip_self, udp, ent->ip_next[ring],
        port_next);
    gbye_data->wait = 1;
    verbose("Waiting for EYBG message...");
    pthread_mutex_init(&gbye_data->mutex, NULL);
    pthread_cond_init(&gbye_data->cond, NULL);
    while (gbye_data->wait)
      pthread_cond_wait(&gbye_data->cond, &gbye_data->mutex);
    verbose("EYBG received.");
    unlock_entity();
    debug("gbye", "Entity unlocked.");
  }
  else
  {
    verbose("Quitting solo ring...\n");
  }
  rm_ring(ring);
  /* debug("gbye", RED "Ring %d quit. Ring number:%d\n", ring, *ring_number); */
  /* verbose("Ring %d quit.\n", ring); */
  if (*ring_number == -1) {
    verbose("Last ring quit.\n");
    args->no_more_ring_action();
  }
  pthread_mutex_unlock(&gbye_data->mutex);
  verbose("End of quitting process.\n");
  return NULL;
}



static int compare( const void* a, const void* b);



static void gbye_all_rings(void (*no_more_ring_action) (void))
/* static void gbye_all_rings() */
{
    /* pthread_t wait_gbye_t; */
    /* pthread_t *wait_gbye_t = malloc((*ring_number+1)*sizeof(pthread_t)); */
  if (!waiting) {
    waiting = 1;
    for (int n = *ring_number; n >= 0; --n) {
      goodbye_args *args = malloc(sizeof(goodbye_args));
      args->ring = n;
      args->no_more_ring_action = no_more_ring_action;
      pthread_create(wait_gbye_t+n, NULL, gbye, args);
      /* int *arg = malloc(sizeof(int)); */
      /* int *arg = malloc(sizeof(int)); */
      /* *arg = n; */
      /* pthread_create(&wait_gbye_t, NULL, gbye, arg); */
    }
    for (int n = *ring_number; n >= 0; --n)
      pthread_join(wait_gbye_t[n], NULL);
  }
}



int cmd_gbye(int argc, char **argv)
{
  if (argc == 1) {
    gbye_all_rings(close_threads);
    /* gbye_all_rings(); */
  }
  else {
    pthread_t wait_gbye_t;
    int len = argc-1;
    int *rings = malloc(sizeof(int) * (len));
    for (int i = 1; i < argc; ++i) {
      rings[i-1] = atoi(argv[i]);
      if (rings[i-1] > *ring_number || rings[i-1] < 0) {
        fprintf(stderr, "Invalid ring number: %d.\n", rings[i-1]);
        free(rings);
        return 1;
      }
    }
    qsort(rings, len, sizeof(int), compare);
    for (int i = len-1; i >= 0; --i) {
      goodbye_args *args = malloc(sizeof(goodbye_args));
      args->ring = rings[i];
      args->no_more_ring_action = close_threads;
      pthread_create(&wait_gbye_t, NULL, gbye, args);
      /* int *arg = malloc(sizeof(int)); */
      /* *arg = rings[i]; */
      /* pthread_create(&wait_gbye_t, NULL, gbye, arg); */
    }
    free(rings);
  }
  return 0;
}



////////////////////////////////////////////////////////////////////////////////
// EXIT
////////////////////////////////////////////////////////////////////////////////

#define   OPT_HELP      'h'
#define   OPTL_HELP     "help"
#define   OPT_FORCE     'f'
#define   OPTL_FORCE    "force"

#define   OPT_STRING    "hf"

static struct option longopts_exit[] = {
  {OPTL_HELP,  no_argument,   0,   OPT_HELP},
  {OPTL_FORCE, no_argument,   0,   OPT_FORCE},
  {0,          0,             0,   0}
};



static void usage_exit(const char *argv0) {
  printf("Usage:\t%s [-h --force]\n", argv0);
}



static void help_exit(const char *argv0) {
  usage_exit(argv0);
}

void exit_properly() 
{
  if (*ring_number >= 0)
    gbye_all_rings(close_threads_and_shell);
  else {
    close_threads_and_shell();
  }
}


int cmd_exit(int argc, char **argv)
{
  char c;
  int indexptr;
  optind = 0;
  while ((c = getopt_long(argc, argv, OPT_STRING,
          longopts_exit, &indexptr)) != -1) {
    switch (c) {
      case OPT_HELP:
        help_exit(argv[0]);
        return 0;
        break;
      case OPT_FORCE:
        /* close_threads(); */
        if (waiting)
          for (int i = 0; i <= *ring_number; ++i)
            pthread_cancel(wait_gbye_t[i]);
        pthread_exit(NULL);
        return 0;
        break;
      default:
        usage_exit(argv[0]);
        return 1;
    }
  }

  exit_properly();

  return 0;
}


//// END OF EXIT


static int compare( const void* a, const void* b)
{
  int int_a = * ( (int*) a );
  int int_b = * ( (int*) b );

  if ( int_a == int_b ) return 0;
  else if ( int_a < int_b ) return -1;
  else return 1;
}

