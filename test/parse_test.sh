#!/bin/bash
gcc -D__DEBUG -o test/parse_test test/parse_test.c src/html/parse.c src/utils/logging.c > /dev/null && ./test/parse_test test/simple.html && rm -rf test/parse_test