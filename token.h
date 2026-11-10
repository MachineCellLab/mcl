#ifndef _mcl_token_
#define _mcl_token_

/*
    BaseToken<templated> -- this is what goes into the list (make_uniq, etc)

    TextToken<size, .4 or .8 aligned>

    NumericToken


*/

namespace mcl {
    class token {
        template <class T>
        private:
            token(); // no default constructor
        protected:
            const std::string myString;
        public:
            virtual ~token() {};

            token(const std::string& str) : myString(str) {};

            token(const char* str) : myString(str) {};

            token(const token& token) : myString(token.myString) {};

            inline const std::string& string(void) const { return myString; };

            inline const char* cstring(void) const { return (const char*)myString.c_str(); };
    };
}

#endif // _mcl_token_