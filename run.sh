#/bin/bash

set -xe

cd genetic && ./run.sh
cd ../little && ./run.sh
cd ../tabou && ./run.sh