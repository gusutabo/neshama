#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

Token getToken() {
    static int c = ' ';
    Token t;

    if (isalpha(c)) {
        int i = 0;

        while (isalpha(c)) {
            t.text[i++] = c;
            c = getchar();
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

        while (isdigit(c))
        {
            t.text[i++] = c;
            c = getchar();
        }

        t.text[i] = '\0';
        t.type = TOKEN_NUM;
        return t;
    }
    
    if (c == '+') {
        c = getchar();
        t.type = TOKEN_PLUS;
        return t;
    }

    if (c == '-') {
        c = getchar();
        t.type = TOKEN_MINUS;
        return t;
    }

      if (c == '*') {
        c = getchar();
        t.type = TOKEN_MUL;
        return t;
    }

    if (c == '/') {
        c = getchar();
        t.type = TOKEN_DIV;
        return t;
    }

    if (c == ';') {
        c = getchar();
        t.type = TOKEN_SEMI;
        return t;
    }

    if (c == '=') {
        c = getchar();
        t.type = TOKEN_EQ;
        return t;
    }
    
    if (c == EOF) {
        t.type = TOKEN_EOF;
        return t;
    }

    c = getchar();
    return getToken();
}