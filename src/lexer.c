#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../include/lexer.h"

static char *source;
static int pos;

void setInput(char *text) {
    source = text;
    pos = 0;
}

static char peek() {
    return source[pos];
}

static char advance() {
    return source[pos++];
}

Token getToken() {
    Token t;
    t.text[0] = '\0';

    while (isspace(peek())) {
        advance();
    }

    char c = peek();

    if (c == '\0') {
        t.type = TOKEN_EOF;
        return t;
    }

    if (isalpha(c)) {
        int i = 0;

        while (isalnum(peek())) {
            t.text[i++] = advance();
        }

        t.text[i] = '\0';

        if (strcmp(t.text, "print") == 0) {
            t.type = TOKEN_PRINT;
        } else {
            t.type = TOKEN_ID;
        }

        return t;
    }

    if (isdigit(c)) {
        int i = 0;

        while (isdigit(peek()))
        {
            t.text[i++] = advance();
        }

        t.text[i] = '\0';
        t.type = TOKEN_NUM;
        return t;
    }

    advance();
    
    switch (c) {
        case '+': t.type = TOKEN_PLUS; break;
        case '-': t.type = TOKEN_MINUS; break;
        case '*': t.type = TOKEN_MUL; break;
        case '/': t.type = TOKEN_DIV; break;
        case '=': t.type = TOKEN_EQ; break;
        case ';': t.type = TOKEN_SEMI; break;
        default: t.type = TOKEN_EOF; break;
    }
    
    return t;
}