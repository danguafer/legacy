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

#include "libbnf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_file_string(FILE *fp, long *size) {
    fseek(fp,0,SEEK_END);
    *size = ftell(fp);
    fseek(fp,0,SEEK_SET);

    char *s = (char*) malloc(*size+1);
    s[*size] = 0;
    fread(s,1,*size,fp);

    return s;
}

#include "libbnf/syntax_loader.h"

int bnf_has_error(bnf_syntax *stx) { return stx->errorFlag; }
int bnf_error_line(bnf_syntax *stx) { return stx->errorFlag>>1; }
const char* bnf_error_message(bnf_syntax *stx) { return stx->errorMessage; }

bnf_syntax* bnf_create_syntax(const char *s) {
    syntax_loader sl;
    long size = strlen(s);

    sl.stx = (bnf_syntax*) malloc(sizeof(bnf_syntax));
    sl.stx->errorFlag = 0;
    sl.stx->errorMessage = 0;
    sl.stx->rules = 0;

    sl.s = s;
    sl.i = 0;
    sl.size = size;

    sl.currentLine = 0;
    sl.lastRule = 0;
    sl.lastExpr = 0;
    sl.lastTerm = 0;

    load_syntax(&sl);

    return sl.stx;
}

bnf_syntax* bnf_load_syntax(const char *str) {
    FILE *fp = fopen(str,"rb");
    if (fp) {
        long size;
        char *s = get_file_string(fp, &size);
        fclose(fp);
        bnf_syntax *stx = bnf_create_syntax(s);
        free(s);
        return stx;
    }

    return 0;
}

#include "libbnf/syntax_releaser.h"

void bnf_free_syntax(bnf_syntax *stx) {
    bnf_rule *currentRule = stx->rules;

    while (currentRule) {
        bnf_expr *currentExpr = currentRule->exprs;

        while (currentExpr) {
            bnf_term *currentTerm = currentExpr->terms;

            while (currentTerm) {
                if (currentTerm->type == BNF_LITERAL) free(currentTerm->ptr);

                bnf_term *termToFree = currentTerm;
                currentTerm = currentTerm->n;
                free(termToFree);
            }
            bnf_expr *exprToFree = currentExpr;
            currentExpr = currentExpr->n;
            free(exprToFree);
        }

        bnf_rule *ruleToFree = currentRule;
        currentRule = currentRule->n;
        free(ruleToFree->name);
        free(ruleToFree);
    }

    free(stx);
}

#include "libbnf/syntax_parser.h"

bnf_parse_tree* bnf_parse_file(bnf_syntax *stx, const char *path) {
    FILE *fp = fopen(path,"rb");

    if (fp) {
        long size;
        char *s = get_file_string(fp,&size);
        fclose(fp);
        return bnf_parse(stx,s);
    }
    return 0;
}

bnf_parse_tree* bnf_parse(bnf_syntax *stx, const char *str) {
    syntax_parser sp;
    sp.i = 0;
    sp.s = str;

    // Search root rule
    bnf_rule *rule;
    for (rule = stx->rules; rule; rule = rule->n) {
        bnf_parse_tree *pt = parse_rule(&sp,rule);
        if (pt) return pt;
        else sp.i = 0;
    }
    return 0;
}

void bnf_free_parse_tree(bnf_parse_tree *pt) {
    /*
    if (pt) {
        if (pt->type != BNF_LITERAL) bnf_free_parse_tree((bnf_parse_tree*) pt->ptr);

        bnf_parse_tree *cpt = pt->n;
        while (cpt) {
            bnf_parse_tree *tmp = cpt->n;
            bnf_free_parse_tree(cpt);
            cpt = tmp;
        }
        free(pt);
    }
    */
}
