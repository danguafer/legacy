#include "Parser.SyntaxTree.h"
#include "libbnf/libbnf.h"
#include <cstring>

#include <Veritas/Data/String.h>

using Veritas::etc::Parser;
using Silexars::Data::String;

Parser::SyntaxTree::~SyntaxTree() { bnf_free_parse_tree(this); }

char* Parser::SyntaxTree::getType() const { return type; }
void* Parser::SyntaxTree::getData() const { return ptr; }
Parser::SyntaxTree* Parser::SyntaxTree::next() const { return (Parser::SyntaxTree*) n; }

void print(Parser::SyntaxTree *st, String &s) {
    if (st->getType() == BNF_LITERAL) s += (char*) st->getData();
    else print((Parser::SyntaxTree*) st->getData(), s);

    if (st->next()) print(st->next(), s);
}

void Parser::SyntaxTree::print(bool ident) const {
    print(ident, 0);
}
void Parser::SyntaxTree::print(bool ident, uint32 nident) const {
    if (ident) for (uint32 i = 0; i < nident; i++) printf(" ");
    if (getType() == BNF_LITERAL) printf("%s\n", (char*) getData());
    else {
        printf("<%s>\n", getType());
        ((Parser::SyntaxTree*) getData())->print(ident, nident + 1);
    }

    if (next()) next()->print(ident, nident);
}

void Parser::SyntaxTree::merge() {
    if (getType() != BNF_LITERAL) {
        String string;
        ::print((SyntaxTree*) ptr, string);

        SyntaxTree *child = new SyntaxTree;
        child->n = 0;
        child->type = BNF_LITERAL;
        child->ptr = malloc(string.length() + 1);
        strcpy((char*) child->ptr, (char*) string.c_str());

        ptr = child;
    }
}

void Parser::SyntaxTree::merge(const char *element) {
    if (getType() != BNF_LITERAL) {
        if (!strcmp((char*) getType(), element)) merge();
        else ((Parser::SyntaxTree*) getData())->merge(element);
    }
    if (next()) next()->merge(element);
}

uint32 Parser::SyntaxTree::count(const char *element) const {
    uint32 count = 0;
    if (getType() != BNF_LITERAL) {
        if (!strcmp((char*) getType(), element)) count++;
        count += ((SyntaxTree*) getData())->count(element);
    }
    if (next()) count += next()->count(element);
    return count;
}
