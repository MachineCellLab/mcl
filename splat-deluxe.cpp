#include "terminal.h"
#include <unistd.h>
#include <random>
#include <cstdio>
#include <iostream>


static const size_t numChars = 20;

static char Char[numChars] = {
    '*', '.', '!', '@',
    'o', '-', '%', '#',
    ',', '_', '+', ';',
    '.', '*', '=', 'q',
    '.', '*', '<', '>'
};


int main(int argc, char* argv[] ) {
    mcl::terminal term;
    std::random_device rng;
    std::mt19937_64 gen(rng());

    // determine screen size
    uint16_t x,y, new_x, new_y;
    char c;
    term.getTerminalSize(x,y);

    // set up rngs
    std::uniform_int_distribution<uint16_t> x_distrib(1, x);
    std::uniform_int_distribution<uint16_t> y_distrib(1, y);

    std::uniform_int_distribution<uint8_t>  color_distrib(0,7);

    std::uniform_int_distribution<size_t>   char_distrib(0,numChars);

    //std::uniform_real_distribution<double> distrib(0.0, 1.0);
    // std::cout << distrib(gen);

    // clear screen
    term.clear();
    term.home();
    term.resetStyle();

    std::printf("Detected Screen Size: %d rows %d cols\n",
                    x, y);

    // term.setCursorPosition(1, 1);
    // term.setForegroundColor(mcl::terminal::WHITE);
    // term.put('*');

    // term.setCursorPosition(10, 85);
    // term.setForegroundColor(mcl::terminal::RED);
    // term.put('*'); std::cout.flush();

    // sleep(3);

    new_x = 1; 
    new_y = 1;
    size_t rounds = 0;
    mcl::terminal::AnsiColor_t color;

    while(true) {
        // FIXME: make a size-change an update event

        // select splat origin
        new_x = x_distrib(gen);
        new_y = y_distrib(gen);
        color = (mcl::terminal::AnsiColor_t )color_distrib(gen);
        c     = Char[char_distrib(gen)];

        term.setCursorPosition(new_x, new_y);
        term.setForegroundColor(color);
        term.put(c); std::cout.flush();
        
        //usleep(1000);
        //term.setCursorPosition(new_x, new_y);
        //term.put(' '); std::cout.flush();

        // new_x++;
        // new_y++;

        // printf("!");

        // sleeep
        usleep(100);

        if (1 == (rounds++ % 1000)) { term.clear(); }
    }
}