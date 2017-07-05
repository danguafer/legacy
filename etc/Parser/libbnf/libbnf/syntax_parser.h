typedef struct s_syntax_parser {
    unsigned long i;
    const char *s;
} syntax_parser;

bnf_parse_tree* parse_rule(syntax_parser *sp, bnf_rule *rule);

bnf_parse_tree* parse_term(syntax_parser *sp, bnf_term *term) {
    if (term->type == BNF_RULE) return parse_rule(sp,(bnf_rule*)term->ptr);
    else if (term->type == BNF_LITERAL) {
        unsigned long slen = strlen((const char*) term->ptr);
        if (!strncmp(&sp->s[sp->i], (char*) term->ptr,slen)) {
            sp->i += slen;

            bnf_parse_tree *pt = (bnf_parse_tree*) malloc(sizeof(bnf_parse_tree));

            pt->type = BNF_LITERAL;
            pt->ptr = term->ptr;
            pt->n = 0;
            return pt;
        }
    }
    return BNF_FAIL;
}

bnf_parse_tree* parse_expr(syntax_parser *sp, bnf_expr *expr) {
    bnf_term *term;
    bnf_parse_tree *pt = 0,*currentPT;

    for (term = expr->terms; term; term = term->n) {
        bnf_parse_tree *retPT = parse_term(sp,term);
        if (retPT) {
            if (!pt) pt = currentPT = retPT;
            else {
                currentPT->n = retPT;
                currentPT = retPT;
            }
        } else {
            bnf_free_parse_tree(pt);
            return BNF_FAIL;
        }
    }
    return pt;
}

bnf_parse_tree* parse_rule(syntax_parser *sp, bnf_rule *rule) {
    unsigned long i = sp->i;
    bnf_expr *expr;
    for (expr = rule->exprs; expr; expr = expr->n) {
        bnf_parse_tree *retPT = parse_expr(sp,expr);
        if (retPT) {
            bnf_parse_tree *pt = (bnf_parse_tree*) malloc(sizeof(bnf_parse_tree));
            pt->type = rule->name;
            pt->ptr = retPT;
            pt->n = 0;
            return pt;
        } else sp->i = i;
    }

    return BNF_FAIL;
}
