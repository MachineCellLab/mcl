#include "terminal.h"
#include <unistd.h>
#include <random>
#include <cstdio>
#include <iostream>

int main(int argc, char* argv[] ) {
    mcl::terminal term;
    std::random_device rng;
    std::mt19937_64 gen(rng());

    // determine screen size
    uint16_t ROWS,COLS,x,y;
    term.getTerminalSize(ROWS,COLS);

    // set up rngs
    std::uniform_int_distribution<uint16_t>    row_distrib(1, ROWS);
    std::uniform_int_distribution<uint16_t>    col_distrib(1, COLS);
    std::uniform_int_distribution<uint8_t>     color_distrib(0,7);

    mcl::terminal::AnsiColor_t color;

    //std::uniform_real_distribution<double> distrib(0.0, 1.0);
    // std::cout << distrib(gen);

    // clear screen
    term.clear();
    term.home();
    term.resetStyle();

    // choose initial pos
    //x = col_distrib(gen);
    //y = row_distrib(gen);

    uint16_t delta_x = 1;
    uint16_t delta_y = 1;

    term.setCursorPosition(ROWS/2, COLS/2);
    term.put("GO!");

    size_t max_rounds = 20*(ROWS * COLS);
    size_t rounds = 0;

    term.hideCursor();

    x = 1; y = 1;

    while (true) {
        term.setCursorPosition(y,x);
        term.put('*');
        usleep(1000);

        mcl::terminal::AnsiColor_t color = (mcl::terminal::AnsiColor_t)color_distrib(gen);
        term.setForegroundColor(color);

        // increment
        x += delta_x;
        y += delta_y;

        // check bounds
        if (x > COLS) {
            x--; delta_x = -delta_x;
        }

        if (x < 1) {
            x++; delta_x = -delta_x;
        }

        if (y > ROWS) {
            y--; delta_y = -delta_y;
        }

        if (y < 1) {
            y++; delta_y = -delta_y;
        }

        // possible reset condition?
        //if ((x==1)&&(y==1)) {term.clear();}

        // another one?
        rounds++;
        //if (rounds > max_rounds) {term.clear(); rounds = 0;}
    }
}