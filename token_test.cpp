#include "token.h"
#include <list>

int main(int argc, char *argv[]) {
    mcl::token t1("hello");
    mcl::token t2("world");
    mcl::token t3(t1);

    std::list<mcl::token> token_list;
    token_list.push_back(t1);
    token_list.push_back(t2);
    token_list.push_back(t3);

    return 0;
}