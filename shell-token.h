#ifndef _mcl_shell_token_
#define _mcl_shell_token_

#include "token.h"

namespace mcl {
    class shell_token : public token {
        public:
            /*
                By convention, we use u32s as strings.
            */
            typedef enum shell_token_type : uint32_t {
                Unknown = (uint32_t)('none'),
                Char = (uint32_t)('char'),
                String = (uint32_t)('strn'),

                Integer = (uint32_t)('intg'),
                Count = (uint32_t)('icnt'),
                Real = (uint32_t)('real'),

                ParenClause = (uint32_t)('parn'),
                BraceClause = (uint32_t)('brce'),
                BracketClause = (uint32_t)('brkt'),

                Quoted = (uint32_t)('quot'),
                Substitution = (uint32_t)('sbst'),
            } shell_token_type;

            // create from string
            shell_token(const std::string& str, const shell_token_type type) : token(str), myType(type) {
                // tbd
            };

            // create from c-string
            shell_token(const char* str, const shell_token_type type) : token(str), myType(type) {
                // tbd
            };

            // copy constructor
            shell_token(const shell_token& token) : shell_token(token.myString), myType(token.myType) {
                // tbd
            };

            inline const shell_token_type getType(void) const { return myType; };
            
            virtual ~shell_token() {};

        private:
            shell_token(); // no default constructor
            const shell_token_type myType;
    };
}

/*
    PofS: noun, pron, verb, advb, adjv, prep, conj, intj

    SOV: subj [tvrb | ivrb] objt 
*/

#endif