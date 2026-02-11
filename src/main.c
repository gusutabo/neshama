#include <stdio.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/parser.h"

int main() {
    char line[256];

    Parser parser;
    Environment env;
    
    env_init(&env);

    printf("Neshama - REPL\n");

    while (1) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        setInput(line);
        parser_init(&parser, &env);
        parser_parse(&parser);
    }

    return 0;
}