#include "custom_matrix.h"
#include "custom_vector.h"
#include <math.h>
#include <vector>

#include <stdexcept>
#include <algorithm>
#include <iostream>


#define EPS 0.000001

// конструкторы
CustomMatrix::CustomMatrix()
    : _num_rows(0)
    , _num_cols(0)
    , _data(nullptr)
{}

CustomMatrix::CustomMatrix(size_t num_rows, size_t num_cols)
    : _num_rows(num_rows)
    , _num_cols(num_cols)
    , _data(std::make_unique<double[]>(num_rows * num_cols))
{}

CustomMatrix::CustomMatrix(const CustomMatrix &rhs)
    : _num_rows(rhs.num_rows())
    , _num_cols(rhs.num_cols())
    , _data(std::make_unique<double[]>(rhs.num_rows() * rhs.num_cols())) {
    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] = rhs._data[i];
    }
}

CustomMatrix::CustomMatrix(CustomMatrix &&rhs)
    : _num_rows(rhs.num_rows())
    , _num_cols(rhs.num_cols())
    , _data(std::move(rhs._data))
{}

CustomMatrix::CustomMatrix(const std::vector<double> &rhs, size_t num_rows, size_t num_cols) {
    if (num_rows * num_cols != rhs.size()) {
        throw std::invalid_argument("Vector's size and matrix's shape doesn't match!");
    }

    _num_rows = num_rows;
    _num_cols = num_cols;
    _data = std::make_unique<double[]>(num_rows * num_cols);

    for (size_t i = 0; i < num_rows * num_cols; i++) {
        _data[i] = rhs[i];
    }
}

CustomMatrix::CustomMatrix(const std::vector<CustomVector> &rhs) {
    size_t num_rows = rhs.size();
    if (num_rows == 0) {
        throw std::invalid_argument("Zero rows!");
    }

    size_t num_cols = rhs[0].size();

    if (num_cols == 0) {
        throw std::invalid_argument("Zero columns!");
    }

    for (size_t i = 0; i < num_rows; i++) {
        if (rhs[i].size() != num_cols) {
            throw std::invalid_argument("Rows have different sizes!");
        }
    }

    _num_rows = num_rows;
    _num_cols = num_cols;
    _data = std::make_unique<double[]>(_num_rows * _num_cols);

    for (size_t i = 0; i < _num_rows; i++) {
        for (size_t j = 0; j < _num_cols; j++) {
            this->elem(i, j) = rhs[i][j];
        }
    }
}

// метод вывода количества строк и столбцов
size_t CustomMatrix::num_rows() const {
    return _num_rows;
}

size_t CustomMatrix::num_cols() const {
    return _num_cols;
}

// возвращение элементов по  двум индексам
double &CustomMatrix::elem(size_t i, size_t j) {
    return _data[i * _num_cols + j];
}

const double &CustomMatrix::elem(size_t i, size_t j) const {
    return _data[i * _num_cols + j];
}

// присваивание с копированием и перемещением
CustomMatrix &CustomMatrix::operator=(const CustomMatrix &rhs) {
    if (this != &rhs) {
        _num_rows = rhs.num_rows();
        _num_cols = rhs.num_cols();
        _data = std::make_unique<double[]>(_num_rows * _num_cols);

        for (size_t i = 0; i < _num_rows * _num_cols; i++) {
            _data[i] = rhs._data[i];
        }
    }
    return *this;
}

CustomMatrix &CustomMatrix::operator=(CustomMatrix &&rhs) {
    if (this != &rhs) {
        _num_rows = rhs.num_rows();
        _num_cols = rhs.num_rows();
        _data = std::move(rhs._data);
    }
    return *this;
}

// возвращение диагонали, столбца и строки
CustomVector CustomMatrix::get_row(size_t i) const {
    if (i >=_num_rows) {
        throw std::out_of_range("Row index is out of range!");
    }
    CustomVector result {_num_cols};
    for (size_t j = 0; j < _num_cols; j++) {
        result[j] = this->elem(i, j);
    }
    return result;
}

CustomVector CustomMatrix::get_col(size_t j) const {
    if (j >=_num_cols) {
        throw std::out_of_range("Column index is out of range!");
    }
    CustomVector result {_num_rows};

    for (size_t i = 0; i < _num_rows; i++) {
        result[i] = this->elem(i, j);
    }

    return result;
}

CustomVector CustomMatrix::get_diag() const {
    size_t min_size = std::min(_num_rows, _num_cols);
    CustomVector result {min_size};

    for (size_t i = 0; i < min_size; i++) {
        result[i] = this->elem(i, i);
    }

    return result;
}

// унарные операторы
const CustomMatrix &CustomMatrix::operator+() const {
    return *this;
}

CustomMatrix &CustomMatrix::operator+() {
    return *this;
}

CustomMatrix CustomMatrix::operator-() const {
    return (*this) * (-1);
}

// сложение, вычитание и умножение матриц
CustomMatrix &CustomMatrix::operator+=(const CustomMatrix &rhs) {
    if (_num_rows != rhs.num_rows() || _num_cols != rhs.num_cols()) {
        throw std::invalid_argument("Matrixes' sizes doesn't match!");
    }

    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] += rhs._data[i];
    }

    return *this;
}

CustomMatrix &CustomMatrix::operator-=(const CustomMatrix &rhs) {
    if (_num_rows != rhs.num_rows() || _num_cols != rhs.num_cols()) {
        throw std::invalid_argument("Matrixes' sizes doesn't match!");
    }

    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] -= rhs._data[i];
    }

    return *this;
}

CustomMatrix &CustomMatrix::operator*=(const CustomMatrix &rhs) {
    if (_num_rows != rhs.num_rows() || _num_cols != rhs.num_cols()) {
        throw std::invalid_argument("Matrixes' sizes doesn't match!");
    }

    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] *= rhs._data[i];
    }

    return *this;
}

CustomMatrix CustomMatrix::operator+(const CustomMatrix &rhs) const {
    CustomMatrix result {*this};
    result += rhs;
    return result;
}

CustomMatrix CustomMatrix::operator-(const CustomMatrix &rhs) const {
    CustomMatrix result {*this};
    result -= rhs;
    return result;
}

CustomMatrix CustomMatrix::operator*(const CustomMatrix &rhs) const {
    CustomMatrix result {*this};
    result *= rhs;
    return result;
}

// сложение матрицы и вектора
CustomMatrix &CustomMatrix::add_vec(const CustomVector &rhs, size_t axis) {
    if (axis == 0) {
        if (_num_cols != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _num_rows; i++) {
            for (size_t j = 0; j < _num_cols; j++) {
                this->elem(i, j) += rhs[j];
            }
        }

        return *this;
    } else if (axis == 1) {
        if (_num_rows != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _num_rows; i++) {
            for (size_t j = 0; j < _num_cols; j++) {
                this->elem(i, j) += rhs[i];
            }
        }

        return *this;
    } else {
        throw std::invalid_argument("Incorrect axis");
    }
}

CustomMatrix &CustomMatrix::sub_vec(const CustomVector &rhs, size_t axis) {
    if (axis == 0) {
        if (_num_cols != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _num_rows; i++) {
            for (size_t j = 0; j < _num_cols; j++) {
                this->elem(i, j) -= rhs[j];
            }
        }

        return *this;
    } else if (axis == 1) {
        if (_num_rows != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _num_rows; i++) {
            for (size_t j = 0; j < _num_cols; j++) {
                this->elem(i, j) -= rhs[i];
            }
        }

        return *this;
    } else {
        throw std::invalid_argument("Incorrect axis");
    }
}

CustomMatrix CustomMatrix::add(const CustomVector &rhs, size_t axis) const {
    CustomMatrix tmp {*this};
    tmp.add_vec(rhs, axis);
    return tmp;
}

CustomMatrix CustomMatrix::sub(const CustomVector &rhs, size_t axis) const {
    CustomMatrix tmp {*this};
    tmp.sub_vec(rhs, axis);
    return tmp;
}

CustomVector CustomMatrix::dot(const CustomVector &rhs) const {
    if (_num_cols != rhs.size()) {
        throw std::invalid_argument("Vector has incorrect size");
    }

    CustomVector res {_num_rows};

    for (size_t i = 0; i < _num_rows; i++) {
        res[i] = 0;
        for (size_t j = 0; j < _num_cols; j++) {
            res[i] += this->elem(i, j) * rhs[j];
        }
    }

    return res;
}

// сложение, вычитание и умножение на число
CustomMatrix &CustomMatrix::operator+=(const double &rhs) {
    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] += rhs;
    }
    return *this;
}

CustomMatrix &CustomMatrix::operator-=(const double &rhs) {
    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] -= rhs;
    }
    return *this;
}

CustomMatrix &CustomMatrix::operator*=(const double &rhs) {
    for (size_t i = 0; i < _num_rows * _num_cols; i++) {
        _data[i] *= rhs;
    }
    return *this;
}


CustomMatrix CustomMatrix::operator+(const double &rhs) const {
    CustomMatrix result {*this};
    result += rhs;
    return result;
}

CustomMatrix CustomMatrix::operator-(const double &rhs) const {
    CustomMatrix result {*this};
    result -= rhs;
    return result;
}

CustomMatrix CustomMatrix::operator*(const double &rhs) const {
    CustomMatrix result {*this};
    result *= rhs;
    return result;
}

// перемножение матриц
CustomMatrix CustomMatrix::dot(const CustomMatrix &rhs) const {
    if (_num_cols != rhs.num_rows()) {
        throw std::invalid_argument("Sizes does not match!");
    }

    CustomMatrix result {_num_rows, rhs.num_cols()};

    for (size_t i = 0; i < _num_rows; i++) {
        for (size_t j = 0; j < rhs.num_cols(); j++) {
            double sum = 0;
            for (size_t k = 0; k < _num_cols; k++) {
                sum += this->elem(i, k) * rhs.elem(k, j);
            }
            result.elem(i, j) = sum;
        }
    }
    return result;
}

// транспонирование, определитель и вычисление обратной матрицы
CustomMatrix CustomMatrix::T() const {
    CustomMatrix result {_num_cols, _num_rows};

    for (size_t i = 0; i < _num_cols; i++) {
        for (size_t j = 0; j < _num_rows; j++) {
            result.elem(i, j) = this->elem(j, i);
        }
    }
    return result;
}

CustomMatrix CustomMatrix::inv() const {
    if (_num_rows != _num_cols) {
        throw std::invalid_argument("Matrix is not square, so it cannot be inversed!");
    }
    size_t n = _num_rows;

    CustomMatrix eye {n, n};
    for (size_t i = 0; i < n; i++) {
        eye.elem(i, i) = 1;
    }

    CustomMatrix matr_and_eye {n, 2 * n};
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            matr_and_eye.elem(i, j) = this->elem(i, j);
            matr_and_eye.elem(i, j + n) = eye.elem(i, j);
        }
    }

    for (size_t i = 0; i < n; i++) {
        size_t cur_row_num = i;
        for (size_t j = i + 1; j < n; j++) {
            if (fabs(matr_and_eye.elem(j, i)) > fabs(matr_and_eye.elem(cur_row_num, i))) {
                cur_row_num = j;
            }
        }

        matr_and_eye._swap_rows(i, cur_row_num);

        double cur = matr_and_eye.elem(i, i);
        if (fabs(cur) < EPS) {
            throw std::invalid_argument("Matrix has zero determinant, so it cannot be inversed!");
        }
        for (size_t j = i; j < matr_and_eye.num_cols(); j++) {
            matr_and_eye.elem(i, j) /= cur;
        }
        for (size_t j = 0; j < n; j++) {
            if (j != i && fabs(matr_and_eye.elem(j, i)) > EPS) {
                cur = matr_and_eye.elem(j, i);
                for (size_t l = i; l < matr_and_eye.num_cols(); l++) {
                    matr_and_eye.elem(j, l) -= matr_and_eye.elem(i, l) * cur;
                }
            }
        }
    }

    CustomMatrix result {n, n};
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result.elem(i, j) = matr_and_eye.elem(i, n + j);
        }
    }
    return result;
}

double CustomMatrix::det() const {
    if (_num_rows != _num_cols) {
        throw std::invalid_argument("Matrix has incorrent shape");
    }
    size_t n = _num_rows;
    CustomMatrix matr {*this};

    double det = 1;
    for (size_t i = 0; i < n; i++) {
        size_t cur_row_num = i;

        for (size_t j = i + 1; j < n; j++) {
            if (fabs(matr.elem(j, i)) > fabs(matr.elem(cur_row_num, i))) {
                cur_row_num = j;
            }
        }

        if (fabs(matr.elem(cur_row_num, i)) < EPS) {
            return 0;
        }

        matr._swap_rows(i, cur_row_num);

        if (i != cur_row_num) {
            det *= -1;
        }

        det *= matr.elem(i, i);

        double cur = matr.elem(i, i);
        for (size_t j = i; j < n; j ++) {
            matr.elem(i, j) /= cur;
        }

        for (size_t j = 0; j < n; j++) {
            if (j != i && fabs(matr.elem(j, i)) > EPS) {
                for (size_t l = i + 1; l < n; l++) {
                    matr.elem(j, l) -= matr.elem(i, l) * matr.elem(j, i);
                }
            }
        }
    }
    return det;
}

CustomMatrix operator+(const double &lhs, const CustomMatrix &rhs) {
    return rhs + lhs;
}

CustomMatrix operator-(const double &lhs, const CustomMatrix &rhs) {
    return -(rhs - lhs);
}

CustomMatrix operator*(const double &lhs, const CustomMatrix &rhs) {
    return rhs * lhs;
}

CustomMatrix CustomMatrix::_swap_rows(size_t i, size_t j) {
    for (size_t k = 0; k < _num_cols; k++) {
        double tmp = this->elem(i, k);
        this->elem(i, k) = this->elem(j, k);
        this->elem(j, k) = tmp;
    }
    return *this;
}
