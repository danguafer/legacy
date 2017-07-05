#pragma once

namespace Veritas {
    namespace etc {
        class Parser {
            public:
                class SyntaxTree;

                Parser(const char *grammar);
                ~Parser();

                SyntaxTree* parse(const char *source) const;

                bool isValid() const;
                const char* getMessage() const;
            private:
                void* syntax;

                bool isvalid;
                char *message;
        };
    }
}

#include "Parser.SyntaxTree.h"
