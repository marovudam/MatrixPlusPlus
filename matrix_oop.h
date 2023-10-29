#ifndef MATRIXPLUSPLUS_MATRIX_OOP_H_
#define MATRIXPLUSPLUS_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

class Matrix {
 public:
  const double kPrecision = std::numeric_limits<double>::epsilon();

  Matrix();
  explicit Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other) noexcept;
  ~Matrix();

  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;
  bool EqMatrix(const Matrix &other) const noexcept;
  bool operator==(const Matrix &other) const;
  void SumMatrix(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix &operator+=(const Matrix &other);
  void SubMatrix(const Matrix &other);
  Matrix operator-(const Matrix &other) const;
  Matrix &operator-=(const Matrix &other);
  void MulNumber(const double num);
  Matrix operator*(const double num) const;

  Matrix &operator*=(const double num);
  void MulMatrix(const Matrix &other);
  Matrix operator*(const Matrix &other) const;
  Matrix &operator*=(const Matrix &other);
  Matrix Transpose() const;
  double Determinant() const;
  Matrix CalcComplements() const;
  Matrix InverseMatrix() const;

 private:
  void CopyNeeded(const Matrix &other) noexcept;
  void ClearMatrix();
  Matrix Minor(int i, int j) const;

  int rows_, cols_;
  double **matrix_;
};
Matrix operator*(const double num, const Matrix m);
#endif  // MATRIXPLUSPLUS_MATRIX_OOP_H_