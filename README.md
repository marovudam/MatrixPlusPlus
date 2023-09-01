# MatrixPlusPlus
_My first C++ project_

Implementation of Matrix library with C++ object-oriented approach.
- C++17 version
- Compiler used: g++
- Gtest library used for testing
- Coverage check with gcovr & lcov
- C++ Google Style Guide followed *(or so i think)*

### Makefile targets
- `make all` and `make matrix_oop.a` builds static library `matrix_oop.a`
- `make clean` removes anything produced by any target
- `make test` builds and runs tests
- `make coverage` forms and opens html coverage report
- `make leak` checks compiled tests for possible memory leaks (`leaks` utility used). _**In some cases Gtest exception assertions (`ASSERT_THROW`) may leak by 16 bytes. This is the common thing and I do not know how to fix it**_ 
- `make style` formats code to satisfy Google Style. You probably do not not need this one

### List of private fields
| Field | Type | Description |
|-|-|-|
| `rows_` | integer | Number of rows (equal or greater than zero) |
| `cols_` | integer | Number of colums (equal or greater than zero) |
| `double **matrix_` | Nested double array | `rows_ * cols` matrix |

### List of methods
| Method | Descrition |
|--------|------------|
| `Matrix()` | Non-parametrized constructor. Creates `0*0` matrix|
| `Matrix(int rows, int cols)` | Parametrized constructor. Creates Matrix with `rows*cols` dimentions |
| `Matrix(const Matrix &other)` | Copy constructor |
| `Matrix(Matrix &&other)` | Move constructor |
| `Matrix &operator=(const Matrix &other)` | Copy assigment operator |
| `Matrix &operator=(Matrix &&other)` | Move assigment operator |
| `~Matrix()` | Destructor |
| `int get_rows()` | Accessor for the `rows_` field |
| `int get_cols()` | Accessor for the `cols_` field |
| `void set_rows(int rows)` | Mutator for the `rows_` field |
| `void set_cols(int cols)` | Mutator for the `cols_` field |
| `double &operator()(int i, int j)` | Overload of `()` operator; acts as both mutator and accessor for individual matrix elements |
| `bool EqMatrix(const Matrix &other)` | Checks matrices for equality with each other |
| `bool operator==(const Matrix &other)` | Operator of `==` operator, checks matrices for equality |
| `void SumMatrix(const Matrix &other)` | Adds `other` matrix to the current one |
| `Matrix operator+(const Matrix &other)` | Overload of `+` operator. Returns the result of addition of current and `other` matrices |
| `Matrix &operator+=(const Matrix &other)` | Overloal of `+=` operator. Returns the result of addition of current and `other` matrices |
| `void SubMatrix(const Matrix &other)` | Substracts `other` matrix from the current one |
| `Matrix operator-(const Matrix &other)` | Overload of `-` operator. Returns the result of substraction `other` matrix from the current one |
| `Matrix &operator-=(const Matrix &other)` | Overload of `-=` operator. Returns the result of substraction `other` matrix from the current one |
| `void MulNumber(const double num)` | Multiplies current matrix by `num` |
| `Matrix operator*(const double num)` | Returns the result of multiplication of current matrix and `num` |
| `Matrix &operator*=(const double num)` | Overload of multiplication assigment operator (Multiplies matrix by number) |
| `void MulMatrix(const Matrix &other)` | Multiplies current and `other` matrices |
| `Matrix operator*(const Matrix &other)` | Returns the result of multiplication current matrix by matrix `other` |
| `Matrix &operator*=(const Matrix &other)` | Overload of multiplication assigment operator (Multiplies two matrices) |
| `Matrix Transpose()` | Returns transposed matrix | 
| `double Determinant()` | Calculates matrix determinant (Gaussian elimination is used; No-recursion method) |
| `Matrix CalcComplements()` | Calculates cofactor matrix |
| `Matrix InverseMatrix()` | Calculates invertible matrix |
