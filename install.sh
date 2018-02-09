#!/bin/bash
if [ -z "$1" ]; then
	echo "Usage: $0 <destination>"
	exit 1
fi

([ -e "$1" ] && ! [ -d "$1" ]) && (echo "Error: destination is not a directory"; exit 1)
mkdir -p "$1"
cp esmvm esmdump esms esmputdata "$1" -v
