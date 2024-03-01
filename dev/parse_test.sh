#!/bin/bash
gcc -D__DEBUG -o dev/parse_test dev/parse_test.c src/html/parse.c src/utils/logging.c > /dev/null && ./dev/parse_test dev/parse_test.html && rm -rf dev/parse_test