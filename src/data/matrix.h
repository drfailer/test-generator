#ifndef TEST_GENERATOR_MATRIX_H
#define TEST_GENERATOR_MATRIX_H

#include <cstddef>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

template <typename T>
class Matrix {
 public:
  Matrix(size_t width, size_t height) :
          width_(width), height_(height), ptr_(new T[width * height]()) {
  }

  Matrix(Matrix<T> const &other) : Matrix(other.width_, other.height_) {
    memcpy(ptr_, other.ptr_, sizeof(T) * width_ * height_);
  }

  Matrix(Matrix<T> &&other) noexcept
          : width_(other.width_), height_(other.height_), ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  ~Matrix() {
    delete[] ptr_;
  }

  [[nodiscard]] size_t width() const { return width_; }
  void width(size_t width) { width_ = width; }

  [[nodiscard]]size_t height() const { return height_; }
  void height(size_t height) { height_ = height; }

  T at(size_t i, size_t j) const { return ptr_[i * width_ + j]; }
  T &at(size_t i, size_t j) { return ptr_[i * width_ + j]; }

  T *get() { return ptr_; }

  // todo: for load and dump: add options to be able to read/write multiple matrix in one single file

  void load(std::ifstream &fs) {
    delete[] ptr_;

    fs >> width_ >> height_; // width and height on first line
    ptr_ = new T[width_ * height_];

    for (size_t i = 0; i < width_ * height_; ++i) {
      fs >> ptr_[i];
    }
  }

  void dump(std::ofstream &fs) const {
    fs << width_ << " " << height_ << std::endl;
    for (size_t i = 0; i < width_ * height_; ++i) {
      fs << ptr_[i] << " ";
    }
    fs << std::endl;
  }

 private:
  size_t width_ = 0;
  size_t height_ = 0;
  T *ptr_ = nullptr;
};

#endif //TEST_GENERATOR_MATRIX_H
