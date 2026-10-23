#include "terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>


#include <iostream>

using namespace mcl;
using namespace std;

terminal::terminal() {
    home();
}

terminal::~terminal() {
    this->resetStyle();
}

void terminal::clear(void) {
    std::printf("\033[2J");
}

void terminal::home(void) {
    std::printf("\033[2J\033[H");
}

void terminal::bell(void) { 
    std::printf("\a"); 
}

// set/clear 'raw mode' 
void terminal::setRawMode(bool tf) {
    struct termios upd = {0};

    if (tf) {
        tcgetattr(STDIN_FILENO, &this->prevTermAttr);
        upd = this->prevTermAttr;
        upd.c_lflag &= ~(ICANON | ECHO /*| ISIG*/); // echoing off, canonical off, no signal chars
	    upd.c_cc[VMIN] = 1; // return on 1st char
	    upd.c_cc[VTIME] = 0; // no timeout
        tcsetattr(STDIN_FILENO,TCSAFLUSH,&upd);
    }
    else {
        tcsetattr(STDIN_FILENO,TCSAFLUSH,&this->prevTermAttr);
    } 
} 

// cursor management

void terminal::setCursorPosition(const uint16_t row, const uint16_t col) {
    std::printf("\033[%d;%dH", row, col);
}

void terminal::setCursorPosition(const CursorPosition_t position) {
    std::printf("\033[%d;%dH", position.y, position.x);
}   

void terminal::getTerminalSize(uint16_t& rows, uint16_t& cols) {
    struct winsize ws = {0};
    (void)ioctl (1, TIOCGWINSZ, &ws);

    cols = (uint16_t)ws.ws_col;
    rows = (uint16_t)ws.ws_row;
}

void terminal::setScrollingRegion(const uint16_t top, const uint16_t bottom) {
    std::printf("\033[%d;%dr", top, bottom);
}

void terminal::clearScrollingRegion(void) {
    std::printf("\033[r");
}

void terminal::setForegroundColor(const AnsiColor_t color) {
    std::printf("\033[%dm", color + 30);
}

void terminal::setBackgroundColor(AnsiColor_t color) {
    std::printf("\033[%dm", color + 40);
}

void terminal::setStyle(const AnsiStyle_t style) {
    std::printf("\033[%dm", style);
}

void terminal::resetStyle() {
    std::printf("\033[0m");
}

// print stuff out to the terminal

void terminal::put(const char c) {   
    std::putchar(c);   
    std::cout.flush();
}

void terminal::printLine(const char* str) {
    std::printf("%s\n", str);   
}

void terminal::printLine(const std::string& str) {
    std::printf("%s\n", str.c_str());   
}

void terminal::put(const char* str) {
    std::string cppstring(str);
    this->put(cppstring);  
}

void terminal::put(const std::string& str) {
    
    size_t n = 0;
    const size_t N = str.length();
    const char* c = str.c_str();

    if (c) {
        while ((c[n]) && (c[n] != '\n') && (n < N)) {
            this->put(c[n++]);
        }
    }

    std::cout.flush();
}

// fancier prints

void terminal::put(const AnsiColor_t fg, const AnsiColor_t bg, const AnsiStyle_t style, const std::string& str) {
    setForegroundColor(fg);
    setBackgroundColor(bg);
    setStyle(style);

    put(str);
    resetStyle();
} 

void terminal::put(const AnsiColor_t fg, const AnsiColor_t bg, const std::string& str) {
    setForegroundColor(fg);
    setBackgroundColor(bg);
    put(str);
    resetStyle();
}   

void terminal::put(const AnsiColor_t fg, const AnsiColor_t bg, const char c) {
    setForegroundColor(fg);
    setBackgroundColor(bg);

    put(c);
    resetStyle();
}

void terminal::put(const AnsiColor_t fg, const AnsiColor_t bg, const AnsiStyle_t style, const char c) {
    setForegroundColor(fg);
    setBackgroundColor(bg);
    setStyle(style);

    put(c);
    resetStyle();
}

// accept a line of user input
void terminal::getLine(const std::string& prompt, std::string& line) {
    std::memset(inputBuffer, 0, sizeof(inputBuffer));
    line = std::string("\0");
    bool readingInput = true;

    std::printf("%s", prompt.c_str());
    std::fflush(stdout);

    while (readingInput) {
        if (NULL == fgets(inputBuffer, sizeof(inputBuffer), stdin)) {
            readingInput = false;
        } 
        else {
            inputBuffer[std::strcspn(inputBuffer, "\n")] = '\0';
            line = std::string(inputBuffer);
            readingInput = false;
        }
    }
}

// get one char
char terminal::getRawChar(void) {
    struct termios org = {0};
    struct termios upd = {0};
    int tc = 0;

    tcgetattr(STDIN_FILENO, &org);
    upd = org;
    upd.c_lflag &= ~(ICANON | ECHO);

    upd.c_cc[VMIN] = 0; // return on 1st char
    upd.c_cc[VTIME] = 0; // no timeout

    tcsetattr(STDIN_FILENO, TCSANOW, &upd);
    tc = getchar(); // FIXME: handle escape codes too
    tcsetattr(STDIN_FILENO, TCSANOW, &org);

    return (char)tc;
}

void terminal::hideCursor(void) {
    std::printf("\033[?25l"); // Hide cursor
}

void terminal::showCursor(void) {
    std::printf("\033[?25h"); // Show cursor
}
