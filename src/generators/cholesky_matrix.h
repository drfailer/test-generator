#ifndef TEST_GENERATOR_CHOLESKY_MATRIX_H
#define TEST_GENERATOR_CHOLESKY_MATRIX_H

#include <random>
#include <cblas.h>
#include "../data/matrix.h"
#include "../tools/metafunctions.h"
#include "../tools/cli.h"

namespace tg::cholesky {

/// @brief Compute A = L * LT
template <typename T>
void matrixDotProduct(Matrix<T> &L, Matrix<T> &A) {
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, A.width(), A.height(), L.height(), 1.0,
              L.get(), L.width(), L.get(), L.width(), 1.0, A.get(), A.width());
}

/// @brief Generate a random lower triangular matrix and compute the product L*L**T.
/// @param matrix Symmetric matrix that contains the result of L*L**T. Can be used to test the
///               cholesky decomposition algorithm.
/// @param result Lower triangular matrix (L). Can be used to verify the result of the cholesky
///               algorithm.
template <typename T, typename BT = long>
void generateRandomCholeskyMatrix(Matrix<T> &matrix, Matrix<T> &result, BT low, BT high) {
  std::random_device dv;
  std::mt19937 gen(dv());
  mtf::distribution_type<BT> dis(low, high);

  for (size_t i = 0; i < matrix.height(); ++i) {
    for (size_t j = 0; j <= i; ++j) {
      BT value = dis(gen);
      if (value == 0 && i == j) value++;
      /* if (value == 0) value++; */
      result.at(i, j) = value;
    }
  }
  matrixDotProduct(result, matrix);
}

/// @brief Generate a random vector and compute result: matrix.solution = result
/// @param matrix Matrix containing the equation
/// @param result Vector result of the equation
/// @param solution Vector solution of the equation
template <typename T, typename BT = long>
void generateRandomEquationVector(Matrix<T> &matrix, Matrix<T> &result, Matrix<T> &solution, BT low, BT high) {
  std::random_device dv;
  std::mt19937 gen(dv());
  mtf::distribution_type<BT> dis(low, high);

  memset(result.get(), 0, sizeof(T) * result.height());

  for (size_t i = 0; i < solution.height(); ++i) {
    solution.at(i, 0) = dis(gen);
  }
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, result.height(), solution.width(),
              matrix.width(), 1.0, matrix.get(), matrix.width(), solution.get(), solution.width(),
              1.0, result.get(), result.width());
}

template <typename T, typename BT = long>
void generate(Config const &config) {
  size_t width = config.size.first;
  size_t height = config.size.second;
  Matrix<T> matrix(width, height);
  Matrix<T> triangular(width, height);
  std::ofstream fs(config.filename, std::ios::binary);

  // todo: the boundaries should be configurable
  generateRandomCholeskyMatrix<T, BT>(matrix, triangular, 0, 10);
  matrix.dump(fs);
  triangular.dump(fs);

  if (config.generator == CholeskyEquation) {
    Matrix<T> result(1, height);
    Matrix<T> solution(1, height);

    generateRandomEquationVector(matrix, result, solution, 0, 10);
    result.dump(fs);
    solution.dump(fs);
  }
}

}

#endif //TEST_GENERATOR_CHOLESKY_MATRIX_H
