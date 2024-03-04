#!/bin/bash
make -C build
cd $(pwd)/build
./bin/SusieBrowser 
cd ..