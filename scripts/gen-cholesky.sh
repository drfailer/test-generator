#!/usr/bin/env bash

TEST_GENERATOR=../build/test_generator
OUTPUT_DIR=./cholesky

declare -a sizes=(4000 6000 8000 10000)
# declare -a sizes=(10)

if [ ! -d $OUTPUT_DIR ]; then
  mkdir -p $OUTPUT_DIR
fi

for size in ${sizes[@]}; do
  echo $size
  $TEST_GENERATOR -g choleq -s $size -o cholesky/$size.in
done
