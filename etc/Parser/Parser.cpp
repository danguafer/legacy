#include "Parser.h"
#include "Parser.SyntaxTree.h"

#include "libbnf/libbnf.h"
#include <Veritas/Data/String.h>
#include <cstring>

using namespace Silexars;
using namespace Data;

using Veritas::etc::Parser;

Parser::Parser(const char *grammar) {
    message = 0;

    bnf_syntax *stx = bnf_create_syntax(grammar);
    isvalid = !bnf_has_error(stx);
    if (!isValid()) {
        String s = String().format("L%d - %s", bnf_error_line(stx), bnf_error_message(stx));
        message = new char[s.length() + 1];
        strcpy(message, (char*) s.c_str());
    }

    syntax = stx;
}

Parser::~Parser() {
    bnf_free_syntax((bnf_syntax*) syntax);
    delete[] message;
}

bool Parser::isValid() const { return isvalid; }
const char* Parser::getMessage() const { return (const char*) message; }
Parser::SyntaxTree* Parser::parse(const char *source) const { return (SyntaxTree*) bnf_parse((bnf_syntax*) syntax, source); }
