#include "terminal.h"

static mcl::terminal term;

static void printout(uint16_t row, 
                     uint16_t col,
                     const char* text,
                     const char gchar)
{
    term.setCursorPosition(row, col);
    term.setGraphicsMode(false);
    term.put(text);

    term.setGraphicsMode(true);
    term.setCursorPosition(row, col+20);
    term.put(gchar);
}

int main (int argc, char *argv[]) {
    term.clear();
    term.hideCursor();

    printout(1, 1, "LowerLeftCorner:", mcl::terminal::LowerLeftCorner);
    printout(3, 1, "LowerRightCorner:", mcl::terminal::LowerRightCorner);
    printout(5, 1, "UpperLeftCorner:", mcl::terminal::UpperLeftCorner);
    printout(5, 1, "UpperRightCorner:", mcl::terminal::UpperRightCorner);


    printout(7, 1, "CrossTee:", mcl::terminal::CrossTee);
    printout(9, 1, "Horizontal:", mcl::terminal::Horizontal);
    printout(11, 1, "LeftTee:", mcl::terminal::LeftTee);
    printout(13, 1, "RightTee:", mcl::terminal::RightTee);
    printout(15, 1, "BottomTee:", mcl::terminal::BottomTee);
    printout(17, 1, "TopTee:", mcl::terminal::TopTee);
    printout(19, 1, "Vertical:", mcl::terminal::Vertical);

    printout(21, 1, "CheckerBoard:", mcl::terminal::CheckerBoard);
    printout(23, 1, "Degree:", mcl::terminal::Degree);

    printout(25, 1, "PlusMinus:", mcl::terminal::PlusMinus);

    term.printLine("");

    term.setGraphicsMode(false);
}