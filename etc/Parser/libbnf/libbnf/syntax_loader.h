/*
The MIT License (MIT)

Copyright (c) 2014 Danilo Guanabara Fernandes (danguafer)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __LIBBNF_SYNTAX_LOADER_H__
#define __LIBBNF_SYNTAX_LOADER_H__

typedef struct s_syntax_loader {
    bnf_syntax *stx;
    const char *s;
    long i,size;
    long currentLine;

    bnf_rule *lastRule;
    bnf_expr *lastExpr;
    bnf_term *lastTerm;
} syntax_loader;

int set_error(bnf_syntax *stx, int line, const char *errorMessage) {
    stx->errorFlag = 1 | line << 1;
    stx->errorMessage = errorMessage;
    return BNF_ERROR;
}

int load_error(syntax_loader *sl, const char *errorMessage) {
    sl->i = sl->size;
    return set_error(sl->stx,sl->currentLine,errorMessage);
}

void load_whitespace(syntax_loader *sl) { while (sl->i < sl->size && (sl->s[sl->i] == ' ' || sl->s[sl->i] == '\t')) sl->i++; }

long load_rule_name(syntax_loader *sl) {
    char *name;
    long size = sl->i; // pre-initialization for calculating i - i0 = size
    for (; sl->i < sl->size && sl->s[sl->i] != '>'; sl->i++) {
        char c = sl->s[sl->i];
        if (!((c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9')
        || c == ' '
        || c == '-'
        || c == '_')) return load_error(sl,"Rule-name: Alphabet, digit or ' '/'-'/'_' expected but not found.");
    }
    if (sl->i == sl->size) return load_error(sl,"Rule: '>' expected but not found.");
    size = sl->i - size; // initialization (i - i0 = size)
    name = (char*) malloc(sizeof(char)*(size+1));
    name[size] = 0;
    strncpy(name,&sl->s[sl->i - size],size);

    bnf_rule *rule = (bnf_rule*) malloc(sizeof(bnf_rule));
    rule->name = name;
    rule->n = 0;
    rule->p = sl->lastRule;
    rule->exprs = 0;

    if (!sl->stx->rules) sl->stx->rules = rule;
    if (sl->lastRule) sl->lastRule->n = rule;

    sl->lastRule = rule;

    return BNF_SUCCESS;
}

int load_term(syntax_loader *sl) {
    unsigned int size;
    char delim;
    if (sl->s[sl->i] == '\'') delim = '\'';
    else if (sl->s[sl->i] == '"') delim = '"';
    else if (sl->s[sl->i] == '<') delim = '>';
    else return load_error(sl,"Term: Expecting (\\), (\") or (<) but none was found.");

    sl->i++; // skips delim

    char *pos = (char*) strchr(&sl->s[sl->i], delim);
    if (pos == &sl->s[sl->size]) return load_error(sl,delim == '>' ? "Term: <EOL> reached before terminating rule-name." : "Term: <EOL> reached before terminating literal.");

    size = pos - &sl->s[sl->i];

    bnf_term *term = (bnf_term*) malloc(sizeof(bnf_term));
    term->type = delim == '>' ? BNF_RULE : BNF_LITERAL;
    term->n = 0;
    term->p = sl->lastTerm;
    term->ptr = (char*) malloc(sizeof(char)*(size+1));
    ((char*) term->ptr)[size] = 0;
    strncpy((char*) term->ptr,&sl->s[sl->i],size);

    sl->i += size + 1; // length of literal + 1 for the delimitator

    if (!sl->lastExpr->terms) sl->lastExpr->terms = term;
    if (sl->lastTerm) sl->lastTerm->n = term;
    sl->lastTerm = term;

    return BNF_SUCCESS;
}

int load_expression(syntax_loader *sl) {
    sl->lastTerm = 0;

    bnf_expr *expr = (bnf_expr*) malloc(sizeof(bnf_expr));
    expr->terms = 0;
    expr->n = 0;
    expr->p = sl->lastExpr;

    if (!sl->lastRule->exprs) sl->lastRule->exprs = expr;
    if (sl->lastExpr) sl->lastExpr->n = expr;
    sl->lastExpr = expr;

    do {
        if (load_term(sl) == BNF_ERROR) return BNF_ERROR;
        load_whitespace(sl);
    } while ((sl->s[sl->i] == '"' || sl->s[sl->i] == '\'' || sl->s[sl->i] == '<'));

    return BNF_SUCCESS;
}

int load_rule(syntax_loader *sl) {
    sl->lastExpr = 0;

    load_whitespace(sl);

    if (sl->s[sl->i] == '<') sl->i++;
    else return load_error(sl,"Rule: '<' expected but not found.");

    if (load_rule_name(sl) == BNF_ERROR) return BNF_ERROR;

    if (sl->s[sl->i] == '>') sl->i++;
    else return load_error(sl,"Rule: '>' expected but not found.");

    load_whitespace(sl);

    if (!strncmp("::=",&sl->s[sl->i],3)) sl->i += 3;
    else return load_error(sl,"Rule: '::=' expected but not found.");

    load_whitespace(sl);
    do {
        if (sl->s[sl->i] == '|') sl->i++;

        load_whitespace(sl);

        if (load_expression(sl) == BNF_ERROR) return BNF_ERROR;

        load_whitespace(sl);
    } while (sl->s[sl->i] == '|');

    unsigned int i;
    for (i=0;;i++) {
        switch (sl->s[sl->i]) {
            case '\0': return BNF_SUCCESS;
            case '\r':
                sl->i++;
            case '\n':
                sl->i++;
                sl->currentLine++;
            break;
            default:
                if (!i) return load_error(sl,"Rule: <EOL> expected but not found.");
                return BNF_SUCCESS;
            break;
        }
    }

    return BNF_SUCCESS;
}

#include "syntax_post_process.h"

int load_syntax(syntax_loader *sl) {
    while (sl->i < sl->size)
        if (load_rule(sl) == BNF_ERROR) return BNF_ERROR;
    if (process_syntax(sl->stx) == BNF_ERROR) return BNF_ERROR;
    return BNF_SUCCESS;
}

#endif // __LIBBNF_SYNTAX_LOADER_H__
