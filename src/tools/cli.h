#ifndef TEST_GENERATOR_CLI_H
#define TEST_GENERATOR_CLI_H

enum Generators {
  CholeskyDecomposableMatrix,
};

struct Config {
  Generators generator;
  std::pair<size_t, size_t> size;
  std::string filename;
  std::string type;
};

void parseCmdArgs(int argc, char **argv, Config &config);

#endif //TEST_GENERATOR_CLI_H
