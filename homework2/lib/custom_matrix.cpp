#include "custom_matrix.h"
#include "custom_vector.h"

#include <stdexcept>
// #include <algorithm>


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

CustomMatrix::CustomMatrix(const std::vector<std::vector <double>> &rhs) {
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

size_t CustomMatrix::num_rows() const {
    return _num_rows;
}

size_t CustomMatrix::num_cols() const {
    return _num_cols;
}

double &CustomMatrix::elem(size_t i, size_t j) {
    return _data[i * _num_cols + j];
}

const double &CustomMatrix::elem(size_t i, size_t j) const {
    return _data[i * _num_cols + j];
}

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
