#ifndef INTERFACE_H
#define INTERFACE_H



void run_shell();


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct cmd {
    char name[30];
    char desc[512];
    void (*exec)(int argc, char **args);
} command;


#endif /* INTERFACE_H */
