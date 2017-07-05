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

#ifndef __LIBBNF_H__
#define __LIBBNF_H__

#define BNF_LITERAL 0
#define BNF_RULE    1
//#define BNF_TERM_TYPE_EXPR    2

#define BNF_ERROR  -1
#define BNF_FAIL    0
#define BNF_SUCCESS 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct s_bnf_term {
    char type;
    void *ptr;

    struct s_bnf_term *p,*n;
} bnf_term;

typedef struct s_bnf_expr {
    bnf_term *terms;

    struct s_bnf_expr *p,*n;
} bnf_expr;

typedef struct s_bnf_rule {
    char *name;
    bnf_expr *exprs;

    struct s_bnf_rule *p,*n;
} bnf_rule;

typedef struct s_bnf_syntax {
    bnf_rule *rules;
    long errorFlag;
    const char *errorMessage;
} bnf_syntax;

typedef struct s_bnf_parse_tree {
    char *type;
    void *ptr;
    struct s_bnf_parse_tree *n;
} bnf_parse_tree;

bnf_syntax* bnf_create_syntax(const char *grammar);
bnf_syntax* bnf_load_syntax(const char *filepath);
void bnf_free_syntax(bnf_syntax *stx);

int bnf_has_error(bnf_syntax *stx);
int bnf_error_line(bnf_syntax *stx);
const char* bnf_error_message(bnf_syntax *stx);

bnf_parse_tree* bnf_parse(bnf_syntax *stx, const char *code);
bnf_parse_tree* bnf_parse_file(bnf_syntax *stx, const char *path);
void bnf_free_parse_tree(bnf_parse_tree *pt);

#ifdef __cplusplus
}
#endif

#endif // __LIBBNF_H__
