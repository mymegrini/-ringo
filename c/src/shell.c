#include "shell.h"

#include "common.h"
#include "message.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <stdio.h>

typedef struct cmd {
    char name[32];
    char desc[512];
    void (*exec)(int argc, char **args);
} command;


void echo(int argc, char **argv) {
    
    for ( ++argv; *argv != NULL; ++argv)
        printf("%s ", *argv);
    printf("\n");
}

command cmd[] = { 
    { "echo", "Print a message", &echo },
    { "", "", NULL }
};

static char **split(char *str) {
    char **res = NULL;
    char *cpy = strdup(str);
    char *token = strtok(cpy, " ");
    int n = 0;
   while (token != NULL) {
       res = realloc(res, sizeof(char *) * ++n);
       if (res == NULL)
           return NULL;
       res[n-1] = (char *)malloc(strlen(token) + 1);
       strcpy(res[n-1], token);
       token = strtok(NULL, " ");
   } 
   res = realloc(res, sizeof(char *) * (n+1));
   res[n] = NULL;
   free(cpy);
   return res;
}



static void free_split(char **sp) {
    char **i;
    for (i = sp; *i != NULL; i++ )
        free(*i);
    free(sp);
}



static void exec_cmd(char *str) {
    char **sp = split(str);
    if (sp == NULL) {
        debug("exec_cmd(\"%s\")", "split returned NULL. realloc error.\n", str);
        free_split(sp);
        return;
    }
    if (*sp == NULL) {
        debug("exec_cmd(\"%s\")", 
                "split returned a pointer to NULL. Parsing error.\n", str);
        free_split(sp);
        return;
    }
    int argc;
    for (argc = 1; sp[argc] != NULL; ++argc)
        ;
    for (int i = 0; cmd[i].name[0] != 0; i++) {
        if (strcmp(cmd[i].name, sp[0]) == 0) {
            (*cmd[i].exec)(argc, sp);
            free_split(sp);
            return;
        }
    }
    system(str);
}


static void prompt() {
    char dirname[256];
    getcwd(dirname, 256);
    printf("%s > ", dirname);
}


static void cmd_whos(int argc, char **argv) {
    if (argc != 1)
        fprintf(stderr, "Usage:\t%s");
    sendmessage("WHOS", "");
}

////////////////////////////////////////////////////////////////////////////////
// GLOBAL
////////////////////////////////////////////////////////////////////////////////

void run_shell() {
    while(1) {
        prompt();
        char *line = NULL;
        size_t size = 0;
        size = getline(&line, &size, stdin);
        debug("run_shell()", "%d charaters read:\n%s\n", line);
        exec_cmd(line);
    }
}



