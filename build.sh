#!/bin/sh
g++ -c terminal.cpp
g++ -o TEST *.o Test.cpp
g++ -o SPLAT *.o splat.cpp
g++ -o DELUXE-SPLAT *.o splat-deluxe.cpp

