#!/bin/sh
rm *.o

rm TEST
rm SPLAT
rm DELUXE-SPLAT
rm BALL
rm THOLIAN
rm GRAFX

g++ -c terminal.cpp
g++ -o tests/TEST *.o tests/test.cpp
g++ -o tests/SPLAT *.o tests/splat.cpp
g++ -o tests/DELUXE-SPLAT *.o tests/splat-deluxe.cpp
g++ -o tests/BALL *.o tests/bouncy-ball.cpp
g++ -o tests/THOLIAN *.o tests/tholian.cpp
g++ -o tests/GRAFX *.o tests/graphics-chars.cpp

