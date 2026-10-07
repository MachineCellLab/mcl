#ifndef _mcl_tokenzier
#define _mcl_tokenzier

#include "token.h"
#include <list>

namespace mcl {
    class tokenizer {
        public:
            tokenizer() {};
            virtual ~tokenizer() {};

            virtual std::list<token> tokenize(const std::string& str) = 0;
    };
}

#endif // _mcl_tokenzier

/*
    this is "an example token string 'with embedded quote' and..." maybe $substys, too
*/