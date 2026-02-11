#ifndef PARSER_H
#define PARSER_H

#include "symbols.h"

typedef struct {
    Token current;
    Environment *env;
} Parser;

void parser_init(Parser *parser, Environment *env);
void parser_parse(Parser *parser);

#endif