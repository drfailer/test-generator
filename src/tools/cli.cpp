#include "tclap/CmdLine.h"
#include "cli.h"

class SizeConstraint : public TCLAP::Constraint<size_t> {
 public:
  [[nodiscard]] std::string description() const override {
    return "Positive non null";
  }
  [[nodiscard]] std::string shortID() const override {
    return "NonNullInteger";
  }
  [[nodiscard]] bool check(size_t const &value) const override {
    return value > 0;
  }
};

std::pair<size_t, size_t> parseSize(std::string const& sizeStr) {
    std::pair<size_t, size_t> size;
    char separator;
    std::istringstream iss(sizeStr);
    iss >> size.first;
    if (iss.eof()) {
      size.second = size.first;
    } else {
      iss >> separator;
      iss >> size.second;
    }
    return size;
}

Generators parseGenerator(std::string const &str) {
  Generators result;

  if (str == "cholesky" || str == "CholeskyDecomposableMatrix") {
    result = CholeskyDecomposableMatrix;
  } else if (str == "choleq" || str == "CholeskyEquation") {
    result = CholeskyEquation;
  } else {
    throw std::invalid_argument("error: generator not found.");
  }
  return result;
}

void parseCmdArgs(int argc, char **argv, Config &config) {
  // Parse the command line arguments
  try {
    TCLAP::CmdLine cmd("Generate test sample for testing linear algebra algorithms", ' ', "0.1");
    SizeConstraint sc;
    TCLAP::ValueArg<std::string> generatorArg("g", "generator", "Generator generator (ex: cholesky)", true, "", "string");
    cmd.add(generatorArg);
    TCLAP::ValueArg<std::string> sizeArg("s", "size", "Problem size (ex: 1000x1000 for matrix).", true, "", "string");
    cmd.add(sizeArg);
    TCLAP::ValueArg<std::string> outputArg("o", "output", "Output file name", false, "a.out", "string");
    cmd.add(outputArg);
    cmd.parse(argc, argv);

    auto size = parseSize(sizeArg.getValue());
    auto generator = parseGenerator(generatorArg.getValue());
    config.generator = generator;
    config.size = size;
    config.filename = outputArg.getValue();
  } catch (TCLAP::ArgException &e)  // catch any exceptions
  { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
}
