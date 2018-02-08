#!/bin/bash
make clean
find -type f -name '*.o' | xargs rm -v
rm esmvm esmdump esms
