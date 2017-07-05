#ifndef __LIBBNF_SYNTAX_LOADER_H__
#define __LIBBNF_SYNTAX_LOADER_H__

typedef struct s_syntax_loader {
    bnf_syntax *stx;
    const char *s;
    long i,size;
    long currentLine,currentRule;
} syntax_loader;

unsigned long load_count_rules(const char *s, long size) {
    unsigned long rules = 0;
    unsigned int i;
    char isBOL = 1;
    char isReadingName = 0;
    for (i = 0; i < size; i++) {
        if (isReadingName && s[i] == '>') {
            isReadingName = 0;
            rules++;
        } else if (isBOL) {
            if (s[i] == '<') {
                isReadingName = 1;
                isBOL = 0;
            }
        } else if (s[i] == '\n') isBOL = 1;
    }
    return rules;
}

long load_error(syntax_loader *sl, const char *errorMessage) {
    sl->stx->errorFlag = 1 | sl->currentLine << 1;
    sl->stx->errorMessage = errorMessage;
    sl->i = sl->size;
    return 0;
}

void load_whitespace(syntax_loader *sl) { while (sl->i < sl->size && sl->s[sl->i] == ' ') sl->i++; }

long load_rule_name(syntax_loader *sl) {
    char *name;
    long size = sl->i; // pre-initialization for calculating i - i0 = size
    for (; sl->i < sl->size && sl->s[sl->i] != '>'; sl->i++) {
        char c = sl->s[sl->i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) return load_error(sl,"Rule-name: Alphabet or ' ' expected but not found.");
    }
    if (sl->i == sl->size) return load_error(sl,"Rule: '>' expected but not found.");
    size = sl->i - size; // initialization (i - i0 = size)
    name = (char*) malloc(sizeof(char)*(size+1));
    name[size] = 0;
    strncpy(name,&sl->s[sl->i - size],size);

    sl->stx->rules[sl->currentRule].name = name;

    return 1;
}



int load_expression(syntax_loader *sl) {

    return 1;
}

int load_rule(syntax_loader *sl) {
    load_whitespace(sl);

    if (sl->s[sl->i] == '<') sl->i++;
    else return load_error(sl,"Rule: '<' expected but not found.");

    if (!load_rule_name(sl)) return 0;

    if (sl->s[sl->i] == '>') sl->i++;
    else return load_error(sl,"Rule: '>' expected but not found.");

    load_whitespace(sl);

    if (!strncmp("::=",&sl->s[sl->i],3)) sl->i += 3;
    else return load_error(sl,"Rule: '::=' expected but not found.");

    load_whitespace(sl);

    if (!load_expression(sl)) return 0;

    if (sl->s[sl->i] == '\0');
    else if (sl->s[sl->i] == '\n') {
        sl->i++;
        sl->currentLine++;
    } else if (!strncmp("\r\n",&sl->s[sl->i],2)) {
        sl->i += 2;
        sl->currentLine++;
    } else return load_error(sl,"Rule: <EOL> expected but not found.");

    sl->currentRule++;
    return 1;
}

int load_syntax(syntax_loader *sl) {
    while (sl->i < sl->size) load_rule(sl);
    return 1;
}

#endif // __LIBBNF_SYNTAX_LOADER_H__
