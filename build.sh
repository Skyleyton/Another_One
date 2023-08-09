#!/bin/bash

set -xe

clang src/main.c src/Parser.c src/Scanner.c src/Symbtab.c src/Token.c -o bin/main