#!/bin/bash
make clean
find -type f -name '*.o' -delete
rm -f esmvm esmdump esms esmputdata
