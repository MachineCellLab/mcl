#!/bin/sh
rm *.o

rm TEST
rm SPLAT
rm DELUXE-SPLAT
rm BALL
rm THOLIAN
rm GRAFX

g++ -c terminal.cpp
g++ -o TEST *.o Test.cpp
g++ -o SPLAT *.o splat.cpp
g++ -o DELUXE-SPLAT *.o splat-deluxe.cpp
g++ -o BALL *.o bouncy-ball.cpp
g++ -o THOLIAN *.o tholian.cpp
g++ -o GRAFX *.o graphics-chars.cpp

