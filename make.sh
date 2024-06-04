#/bin/bash

set -xe

cd genetic && make
cd ../little && make
cd ../tabou && make

echo "Compilation done"