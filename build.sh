#!/bin/bash
g++ -c main.cpp -ISFML-2.6.1/include
g++ main.o -o sfml-app -LSFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=SFML-2.6.1/lib && ./sfml-app