#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include <unistd.h>

extern int (*open_terminal)(pid_t *pid);

extern int isnumericn(const char *str, int n);

extern void itoa(char *s, int size, int i);
#endif /* PLUGIN_TOOL_H */