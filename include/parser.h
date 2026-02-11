#ifndef PARSER_H
#define PARSER_H

#include "symbols.h"

typedef struct {
    Token current;
    Environment *env;
} Parser;

void parser_init(Parser *p, Environment *env);
void parser_parse(Parser *p);

#endif