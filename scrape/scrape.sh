#!/bin/bash

curl $1 > html.txt
./traverse $1 &
#rm ./traverse
#rm ./html.txt