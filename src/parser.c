#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/symbols.h"
#include "../include/parser.h"
#include "../include/colors.h"

static void next(Parser *parser) {
    parser->current = getToken();
}

static void error(Parser *parser, const char *msg) {
    fprintf(stderr, COLOR_RED "Syntax error: %s\n" COLOR_RESET, msg);
    fprintf(stderr, COLOR_YELLOW "Actual token: '%s'\n" COLOR_RESET, parser->current.text);
    exit(EXIT_FAILURE);
}

static void expect(Parser *parser, TokenType type, const char *msg) {
    if (parser->current.type != type) {
        error(parser, msg);
    }
    
    next(parser);
}

int parse_factor(Parser *parser) {
    if (parser->current.type == TOKEN_NUM) {
        int result = atoi(parser->current.text);
        next(parser);
        return result;
    }
    
    if (parser->current.type == TOKEN_ID) {
        int result = env_get(parser->env, parser->current.text);
        next(parser);
        return result;
    } 

    error(parser, "Expected a number or a identifier symbol;");
    return 0;
}

int parse_term(Parser *parser) {
    int result = parse_factor(parser);
    
    while (parser->current.type == TOKEN_MUL || 
           parser->current.type == TOKEN_DIV) {
        
        TokenType operator_type = parser->current.type;
        next(parser);
            
        int right_value = parse_factor(parser);
        
        switch (operator_type) {
            case TOKEN_MUL:
                result *= right_value;
                break;
                
            case TOKEN_DIV:
                if (right_value == 0) {
                    error(parser, "This isn't possible.");
                }
                result /= right_value;
                break;
        }
    }
    
    return result;
}

int parse_expression(Parser *parser) {
    int result = parse_term(parser);
    
    while (parser->current.type == TOKEN_PLUS || 
          parser->current.type == TOKEN_MINUS) {
        TokenType operator_type = parser->current.type;
        next(parser);
            
        int right_value = parse_term(parser);
            
        switch (operator_type) {
            case TOKEN_PLUS:
                result += right_value;
                break;

            case TOKEN_MINUS:
                result -= right_value;
                break;
        }
    }
        
    return result;
}
    
static void parse_assignment(Parser *parser) {
    char variable_name[32];
    strcpy(variable_name, parser->current.text);
    
    next(parser);
    expect(parser, TOKEN_EQ, "Expected a '='");
    
    int value = parse_expression(parser);
    env_set(parser->env, variable_name, value);
    
    expect(parser, TOKEN_SEMI, "Expected a ';'");        
}

static void parse_print(Parser *parser) {
    next(parser);
    
    int value = parse_expression(parser);
    
    expect(parser, TOKEN_SEMI, "Expected a ';'");
    printf("%d\n", value);
}

void parse_statement(Parser *parser) {
    switch (parser->current.type) {
        case TOKEN_ID: parse_assignment(parser); break;
        case TOKEN_PRINT: parse_print(parser); break;
        default: error(parser, "Unexpected statement"); break;
    }
}

void parser_init(Parser *parser, Environment *env) {
    parser->env = env;
    next(parser);
}

void parser_parse(Parser *parser) {
    while (parser->current.type != TOKEN_EOF) {
        parse_statement(parser);
    }
}