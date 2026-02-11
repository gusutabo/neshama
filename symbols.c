#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "symbols.h"

#define MAX_VARS 100
#define NAME_SIZE 32

typedef struct {
    char name[NAME_SIZE];
    int value;
} Variable;

static Variable vars[MAX_VARS];
static int varCount = 0;

void setVar(char *name, int value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;
            return;
        }
    }
    
    strcpy(vars[varCount].name, name);
    vars[varCount].value = value;
    varCount++;
}

int getVar(char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].value;
        }
    }
    printf("Undefined variable: %s\n", name);
    exit(1);
}