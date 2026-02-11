#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_PRINT,
    TOKEN_EQ,
    TOKEN_SEMI,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char text[32];
} Token;

void setInput(char *text);
Token getToken();

#endif