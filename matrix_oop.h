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

  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);
  double &operator()(int i, int j);
  bool EqMatrix(const Matrix &other) noexcept;
  bool operator==(const Matrix &other);
  void SumMatrix(const Matrix &other);
  Matrix operator+(const Matrix &other);
  Matrix &operator+=(const Matrix &other);
  void SubMatrix(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  void MulNumber(const double num);
  Matrix operator*(const double num);

  Matrix &operator*=(const double num);
  void MulMatrix(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix Transpose();
  double Determinant();
  // need to check this one (1*1 matrix)
  Matrix CalcComplements();
  Matrix InverseMatrix();

 private:
  void CopyNeeded(const Matrix &other) noexcept;
  void ClearMatrix();
  Matrix Minor(int i, int j);

  int rows_, cols_;
  double **matrix_;
};
Matrix operator*(const double num, const Matrix m);
#endif  // MATRIXPLUSPLUS_MATRIX_OOP_H_