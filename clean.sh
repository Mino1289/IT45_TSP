#/bin/bash

set -xe

cd genetic && make clean
cd ../little && make clean
cd ../tabou && make clean

echo "Clean done"