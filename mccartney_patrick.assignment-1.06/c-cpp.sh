#!/usr/bin/env bash

# renames all .c files to .cpp

for f in *.c; do mv "$f" "${f%.c}.cpp"; done