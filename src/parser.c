#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/symbols.h"
#include "../include/parser.h"

void next(Parser *p) {
    p->current = getToken();
}

void error(Parser *p, const char *msg) {
    printf("Syntax error: %s\n", msg);
    printf("Actual token: '%s'\n", p->current.text);
}

void expect(Parser *p, TokenType type, const char *msg) {
    if (p->current.type != type) {
        error(p, msg);
    }
    
    next(p);
}

int factor(Parser *p) {
    int result;
    
    if (p->current.type == TOKEN_NUM) {
        result = atoi(p->current.text);
        next(p);
    } else if (p->current.type == TOKEN_ID) {
        result = env_get(p->env, p->current.text);
        next(p);
    } else {
        error(p, "Expected a number or a identifier symbol;");
    }
    
    return result;
}

int term(Parser *p) {
    int result = factor(p);
    
    while (p->current.type == TOKEN_MUL || 
        p->current.type == TOKEN_DIV) {
            TokenType op = p->current.type;
            next(p);
            
            int right = factor(p);
            
            if (op == TOKEN_MUL) {
                result *= right;
            } else {
                result /= right;
            }
    }
    
    return result;
}

int expression(Parser *p) {
    int result = term(p);
    
    while (p->current.type == TOKEN_PLUS || 
        p->current.type == TOKEN_MINUS) {
            TokenType op = p->current.type;
            next(p);
            
            int right = term(p);
            
            if (op == TOKEN_PLUS) {
                result += right;
            } else {
                result -= right;
            }
        }
        
        return result;
    }
    
void statement(Parser *p) {
    if (p->current.type == TOKEN_ID) {
        char name[32];
        strcpy(name, p->current.text);
        next(p);
        
        expect(p, TOKEN_EQ, "Expected a '='");
        
        int value = expression(p);
        env_set(p->env, name, value);
        
        expect(p, TOKEN_SEMI, "Expected a ';'");        
    } else if (p->current.type == TOKEN_PRINT) {
        next(p);
        
        int value = expression(p);
        
        expect(p, TOKEN_SEMI, "Expected a ';'");
        printf("%d\n", value);
    }
}

void parser_init(Parser *p, Environment *env) {
    p->env = env;
    next(p);
}

void parser_parse(Parser *p) {
    while (p->current.type != TOKEN_EOF) {
        statement(p);
    }
}