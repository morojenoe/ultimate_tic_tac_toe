#!/usr/bin/env bash

g++ -std=c++1y -O2 -static -lm strategy.cpp
java -cp ../fourinarow-engine/bin com.theaigames.fourinarow.FourInARow "./a.out" "./a.out" 2>err.txt 1>out.txt