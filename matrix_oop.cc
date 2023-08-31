#include "matrix_oop.h"

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Negative matrix dimentions");
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  int i = 0;
  try {
    for (i = 0; i < rows; i++) {
      matrix_[i] = new double[cols_]{};
    }
  } catch (...) {
    for (int j = 0; j < i; j++) delete[] matrix_[j];
    delete[] matrix_;
    throw;
  }
}

Matrix::Matrix(const Matrix &other)
    : Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    Matrix temp_m(other.rows_, other.cols_);
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++)
        temp_m.matrix_[i][j] = other.matrix_[i][j];
    }
    *this = std::move(temp_m);
  }
  return *this;
}

Matrix::Matrix(Matrix &&other) noexcept : Matrix() {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    ClearMatrix();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

Matrix::~Matrix() { ClearMatrix(); }

void Matrix::ClearMatrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

int Matrix::get_rows() { return rows_; }

int Matrix::get_cols() { return cols_; }

void Matrix::CopyNeeded(const Matrix &other) noexcept {
  int rows = std::min(rows_, other.rows_);
  int cols = std::min(cols_, other.cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}

void Matrix::set_rows(int rows) {
  if (rows > 0) {
    Matrix new_m(rows, cols_);
    new_m.CopyNeeded(*this);
    ClearMatrix();
    *this = std::move(new_m);
  }
}

void Matrix::set_cols(int cols) {
  if (cols > 0) {
    Matrix new_m(rows_, cols);
    new_m.CopyNeeded(*this);
    ClearMatrix();
    *this = std::move(new_m);
  }
}

bool Matrix::EqMatrix(const Matrix &other) noexcept {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > kPrecision)
          return false;
      }
    }
    return true;
  }
  return false;
}

bool Matrix::operator==(const Matrix &other) {
  return this->EqMatrix(other);
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Different matrix dimensions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Different matrix dimensions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

Matrix Matrix::operator+(const Matrix &other) {
  Matrix ans(other);
  ans.SumMatrix(*this);
  return ans;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix ans(*this);
  ans.SubMatrix(other);
  return ans;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  *this = *this + other;
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  *this = *this - other;
  return *this;
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
}

Matrix &Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

Matrix Matrix::operator*(const double num) {
  Matrix ans(*this);
  ans.MulNumber(num);
  return ans;
}

Matrix operator*(const double num, const Matrix m) {
  Matrix result = m;
  result *= num;
  return result;
}

Matrix Matrix::operator*(const Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument("Wrong matrix dimensions");
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  Matrix result = *this * other;
  *this = result;
  return *this;
}

void Matrix::MulMatrix(const Matrix &other) { *this *= other; }

Matrix Matrix::Transpose() {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("Matrix must be square");
  Matrix triangle(*this);
  double determinant = 1.0;
  int rows_change = 1;
  for (int i = 0; i < rows_; i++) {
    int i_max = i;
    for (int j = i + 1; j < rows_; j++) {
      if (std::abs(triangle.matrix_[j][i]) >
          std::abs(triangle.matrix_[i_max][i]))
        i_max = j;
    }
    if (std::abs(triangle.matrix_[i_max][i]) > kPrecision) {
      for (int k = 0; k < rows_; k++)
        std::swap(triangle.matrix_[i][k], triangle.matrix_[i_max][k]);
      if (i != i_max) rows_change = -rows_change;
      for (int j = i + 1; j < rows_; j++) {
        double coef = -triangle.matrix_[j][i] / triangle.matrix_[i][i];
        for (int k = rows_ - 1; k >= i; k--)
          triangle.matrix_[j][k] += coef * triangle.matrix_[i][k];
      }
    }
    if (std::abs(triangle.matrix_[i][i]) < kPrecision)
      triangle.matrix_[i][i] = 0;
    determinant *= triangle.matrix_[i][i];
  }
  return determinant * rows_change;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::invalid_argument("Matrix must be square");
  Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result.matrix_[i][j] =
            Minor(i, j).Determinant() * (((i + j + 1) % 2) * 2 - 1);
  }
  return result;
}

Matrix Matrix::Minor(int i, int j) {
  Matrix result(rows_ - 1, cols_ - 1);
  for (int k = 0, m = 0; k < rows_, m < result.rows_; k++, m++) {
    if (k == i) k++;
    for (int l = 0, n = 0; l < cols_, n < result.cols_; l++, n++) {
      if (l == j) l++;
      result.matrix_[m][n] = matrix_[k][l];
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::invalid_argument("Matrix must be square");
  double determinant = Determinant();
  if (determinant < kPrecision)
    throw std::invalid_argument("Determinant equals zero");
  Matrix result(Transpose().CalcComplements() * (1 / determinant));
  return result;
}

double &Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || i < 0 || j < 0)
    throw std::invalid_argument("Index out of borders");
  return matrix_[i][j];
}