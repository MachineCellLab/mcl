#!/bin/sh
rm *.o

rm TEST
rm SPLAT
rm DELUXE-SPLAT
rm BALL
rm THOLIAN
rm GRAFX

g++ -c ../terminal.cpp -I..
g++ -o TEST *.o test.cpp -I..
g++ -o SPLAT *.o splat.cpp -I..
g++ -o DELUXE-SPLAT *.o splat-deluxe.cpp -I..
g++ -o BALL *.o bouncy-ball.cpp -I..
g++ -o THOLIAN *.o tholian.cpp -I..
g++ -o GRAFX *.o graphics-chars.cpp -I..

