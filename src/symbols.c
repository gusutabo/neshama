#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "../include/symbols.h"

void env_init(Environment *env) {
    env->varCount = 0;
}

void env_set(Environment *env, char *name, int value) {
    for (int i = 0; i < env->varCount; i++) {
        if (strcmp(env->vars[i].name, name) == 0) {
            env->vars[i].value = value;
            return;
        }
    }
    
    strcpy(env->vars[env->varCount].name, name);
    env->vars[env->varCount].value = value;
    env->varCount++;
}

int env_get(Environment *env, char *name) {
    for (int i = 0; i < env->varCount; i++) {
        if (strcmp(env->vars[i].name, name) == 0) {
            return env->vars[i].value;
        }
    }
    printf("Undefined variable: %s\n", name);
    exit(1);
}