#include <iostream>
#include "data/matrix.h"
#include "tools/cli.h"
#include "generators/cholesky_matrix.h"

void generate(Config const &config) {
  switch (config.generator) {
    case CholeskyDecomposableMatrix:
      // todo: boundaries type should be configurable
      tg::cholesky::generate<double, int>(config);
      break;
  }
}

int main(int argc, char **argv) {
  Config config = {
          .generator = CholeskyDecomposableMatrix,
          .size = {0,0},
          .filename = "",
          .type = "int"
  };
  parseCmdArgs(argc, argv, config);
  generate(config);
  return 0;
}