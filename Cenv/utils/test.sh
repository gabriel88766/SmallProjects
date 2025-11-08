#!/bin/bash

cd graphics
g++ -c *.cpp
cd ..
g++ main.cpp graphics/*.o -lSDL2