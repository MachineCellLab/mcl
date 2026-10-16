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

static void makeBox(mcl::terminal::CursorPosition_t upperLeft, 
                    mcl::terminal::CursorPosition_t lowerRight) {
    uint16_t r,c;
    mcl::terminal::CursorPosition_t lowerLeft = {lowerRight.col, lowerLeft.row};
    mcl::terminal::CursorPosition_t upperRight = {upperLeft.row, lowerRight.col};

    // draw the corners
    term.setGraphicsMode(true);

    term.setCursorPosition(upperLeft);
    term.put(mcl::terminal::UpperLeftCorner);

    // upper line
    r = upperLeft.row;
    for (c = upperLeft.col+1; c < lowerRight.col; c++) {
        term.setCursorPosition(r,c);
        term.put(mcl::terminal::Horizontal);
    }

    term.setCursorPosition(upperRight);
    term.put(mcl::terminal::UpperRightCorner);

    term.setCursorPosition(lowerLeft);
    term.put(mcl::terminal::LowerLeftCorner);

    //term.setCursorPosition(lowerRight);
    //term.put(mcl::terminal::LowerRightCorner);

    

    

    // lower line
    //r = lowerRight.row;
    //for (c = upperLeft.col; c < lowerRight.col; c++) {
      //  term.setCursorPosition(r,c);
        //term.put(mcl::terminal::Horizontal);
    //}

    // side, sinister...
    //c = lowerRight.col;
    //for (r = upperLeft.row+1; r < lowerRight.row-1; r++) {
        //term.setCursorPosition(r,c);
      //  term.put(mcl::terminal::Vertical);
    //}

    // side, dexter...
    //c = lowerRight.col;
    //for (r = upperLeft.row+1; r < lowerRight.row-1; r++) {
      //  term.setCursorPosition(r,c);
        //term.put(mcl::terminal::Vertical);
    //}

    term.setGraphicsMode(false);
    term.printLine("\r");
}

static void printGraphicsChars(void) {
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
}

int main (int argc, char *argv[]) {
    term.clear();
    term.hideCursor();

    printGraphicsChars();
    sleep(3);

    // BOX: 20 wide, 5 tall
    mcl::terminal::CursorPosition_t ul = {30, 30};
    mcl::terminal::CursorPosition_t lr = {35, 50};
    makeBox(ul, lr);

    term.setGraphicsMode(false);
    term.printLine("");
}