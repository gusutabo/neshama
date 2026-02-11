#ifndef SYMBOLS_H
#define SYMBOLS_H

#define MAX_VARS 100

typedef struct {
    char variable_name[32];
    int value;
} Variable;

typedef struct {
    Variable vars[MAX_VARS];
    int varCount;
} Environment;

void env_init(Environment *env);
void env_set(Environment *env, char *variable_name, int value);
int env_get(Environment *env, char *variable_name);

#endif
