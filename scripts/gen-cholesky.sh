#!/usr/bin/env bash

TEST_GENERATOR=../build/test_generator
OUTPUT_DIR=./cholesky

declare -a sizes=(1000 2000 3000 4000 5000 6000 7000 8000 9000 10000)

if [ ! -d cholesky2 ]; then
  mkdir -p $OUTPUT_DIR
fi

for size in ${sizes[@]}; do
  echo $size
  $TEST_GENERATOR -g cholesky -s $size -o cholesky/$size.in
done
