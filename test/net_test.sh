#!/bin/bash

gcc -D__DEBUG  -o test/net_test test/net_test.c src/utils/buffer.c src/utils/logging.c src/netwerk/connect.c && ./test/net_test && rm ./test/net_test
