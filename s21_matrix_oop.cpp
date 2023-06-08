#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (_rows > 0 && _cols > 0) {
    create_matrix();
  } else {
    throw std::out_of_range("Rows and cols must be great 0");
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) { copy_matrix(other); }

S21Matrix::S21Matrix(S21Matrix&& other)
    : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
  other._matrix = nullptr;
  other._rows = 0;
  other._cols = 0;
}

S21Matrix::~S21Matrix() { remove_matrix(); }

void S21Matrix::create_matrix() {
  if (_rows > 0 && _cols > 0) {
    _matrix = new double*[_rows]();
    for (int i = 0; i < _rows; i++) {
      _matrix[i] = new double[_cols]();
    }
  }
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
  _rows = other._rows;
  _cols = other._cols;
  create_matrix();
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = other._matrix[i][j];
    }
  }
}

void S21Matrix::remove_matrix() {
  if (check_matrix()) {
    for (int i = 0; i < _rows; i++) {
      delete[] _matrix[i];
      _matrix[i] = nullptr;
    }
    delete[] _matrix;
    _matrix = nullptr;
  }
  _rows = 0;
  _cols = 0;
}

int S21Matrix::get_rows() const {
  int result = _rows;
  return result;
}
int S21Matrix::get_cols() const {
  int result = _cols;
  return result;
}

double S21Matrix::get_matrix(int row, int col) const {
  double result;
  if (row < _rows && col < _cols && row >= 0 && col >= 0) {
    result = _matrix[row][col];
  } else {
    throw std::out_of_range(
        "Rows/Cols should be LT than matrix size or GE than 0");
  }
  return result;
}

void S21Matrix::set_rows(int rows) {
  if (rows > 0) {
    resize_matrix(rows, _cols);
  } else {
    throw std::out_of_range("Rows should be GT than 0");
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols > 0) {
    resize_matrix(_rows, cols);
  } else {
    throw std::out_of_range("Cols should be GT than 0");
  }
}

void S21Matrix::set_matrix(int row, int col, double num) {
  if (row >= 0 && col >= 0 && row < _rows && col < _cols) {
    _matrix[row][col] = num;
  } else {
    throw std::out_of_range(
        "Rows/Colss should be GE than 0 and LT than size matrix");
  }
}

void S21Matrix::resize_matrix(int rows, int cols) {
  if (_rows != rows || _cols != cols) {
    S21Matrix tmp(*this);
    remove_matrix();
    _rows = rows;
    _cols = cols;
    create_matrix();
    for (int i = 0; i < std::min(_rows, tmp._rows); i++) {
      for (int j = 0; j < std::min(_cols, tmp._cols); j++) {
        _matrix[i][j] = tmp._matrix[i][j];
      }
    }
    tmp.remove_matrix();
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  sum_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  sub_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  mul_number(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  mul_matrix(other);
  return *this;
}

S21Matrix operator*(const double left, const S21Matrix& right) {
  S21Matrix result(right);
  result.mul_number(left);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (other._matrix != _matrix) {
    remove_matrix();
    copy_matrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  sum_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  sub_matrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  mul_matrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

double S21Matrix::operator()(int row, int col) { return get_matrix(row, col); }

bool S21Matrix::eq_matrix(const S21Matrix& other) {
  bool result = false;
  if (checkSize_matrix(other)) {
    bool flag = false;
    for (int i = 0; i < _rows; i++) {
      if (flag) break;
      for (int j = 0; j < _cols; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j]) < EPS) {
          result = true;
        } else {
          result = false;
          flag = true;
          break;
        }
      }
    }
  }
  return result;
}
void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (checkSize_matrix(other)) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] += other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument("Matrixs should have equal size");
  }
}
void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (checkSize_matrix(other)) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] -= other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument("Matrixs should have equal size");
  }
}

void S21Matrix::mul_number(const double num) {
  if (check_matrix()) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] *= num;
      }
    }
  } else {
    throw std::invalid_argument("Matrix should be really");
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (check_matrix() && other.check_matrix()) {
    if (_cols != other._rows || _matrix == other._matrix) {
      throw std::invalid_argument(
          "Columns matrix A should be equal rows matrix B");
    } else {
      S21Matrix tmp(*this);
      remove_matrix();
      _rows = tmp._rows;
      _cols = other._cols;
      create_matrix();
      for (int i = 0; i < tmp._rows; i++) {
        for (int j = 0; j < other._cols; j++) {
          for (int r = 0; r < tmp._cols; r++) {
            _matrix[i][j] += tmp._matrix[i][r] * other._matrix[r][j];
          }
        }
      }
      tmp.remove_matrix();
    }
  } else {
    throw std::invalid_argument("Matrixs should be really");
  }
}
S21Matrix S21Matrix::transpose() {
  if (check_matrix()) {
    S21Matrix tmp(*this);
    remove_matrix();
    _rows = tmp._cols;
    _cols = tmp._rows;
    create_matrix();
    for (int i = 0; i < tmp._rows; i++) {
      for (int j = 0; j < tmp._cols; j++) {
        _matrix[j][i] = tmp._matrix[i][j];
      }
    }
    tmp.remove_matrix();
  } else {
    throw std::invalid_argument("Matrix should be really");
  }
  return *this;
}

void S21Matrix::get_minor(int row, int column) {
  S21Matrix tmp(*this);
  remove_matrix();
  _rows = tmp._rows - 1;
  _cols = tmp._cols - 1;
  create_matrix();
  int z = 0;
  for (int i = 0; i < tmp._rows; i++) {
    if (i != row) {
      int k = 0;
      for (int j = 0; j < tmp._cols; j++) {
        if (j != column) {
          _matrix[z][k] = tmp._matrix[i][j];
          k++;
        }
      }
      z++;
    }
  }
  tmp.remove_matrix();
}

S21Matrix S21Matrix::calc_complements() {
  S21Matrix tmp(*this);
  if (checkSquare_matrix()) {
    if (_rows == 1) {
      tmp._matrix[0][0] = 1;
    } else {
      for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
          S21Matrix minor(*this);
          minor.get_minor(i, j);
          double number = minor.determinant();
          tmp._matrix[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * number;
          minor.remove_matrix();
        }
      }
    }
  } else {
    tmp.remove_matrix();
    throw std::invalid_argument("Matrix should be square");
  }
  return tmp;
}

double S21Matrix::determinant() {
  double determ = 0.0;
  if (checkSquare_matrix()) {
    if (_rows == 1) {
      determ = _matrix[0][0];
    } else if (_rows == 2) {
      determ += (_matrix[0][0] * _matrix[1][1] - _matrix[1][0] * _matrix[0][1]);
    } else {
      int minus = -1;
      for (int i = 0; i < _rows; i++) {
        S21Matrix minor(*this);
        minor.get_minor(i, 0);
        minus *= -1;
        determ += (minus * _matrix[i][0] * minor.determinant());
      }
    }
  } else {
    throw std::invalid_argument("Matrix should be square");
  }

  return determ;
}

S21Matrix S21Matrix::inverse_matrix() {
  S21Matrix tmp(calc_complements());
  double determinante = this->determinant();
  if (determinante != 0.0) {
    tmp.transpose();
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        tmp._matrix[i][j] = (double)tmp._matrix[i][j] / (double)determinante;
      }
    }
  } else {
    throw std::invalid_argument(
        "Matrix should be square or determinant should be not equal 0");
  }

  return tmp;
}

bool S21Matrix::check_matrix() const {
  bool result = false;
  if (_rows > 0 && _cols > 0 && _matrix != nullptr) {
    result = true;
  }
  return result;
}

bool S21Matrix::checkSquare_matrix() const {
  bool result = false;
  if (check_matrix()) {
    if (_rows == _cols) {
      result = true;
    }
  }
  return result;
}

bool S21Matrix::checkSize_matrix(const S21Matrix& other) const {
  bool result = false;
  if (check_matrix() && other.check_matrix()) {
    if (_rows == other._rows && _cols == other._cols) {
      result = true;
    }
  }
  return result;
}