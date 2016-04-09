#!/bin/bash
g++ -O3 -std=c++11 -Wall -o apc_st -I./  main.cpp Sparse.cpp Tokenize.cpp CSR.cpp CSC.cpp
