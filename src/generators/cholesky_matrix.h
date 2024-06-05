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

template <typename T, typename BT = long>
void generate(Config const &config) {
  size_t width = config.size.first;
  size_t height = config.size.second;
  Matrix<T> matrix(width, height);
  Matrix<T> result(width, height);
  std::ofstream fs(config.filename);

  // todo: the boundaries should be configurable
  generateRandomCholeskyMatrix<T, BT>(matrix, result, 0, 10);
  matrix.dump(fs);
  result.dump(fs);
}

}

#endif //TEST_GENERATOR_CHOLESKY_MATRIX_H
