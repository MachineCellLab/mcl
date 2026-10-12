#include "terminal"
#include <unistd.h>
#include <random>

int main(int argc, char* argv) {
    mcl::terminal term;
    std::random_device rng;
    std::std::mt19937_64 gen(rng());

    // determine screen size
    uint16_t x,y;
    term.getTerminalSize(x,y);

    // set up rngs
    std::uniform_int_distribution<uint16_t> x_distrib(1, x);
    std::uniform_int_distribution<uint16_t> y_distrib(1, y); 

    //std::uniform_real_distribution<double> distrib(0.0, 1.0);
    // std::cout << distrib(gen);

    while(true) {
        // FIXME: make a size-change an update event

        // select splat origin
        new_x = x_distrib(gen);
        new_y = y_distrib(gen);

        // sleeep
        usleep(100000) // 0.1s
    }
}