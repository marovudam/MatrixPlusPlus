#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(ConstructorTest, WrongBounds) {
  ASSERT_THROW(Matrix(3, -1), std::invalid_argument);
}

TEST(ConstructorTest, MoveConstructor) {
  Matrix m1(2, 3);
  m1(0, 0) = 10.0;
  m1(0, 1) = 189.0;
  m1(0, 2) = -123.0;
  m1(1, 0) = 1289.0;
  m1(1, 1) = 63489.92;
  m1(1, 2) = -218.1207;
  Matrix m2(m1);
  Matrix m3(std::move(m1));
  ASSERT_TRUE(m2 == m3);
}

TEST(ResizeMatrixTest, ResizeDown) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(1, 0) = 1289.0;
  m(1, 1) = 63489.92;
  m(1, 2) = -218.1207;
  m.set_rows(1);
  m.set_cols(2);
  Matrix m2(1, 2);
  m2(0, 0) = 10.0;
  m2(0, 1) = 189.0;
  ASSERT_TRUE(m.EqMatrix(m2));
  ASSERT_TRUE(m.get_rows() == 1);
  ASSERT_TRUE(m.get_cols() == 2);
}

TEST(ResizeMatrixTest, ResizeUp) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(1, 0) = 1289.0;
  m(1, 1) = 63489.92;
  m(1, 2) = -218.1207;
  m.set_rows(5);
  m.set_cols(4);
  Matrix m2(5, 4);
  m2(0, 0) = 10.0;
  m2(0, 1) = 189.0;
  m2(0, 2) = -123.0;
  m2(1, 0) = 1289.0;
  m2(1, 1) = 63489.92;
  m2(1, 2) = -218.1207;
  ASSERT_TRUE(m.EqMatrix(m2));
  ASSERT_TRUE(m.get_rows() == 5);
  ASSERT_TRUE(m.get_cols() == 4);
}

TEST(SumMatrixTest, SimpleSum) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 18.0;
  m(0, 2) = -13.0;
  m(1, 0) = 6.0;
  m(1, 1) = -2.0;
  m(1, 2) = 1.0;
  Matrix m2(2, 3);
  m2(0, 0) = 1.0;
  m2(0, 1) = 8.0;
  m2(0, 2) = 3.0;
  m2(1, 0) = -6.0;
  m2(1, 1) = 0.0;
  m2(1, 2) = 1.0;
  Matrix answer(2, 3);
  answer(0, 0) = 11.0;
  answer(0, 1) = 26.0;
  answer(0, 2) = -10.0;
  answer(1, 0) = 0.0;
  answer(1, 1) = -2.0;
  answer(1, 2) = 2.0;
  Matrix m_copy = m;
  m.SumMatrix(m2);
  ASSERT_TRUE(m.EqMatrix(answer));
  Matrix result = m_copy + m2;
  ASSERT_TRUE(answer == result);
  m_copy += m2;
  ASSERT_TRUE(m_copy == result);
}

TEST(SumMatrixTest, BadSum) {
  Matrix m(2, 3);
  Matrix m2(3, 2);
  ASSERT_THROW(Matrix m3 = m + m2, std::invalid_argument);
}

TEST(SubMatrixTest, SimpleSub) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 18.0;
  m(0, 2) = -13.0;
  m(1, 0) = 6.0;
  m(1, 1) = -2.0;
  m(1, 2) = 1.0;
  Matrix m2(2, 3);
  m2(0, 0) = 1.0;
  m2(0, 1) = 8.0;
  m2(0, 2) = 3.0;
  m2(1, 0) = -6.0;
  m2(1, 1) = 0.0;
  m2(1, 2) = 1.0;
  Matrix answer(2, 3);
  answer(0, 0) = 9.0;
  answer(0, 1) = 10.0;
  answer(0, 2) = -16.0;
  answer(1, 0) = 12.0;
  answer(1, 1) = -2.0;
  answer(1, 2) = 0.0;
  Matrix m_copy = m;
  m.SubMatrix(m2);
  ASSERT_TRUE(m.EqMatrix(answer));
  Matrix result = m_copy - m2;
  ASSERT_TRUE(answer == result);
  m_copy -= m2;
  ASSERT_TRUE(m_copy == result);
}

TEST(SubMatrixTest, BadSub) {
  Matrix m(2, 3);
  Matrix m2(3, 2);
  ASSERT_THROW(Matrix m3 = m - m2, std::invalid_argument);
}

TEST(MulNumberTest, MulNum) {
  Matrix m(2, 3);
  double k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) m(i, j) = k++;
  m.MulNumber(2.0);
  k = 1.0;
  Matrix answer(2, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) answer(i, j) = (k++) * 2;
  ASSERT_TRUE(m.EqMatrix(answer));
}

TEST(MulNumberTest, MulFriend) {
  Matrix m(2, 3);
  double k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) m(i, j) = k++;
  Matrix m2 = m * 2.0;
  Matrix m3 = 2.0 * m;
  m *= 2.0;
  Matrix answer(2, 3);
  k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) answer(i, j) = (k++) * 2;
  ASSERT_TRUE(answer == m);
  ASSERT_TRUE(answer == m2);
  ASSERT_TRUE(answer == m3);
}

TEST(MulMatrixTest, MulOperator) {
  Matrix m1(3, 2);
  Matrix m2(2, 4);
  double k = 1.0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) m1(i, j) = k++;
  k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) m2(i, j) = k++;
  Matrix m3 = m1 * m2;
  Matrix answer(3, 4);
  answer(0, 0) = 11.0;
  answer(0, 1) = 14.0;
  answer(0, 2) = 17.0;
  answer(0, 3) = 20.0;
  answer(1, 0) = 23.0;
  answer(1, 1) = 30.0;
  answer(1, 2) = 37.0;
  answer(1, 3) = 44.0;
  answer(2, 0) = 35.0;
  answer(2, 1) = 46.0;
  answer(2, 2) = 57.0;
  answer(2, 3) = 68.0;
  ASSERT_TRUE(m3 == answer);
}

TEST(MulMatrixTest, MulOperator2) {
  Matrix m1(3, 2);
  Matrix m2(2, 4);
  double k = 1.0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) m1(i, j) = k++;
  k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) m2(i, j) = k++;
  m1 *= m2;
  Matrix answer(3, 4);
  answer(0, 0) = 11.0;
  answer(0, 1) = 14.0;
  answer(0, 2) = 17.0;
  answer(0, 3) = 20.0;
  answer(1, 0) = 23.0;
  answer(1, 1) = 30.0;
  answer(1, 2) = 37.0;
  answer(1, 3) = 44.0;
  answer(2, 0) = 35.0;
  answer(2, 1) = 46.0;
  answer(2, 2) = 57.0;
  answer(2, 3) = 68.0;
  ASSERT_TRUE(m1 == answer);
}

TEST(MulMatrixTest, MulFunction) {
  Matrix m1(3, 2);
  Matrix m2(2, 4);
  double k = 1.0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) m1(i, j) = k++;
  k = 1.0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) m2(i, j) = k++;
  m1.MulMatrix(m2);
  Matrix answer(3, 4);
  answer(0, 0) = 11.0;
  answer(0, 1) = 14.0;
  answer(0, 2) = 17.0;
  answer(0, 3) = 20.0;
  answer(1, 0) = 23.0;
  answer(1, 1) = 30.0;
  answer(1, 2) = 37.0;
  answer(1, 3) = 44.0;
  answer(2, 0) = 35.0;
  answer(2, 1) = 46.0;
  answer(2, 2) = 57.0;
  answer(2, 3) = 68.0;
  ASSERT_TRUE(m1 == answer);
}

TEST(MulMatrixTest, BadMul) {
  Matrix m(2, 4);
  Matrix m2(3, 2);
  ASSERT_THROW(m * m2, std::invalid_argument);
}

TEST(TransposeTest, Transpose) {
  Matrix m(2, 4);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(0, 3) = 1289.0;
  m(1, 0) = 63489.92;
  m(1, 1) = -218.1207;
  m(1, 2) = 18.2;
  m(1, 3) = 219.123;
  Matrix m2 = m.Transpose();
  Matrix answer(4, 2);
  answer(0, 0) = 10.0;
  answer(0, 1) = 63489.92;
  answer(1, 0) = 189.0;
  answer(1, 1) = -218.1207;
  answer(2, 0) = -123.0;
  answer(2, 1) = 18.2;
  answer(3, 0) = 1289.0;
  answer(3, 1) = 219.123;
  ASSERT_TRUE(m2 == answer);
}

TEST(DeterminantTest, DetZero) {
  Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;
  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

TEST(DeterminantTest, Det) {
  Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 10;
  EXPECT_DOUBLE_EQ(m.Determinant(), -3.0);
}

TEST(DeterminantTest, Det2) {
  Matrix m(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 0;
  m(1, 0) = 1;
  m(1, 1) = 0;
  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

TEST(DeterminantTest, Det3) {
  Matrix m(5, 5);
  m(0, 0) = 6;
  m(0, 1) = 8;
  m(0, 2) = 6;
  m(0, 3) = 7;
  m(0, 4) = 1;
  m(1, 0) = 0;
  m(1, 1) = 3;
  m(1, 2) = 5;
  m(1, 3) = 8;
  m(1, 4) = 5;
  m(2, 0) = 2;
  m(2, 1) = 1;
  m(2, 2) = 9;
  m(2, 3) = 7;
  m(2, 4) = 5;
  m(3, 0) = 2;
  m(3, 1) = 5;
  m(3, 2) = 4;
  m(3, 3) = 3;
  m(3, 4) = 9;
  m(4, 0) = 0;
  m(4, 1) = 3;
  m(4, 2) = 2;
  m(4, 3) = 5;
  m(4, 4) = 8;
  EXPECT_DOUBLE_EQ(m.Determinant(), -3306.0);
}

TEST(DeterminantTest, DetError) {
  Matrix m(3, 4);
  ASSERT_THROW(m.Determinant(), std::invalid_argument);
}

TEST(ComplementsTest, Complements1) {
  Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 2;
  m(2, 0) = 5;
  m(2, 1) = 2;
  m(2, 2) = 1;
  Matrix answer(3, 3);
  answer(0, 0) = 0;
  answer(0, 1) = 10;
  answer(0, 2) = -20;
  answer(1, 0) = 4;
  answer(1, 1) = -14;
  answer(1, 2) = 8;
  answer(2, 0) = -8;
  answer(2, 1) = -2;
  answer(2, 2) = 4;
  ASSERT_TRUE(m.CalcComplements() == answer);
}

TEST(ComplementsTest, ComplementsSmall) {
  Matrix m(1, 1);
  m(0, 0) = 1;
  Matrix answer(1, 1);
  answer(0, 0) = 1;
  ASSERT_TRUE(m.CalcComplements() == answer);
}

TEST(ComplementsTest, CompError) {
  Matrix m(3, 4);
  ASSERT_THROW(m.CalcComplements(), std::invalid_argument);
}

TEST(InverseTest, InverseMatrix) {
  Matrix m(3, 3);
  m(0, 0) = -1;
  m(0, 1) = 2;
  m(0, 2) = -2;
  m(1, 0) = 2;
  m(1, 1) = -1;
  m(1, 2) = 5;
  m(2, 0) = 3;
  m(2, 1) = -2;
  m(2, 2) = 4;
  Matrix answer(3, 3);

  answer(0, 0) = 0.6;
  answer(0, 1) = -0.4;
  answer(0, 2) = 0.8;
  answer(1, 0) = 0.7;
  answer(1, 1) = 0.2;
  answer(1, 2) = 0.1;
  answer(2, 0) = -0.1;
  answer(2, 1) = 0.4;
  answer(2, 2) = -0.3;
  ASSERT_TRUE(m.InverseMatrix() == answer);
}

TEST(InverseTest, InverseMatrixSmall) {
  Matrix m(1, 1);
  m(0, 0) = 5.0;
  Matrix answer(1, 1);
  answer(0, 0) = 1.0;
  ASSERT_TRUE(m.InverseMatrix() == answer);
}

TEST(InverseTest, InverseError) {
  Matrix m(3, 4);
  ASSERT_THROW(m.InverseMatrix(), std::invalid_argument);
}

TEST(OperatorTest, Brackets) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(1, 0) = 1289.0;
  m(1, 1) = 63489.92;
  m(1, 2) = -218.1207;
  ASSERT_TRUE(std::abs(m(1, 2) - (-218.1207)) < Matrix().kPrecision);
}

TEST(OperatorTest, OutOfBounds) {
  Matrix m(2, 4);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(1, 0) = 1289.0;
  m(1, 1) = 63489.92;
  m(1, 2) = -218.1207;
  ASSERT_THROW(m(9, 0), std::invalid_argument);
}

TEST(EqTest, Equal) {
  Matrix m(2, 3);
  m(0, 0) = 10.0;
  m(0, 1) = 189.0;
  m(0, 2) = -123.0;
  m(1, 0) = 1289.0;
  m(1, 1) = 63489.92;
  m(1, 2) = -218.1207;
  Matrix m2(m);
  ASSERT_TRUE(m == m2);
  ASSERT_TRUE(m.EqMatrix(m2));
  m2(0, 0) = 0.0;
  ASSERT_FALSE(m == m2);
  ASSERT_FALSE(m.EqMatrix(m2));
  m2(0, 0) = 10.0;
  m2.set_rows(5);
  ASSERT_FALSE(m == m2);
  ASSERT_FALSE(m.EqMatrix(m2));
}
