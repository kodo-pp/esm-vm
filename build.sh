#!/bin/bash
make bee
g++ dump.cpp -std=gnu++17 -Wall -Wextra -o esmdump
g++ esms.cpp -std=gnu++17 -Wall -Wextra -o esms
