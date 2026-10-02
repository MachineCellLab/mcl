#include "terminal.h"
#include "shell-token.h"

int main(int argc, char** argv) {
    mcl::terminal term;

    term.clear();
    term.home();

    term.setForegroundColor(mcl::terminal::RED);
    term.put("Hello, World!\n");
    term.resetStyle();

    term.setCursorPosition(10, 5);
    term.setForegroundColor(mcl::terminal::WHITE);
    term.setBackgroundColor(mcl::terminal::RED);
    term.setStyle(mcl::terminal::BLINK);
    term.put("This is a test.");
    term.resetStyle();  

    term.setCursorPosition(11, 7);
    std::printf("(11,7)\n");

    term.setCursorPosition(17, 75);
    std::printf("(17,75)\n");

    for (int k = 0; k < 10; ++k) {
        uint16_t x, y;
        term.getTerminalSize(x, y);
        printf("terminal size: %d rows, %d cols\n", x, y);
        sleep(1);
    }

    std::printf("Type 'exit' to quit.\n");
    std::printf("none: %x\n", mcl::token::Unknown);
    std::printf("char: %x\n", mcl::token::Char);
    std::printf("string: %x\n", mcl::token::String);
    std::printf("integer: %x\n", mcl::token::Integer);
    std::printf("count: %x\n", mcl::token::Count);
    std::printf("real: %x\n", mcl::token::Real);
    std::printf("paren clause: %x\n", mcl::token::ParenClause);
    std::printf("brace clause: %x\n", mcl::token::BraceClause);
    std::printf("bracket clause: %x\n", mcl::token::BracketClause);
    std::printf("quoted: %x\n", mcl::token::Quoted);    

    while (true) {
        std::string line;
        std::string cmd_exit = "exit\n"; // FIXME: deal with sanitization later.

        term.getLine("i am listening... : ", line);

        std::printf("You entered: %s\n", line.c_str());
    
        if (line == cmd_exit) {
            std::printf("Exiting...\n");
            break;
        }
    }

    return 0;
}