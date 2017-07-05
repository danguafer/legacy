bnf_rule* process_search_rule(bnf_syntax *stx, const char *ruleName) {
    bnf_rule *rule;
    for (rule = stx->rules; rule; rule = rule->n)
        if (!strcmp(rule->name,ruleName)) return rule;
    return 0;
}

int process_term(bnf_syntax *stx, bnf_term *term) {
    if (term->type == BNF_RULE) {
        bnf_rule *rule = process_search_rule(stx, (const char*) term->ptr);
        if (rule) {
            free(term->ptr);
            term->ptr = rule;
        } else return set_error(stx,0,"Expression: Rule definition not found."); // Send a better message, identifying the rule :)
    } else if (term->type == BNF_LITERAL) {
        unsigned int i;
        char *s = (char*) term->ptr,
              isEscape = 0;
        for (i=0;s[i];i++) {
            if (isEscape) {
                isEscape = 0;

                unsigned char c = s[i];
                if (c == 'n') c = '\n';
                else if (c == 'r') c = '\r';
                else if (c == '0') c = '\0';
                else if (c == 't') c = '\t';
                else if (c == '\\');
                else continue;

                unsigned int j;
                s[i-1] = c;
                for (j=i+1;s[j];j++) s[j-1] = s[j];
                s[j-1] = 0;
                i--;
            } else if (s[i] == '\\') isEscape = 1;
        }
    }
    return BNF_FAIL;
}

int process_expr(bnf_syntax *stx, bnf_expr *expr) {
    bnf_term *term;
    for (term = expr->terms; term; term = term->n)
        if (process_term(stx,term) == BNF_ERROR) return BNF_ERROR;
    return BNF_SUCCESS;
}

int process_rule(bnf_syntax *stx, bnf_rule *rule) {
    bnf_expr *expr;

    for (expr = rule->exprs; expr; expr = expr->n)
        if (process_expr(stx,expr) == BNF_ERROR) return BNF_ERROR;
    return BNF_SUCCESS;
}

int process_join_rules(bnf_syntax *stx, bnf_rule *rule) {
    bnf_rule *other_rule;
    bnf_expr *lastExpr;
    for (lastExpr = rule->exprs; lastExpr->n; lastExpr = lastExpr->n);

    other_rule = rule->n;
    while (other_rule) {
        if (!strcmp(rule->name,other_rule->name)) {

            other_rule->exprs->p = lastExpr;
            for (lastExpr->n = other_rule->exprs; lastExpr->n; lastExpr = lastExpr->n);

            other_rule->p->n = other_rule->n;
            if (other_rule->n) other_rule->n->p = other_rule->p;
            free(other_rule->name);

            bnf_rule *ruleToFree = other_rule;
            other_rule = other_rule->n;
            free(ruleToFree);
        } else other_rule = other_rule->n;
    }
    return BNF_FAIL;
}

int process_syntax(bnf_syntax *stx) {
    bnf_rule *rule;

    // Join rules with the same name
    for (rule = stx->rules; rule; rule = rule->n)
        process_join_rules(stx,rule);

    for (rule = stx->rules; rule; rule = rule->n)
        if (process_rule(stx,rule) == BNF_ERROR) return BNF_ERROR;
    return BNF_SUCCESS;
}
