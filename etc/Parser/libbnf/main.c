/*
#include "libbnf.h"
#include <stdio.h>

void print_syntax(bnf_syntax *stx) {
    bnf_rule *rule;
    for (rule = stx->rules; rule; rule = rule->n) {
        printf("<%s> :== ",rule->name);

        bnf_expr *expr;
        for (expr = rule->exprs; expr; expr = expr->n) {
            if (expr != rule->exprs) printf("| ");

            bnf_term *term;
            for (term = expr->terms; term; term = term->n) {
                switch (term->type) {
                    case BNF_LITERAL: printf("\"%s\" ",(char*)term->ptr); break;
                    case BNF_RULE: printf("<%s> ",((bnf_rule*)term->ptr)->name); break;
                    default: break;
                }
            }
        }
        printf("\n");
    }
}

void print_parse_tree(bnf_parse_tree *pt, int ident) {
    int i;
    for (i=0;i<ident;i++) printf(" ");
    if (pt->type == BNF_LITERAL) printf("%s\n",(char*)pt->ptr);
    else {
        printf("<%s>\n",pt->type);
        print_parse_tree(pt->ptr,ident+1);
    }

    if (pt->n) print_parse_tree(pt->n,ident);
}

int main(int argc, char **argv) {
    bnf_syntax *stx = bnf_load_syntax("../../bnfs/GLSL.bnf");
    if (bnf_has_error(stx)) {
        printf("L%d - %s",bnf_error_line(stx),bnf_error_message(stx));
        return 0;
    }

    printf("\n");

    bnf_parse_tree *pt = bnf_parse(stx,
        "attribute vec3 vertices;"
        "uniform float time;"

        "float global;"

        "void main(void) {"
            "a = f(10.0, 5);"
        "}"
    );

    if (pt) print_parse_tree(pt,0);

    bnf_free_parse_tree(pt);
    bnf_free_syntax(stx);
    return 0;
}
*/
