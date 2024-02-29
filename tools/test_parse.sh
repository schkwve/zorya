#!/bin/bash

gcc -o test src/html/parse.c src/log/logging.c -D__DEBUG > /dev/null && ./test ./tests/index.html && rm -rf ./test