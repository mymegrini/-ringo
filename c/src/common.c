#include "common.h"

#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

/* #ifndef NRING */
/* #define NRING 2 */
/* #endif */




int isnumeric(const char *str) {
    while(*str)
    {
        if(!isdigit(*str))
            return 0;
        str++;
    }

    return 1;
}




int isnumericn(const char *str, int n) {
    for (int i = 0; i < n; ++i)
        if(!isdigit(str[i]))
            return 0;

    return 1;
}



void itoa(char *s, int size, int i) {
  /* --size; */
  s[size] = 0;
  while (--size >= 0) {
    s[size] = 48 + i % 10;
    i /= 10;
  }
}




void itoa4(char *s, int i) {
  itoa(s, 4, i);
}


int yesno(const char *question) {
    char *ans = NULL;
    int yes;
    do {
        printf("%s " BOLD "[y/n] " RESET, question);
        size_t lus = 0;
        lus = getline(&ans, &lus, stdin); 
        ans[lus-1] = 0;
        *ans = toupper(*ans);
        yes = strcmp(ans, "Y");
    } while(yes != 0 && strcmp(ans, "N") != 0);
    free(ans);
    return yes == 0;
}


int yesnod(const char *question, const int yes) {
    char *ans = NULL;
    printf("%s " BOLD "[y/n] " RESET, question);
    size_t lus = 0;
    lus = getline(&ans, &lus, stdin); 
    ans[lus-1] = 0;
    *ans = toupper(*ans);
    int response;
    if (yes)
        response = strcmp(ans, "N") != 0;
    else
        response = strcmp(ans, "Y") == 0;
    free(ans);
    return response;
}


void printpacket(const char *packet) {
    printf("---\n%s\n---\n", packet);
}



int isip(const char *str) {
    if (//strlen(str) == 15 && 
            str[3] == '.' && str[7] == '.' && str[11] == '.') {
        return 
            isdigit(str[0]) && isdigit(str[1]) && isdigit(str[2]) &&
            isdigit(str[4]) && isdigit(str[5]) && isdigit(str[6]) &&
            isdigit(str[8]) && isdigit(str[9]) && isdigit(str[10]) &&
            isdigit(str[12]) && isdigit(str[13]) && isdigit(str[14]);
    }
    return 0;
}


int isport(const char *str) {
    return //strlen(str) == 4 &&
        isdigit(str[0]) && isdigit(str[1]) && isdigit(str[2]) &&
        isdigit(str[3]);
}

void ipnozeros(char *nozeros, const char *ip) {
    int j = 0;
    int lz = 0;
    for (int i = 0; i < 16; i++) {
        if ( ! (ip[i] == '0' && lz) ) {
            nozeros[j++] = ip[i];
            if (ip[i] == '.')
                lz = 1;
            else
                lz = 0;
        }
        /* else if (ip[i+1] == '.') { */
        else if (! isdigit(ip[i+1])) {
            nozeros[j++] = ip[i];
        } 
    }
}


static void itoa_var(char *str, int n) {
    int i;
    for (i = 0; n > 0; ++i, n /= 10)
        str[i] = '0' + n % 10;
    str[i] = 0;
}


static void fifo_path(char *name) {
    strcpy(name, "/tmp/ringo_xterm");
    struct timeval t;
    gettimeofday(&t, NULL);
    char istr[20];
    itoa_var(istr, t.tv_sec);
    strcat(name, istr);
    itoa_var(istr, t.tv_usec);
    strcat(name, istr);
}

static int fd_xterm = -1;
static pid_t pid_xterm;
static int fd_log = -1;
static int log_offset = 0;



int init_log(const char *logfile)
{
  int fd = open(logfile, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
  if (fd == -1)
    return 0;
  char str[] = "### LOG STARTING AT ";
  /* char str_date[256]; */

  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  /* printf ( "Current local time and date: %s", asctime (timeinfo) ); */
  /* /1* struct tm t; *1/ */
  /* mktime(&t); */
  /* strftime(str_date, sizeof(str_date), "%F\n", &t); */
  char buff[280];
  strcpy(buff, str);
  /* strcat(buff, str_date); */
  strcat(buff, asctime(timeinfo));
  if (write(fd, buff, strlen(buff)) == -1)
      perror("init_log");
  fd_log = fd;
  log_offset = 3;
  return 1;
}



static void init_verbosexterm() {
  fd_xterm = init_outputxterm(&pid_xterm);
}



/* int init_xterm_communication(pid_t *pid, int *pipe) { */
/*     char path[60], pathin[60]; */
/*     fifo_path(path); */
/*     mkfifo(path, 0600); */
/*     fifo_path(pathin); */
/*     mkfifo(pathin, 0600); */
/*     char cat_cmd[180]; */
/*     strcpy(cat_cmd, "/bin/cat "); */
/*     strcat(cat_cmd, path); */
/*     strcat(cat_cmd, "& tee "); */
/*     strcat(cat_cmd, pathin); */
/*     strcat(cat_cmd, " > /dev/null"); */
/*     int fd, fdin; */
/*     sigset_t mask; */
/*     pid_t p = fork(); */
/*     switch (p) { */
/*         case -1: */
/*             fprintf(stderr, "Fork error.\n"); */
/*             break; */
/*         case 0: */
/*             sigfillset(&mask); */
/*             sigprocmask(SIG_SETMASK, &mask, NULL); */
/*             execlp("xterm", "xterm", "-e", cat_cmd, NULL); */
/*             printf("FAILURE\n"); */
/*             exit(EXIT_FAILURE); */
/*             break; */ 
/*         default: */
/*             if ((fd = open(path, O_WRONLY)) == -1) { */
/*                 fprintf(stderr, "Can't open pipe\n"); */
/*                 return -1; */
/*             } */
/*             if ((fdin = open(pathin, O_RDONLY)) == -1) { */
/*                 fprintf(stderr, "Can't open pipe\n"); */
/*                 return -1; */
/*             } */
/*             *pid = p; */
/*             pipe[0] = fdin; */
/*             pipe[1] = fd; */
/*             return 0; */
/*             break; */
/*     } */
/*     return -1; */
/* } */



int init_outputxterm(pid_t *pid) {
    char path[60];
    fifo_path(path);
    mkfifo(path, 0600);
    char cat_cmd[80];
    strcpy(cat_cmd, "/bin/cat ");
    strcat(cat_cmd, path);
    int fd;
    sigset_t mask;
    pid_t p = fork();
    switch (p) {
        case -1:
            fprintf(stderr, "Fork error.\n");
            break;
        case 0:
            sigfillset(&mask);
            sigprocmask(SIG_SETMASK, &mask, NULL);
            execlp("xterm", "xterm", "-e", cat_cmd, NULL);
            printf("FAILURE\n");
            exit(EXIT_FAILURE);
            break; 
        default:
            if ((fd = open(path, O_WRONLY)) == -1) {
                fprintf(stderr, "Can't open pipe\n");
                return -1;
            }
            *pid = p;
            return fd;
            break;
    }
    return -1;
}

static void verbose_noverb(char *format, ...) {
}



static void verbose_xterm(char *format, ...) {
    va_list aptr;
    va_start(aptr, format);
    vdprintf(fd_xterm, format, aptr);
    va_end(aptr);
}


static void verbose_stdout(char *format, ...) {
    printf(BOLD UNDERLINED "verbose - " RESET);
    va_list aptr;
    va_start(aptr, format);
    vprintf(format, aptr);
    va_end(aptr);
}

static void verbose_noverb_and_log(char *format, ...) {
    va_list aptr;
    va_start(aptr, format);
    vdprintf(fd_log, format, aptr);
    va_end(aptr);
}



static void verbose_xterm_and_log(char *format, ...) {
    va_list aptr;
    va_start(aptr, format);
    vdprintf(fd_log, format, aptr);
    va_start(aptr, format);
    vdprintf(fd_xterm, format, aptr);
    va_end(aptr);
}



static void verbose_stdout_and_log(char *format, ...) {
    printf(BOLD UNDERLINED "verbose - " RESET);
    va_list aptr;
    va_start(aptr, format);
    vdprintf(fd_log, format, aptr);
    va_start(aptr, format);
    vprintf(format, aptr);
    va_end(aptr);
}


static int _verbose_mode = VERBM_NOVERB;
static int _last_verbose_mode = VERBM_STDOUT;



static void (*verbose_mode[])(char *, ...) = { 
    verbose_noverb,
    verbose_stdout,
    verbose_xterm,
    verbose_noverb_and_log,
    verbose_stdout_and_log,
    verbose_xterm_and_log
};



void (* volatile verbose)(char *format, ...) = verbose_noverb;



void verbosity(int mode) {
  if (mode == _verbose_mode)
    return;

  if (_verbose_mode == VERBM_XTERMO) {
    kill(pid_xterm, SIGKILL);
    close(fd_xterm);
  }

  if (mode == VERBM_XTERMO)
    init_verbosexterm();
  _last_verbose_mode = _verbose_mode;
  _verbose_mode = mode;
  verbose = verbose_mode[log_offset + mode];
}



void toggle_verbose() {
  verbosity(_last_verbose_mode);
}


