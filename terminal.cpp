#include "terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

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

// cursor management

void terminal::setCursorPosition(const uint16_t x, const uint16_t y) {
    std::printf("\033[%d;%dH", y, x);
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
    std::printf("%c", c);   
}

void terminal::put(const char* str) {
    std::printf("%s", str);   
}

void terminal::put(const std::string& str) {
    std::printf("%s", str.c_str());
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
