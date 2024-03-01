#!/bin/bash
#
# Name: format.sh
# Author: Jozef Nagy <schkwve@gmail.com>
# Date: 1/3/2024
#
# A small utility to format all code using clang-format.
#

find src -type f \( -iname \*.c -o -iname \*.h \) -print0 | xargs -0 clang-format -i

