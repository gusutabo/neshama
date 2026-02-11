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

static void skip_whitespace() {
    while (isspace(peek())) {
        advance();
    }
}
static void skip_comment() {
    if (peek() == '/' && source[pos + 1] == '/') {
        advance();
        advance();

        while (peek() != '\n' && peek() != '\0') {
            advance();
        }
    }
}

static Token lex_number() {
    Token t;
    int i = 0;

    while (isdigit(peek())) {
        t.text[i++] = advance();
    }

    t.text[i] = '\0';
    t.type = TOKEN_NUM;
    return t;
}

static Token lex_identifier() {
    Token t;
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

static Token symbols() {
    Token t;
    char c = advance();
    t.text[0] = c;
    t.text[1] = '\0';

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

Token getToken() {
    skip_whitespace();
    skip_comment();
    skip_whitespace();
   
    if (peek() == '\0') {
        Token t;
        t.type = TOKEN_EOF;
        t.text[0] = '\0';
        return t;
    }

    if (isalpha(peek())) {
        return lex_identifier();
    }

    if (isdigit(peek())) {
        return lex_number();
    }

    return symbols();
}