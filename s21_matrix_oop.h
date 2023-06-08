#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <exception>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

// Constant EPSILON for Equal
constexpr double EPS = 1e-7;

class S21Matrix {
 private:
  int _rows, _cols;
  double** _matrix;

 public:
  // Constructor and destructor
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  // Accessors
  int get_rows() const;
  int get_cols() const;
  double get_matrix(int row, int col) const;
  // Mutators
  void set_rows(int rows);
  void set_cols(int cols);
  void set_matrix(int row, int col, double num);
  // Helpe functions
  void create_matrix();
  void copy_matrix(const S21Matrix& other);
  void remove_matrix();
  void get_minor(int row, int column);
  bool check_matrix() const;
  bool checkSize_matrix(const S21Matrix& other) const;
  bool checkSquare_matrix() const;
  void resize_matrix(int rows, int cols);

  bool eq_matrix(const S21Matrix& other);
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(const double left, const S21Matrix& right);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double operator()(int row, int col);
};

#endif  // SRC_S21_MATRIX_OOP_H_