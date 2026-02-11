#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

int main() {
    char line[256];
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
        parse();
    }

    return 0;
}