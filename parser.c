#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "symbols.h"
#include "parser.h"

Token current;

void next() {
    current = getToken();
}

void error(const char *msg) {
    printf("Syntax error: %s\n", msg);
    printf("Actual token: '%s'\n", current.text);
    exit(1);
}

void expect(TokenType type, const char *msg) {
    if (current.type != type) {
        error(msg);
    }

    next();
}

int factor() {
    int result;

    if (current.type == TOKEN_NUM) {
        result = atoi(current.text);
        next();
    } else if (current.type == TOKEN_ID) {
        result = getVar(current.text);
        next();
    } else {
        error("Expected a number or a identifier symbol;");
    }

    return result;
}

int term() {
    int result = factor();

    while (current.type == TOKEN_MUL || 
           current.type == TOKEN_DIV) {
        TokenType op = current.type;
        next();

        int right = factor();

        if (op == TOKEN_MUL) {
            result *= right;
        } else {
            result /= right;
        }
    }

    return result;
}

int expression() {
    int result = term();

    while (current.type == TOKEN_PLUS || 
           current.type == TOKEN_MINUS) {
        TokenType op = current.type;
        next();

        int right = term();

        if (op == TOKEN_PLUS) {
            result += right;
        } else {
            result -= right;
        }
    }

    return result;
}

void statement() {
    if (current.type == TOKEN_EOF) {
        return;
    }

    if (current.type == TOKEN_ID) {
        char name[32];
        strcpy(name, current.text);
        next();

        expect(TOKEN_EQ, "Expected a '='");

        int value = expression();
        setVar(name, value);

        expect(TOKEN_SEMI, "Expected a ';'");        
    } else if (current.type == TOKEN_PRINT) {
        next();

        int value = expression();
        
        expect(TOKEN_SEMI, "Expected a ';'");
        printf("%d\n", value);
    }
}

void parse() {
    next();
    statement();
}