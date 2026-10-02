#ifndef _mcl_token_
#define _mcl_token_

namespace mcl {
    class token {
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