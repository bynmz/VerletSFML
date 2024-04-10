#!/bin/bash
g++ -c chainsolver.cpp -ISFML-2.6.1/include
g++ chainsolver.o -o sfml-app -LSFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=SFML-2.6.1/lib && ./sfml-app