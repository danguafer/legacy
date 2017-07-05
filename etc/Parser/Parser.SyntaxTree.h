#pragma once

#include "Parser.h"
#include <Veritas/Definitions/Definitions.h>
#include <Veritas/etc/Parser/libbnf/libbnf.h>

namespace Veritas {
    namespace etc {
        class Parser::SyntaxTree : protected bnf_parse_tree {
            public:
                ~SyntaxTree();

                char* getType() const;
                void* getData() const;

                Parser::SyntaxTree* next() const;

                void print(bool ident = true) const;

                void merge();
                void merge(const char* element);
                uint32 count(const char* element) const;
            private:
                friend class Parser;
                void print(bool ident, uint32 nident) const;
        };
    }
}
