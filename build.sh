#!/bin/bash
make clean -j4
make -j4
for i in \
'g++ dump.cpp -std=gnu++17 -Wall -Wextra -o esmdump' \
'g++ putdata.cpp -std=gnu++17 -Wall -Wextra -o esmputdata' \
'g++ esms.cpp -std=gnu++17 -Wall -Wextra -o esms'
do
    echo "$i"
    $i &
done
wait
