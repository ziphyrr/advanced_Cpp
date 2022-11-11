#include <iostream>
#include "custom_vector.h"
#include <stdexcept>

CustomVector::CustomVector()
    : _size(0)
    , _data(nullptr)
{}

CustomVector::CustomVector(const size_t size)
    : _size(size)
    , _data(std::make_unique<double[]>(size))
{}

CustomVector::CustomVector(const CustomVector &rhs)
    : _size(rhs._size)
    , _data(std::make_unique<double[]>(rhs._size)) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs._data[i];
    }
}

CustomVector::CustomVector(CustomVector &&rhs)
    : _size(rhs._size)
    , _data(std::make_unique<double[]>(rhs._size))

{}

CustomVector::CustomVector(const std::vector<double> &rhs)
    : _size(rhs.size())
    , _data(std::make_unique<double[]>(rhs.size())) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs[i];
    }
}

size_t CustomVector::size() const {
    return _size;
}

double &CustomVector::operator[](size_t i) {
    if (i >= _size) {
        throw std::out_of_range("Vector index is out of range!");
    } else {
        return _data[i];
    }
}

const double &CustomVector::operator[](size_t i) const {
    if (i >= _size) {
        throw std::out_of_range("Vector index is out of range!");
    } else {
        return _data[i];
    }
}

CustomVector &CustomVector::operator=(const CustomVector &rhs) {
    if (this != &rhs) {
        _size = rhs._size;
        _data = std::make_unique<double[]>(rhs._size);
        for (size_t i = 0; i < _size; i++) {
            _data[i] = rhs._data[i];
        }
    }
    return *this;
}

CustomVector &CustomVector::operator=(CustomVector &&rhs) {
    if (this != &rhs) {
        _size = rhs._size;
        _data = std::move(rhs._data);
    }
    return *this;
}

CustomVector &CustomVector::operator+=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] += rhs;
    }

    return *this;
}

CustomVector &CustomVector::operator-=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] -= rhs;
    }

    return *this;
}

CustomVector &CustomVector::operator*=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] *= rhs;
    }

    return *this;
}

CustomVector &CustomVector::operator+=(const CustomVector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Sizes doesn't match!");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] += rhs._data[i];
    }

    return *this;
}

CustomVector &CustomVector::operator-=(const CustomVector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Sizes doesn't match!");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] -= rhs._data[i];
    }

    return *this;
}

CustomVector &CustomVector::operator*=(const CustomVector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Sizes doesn't match!");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] *= rhs._data[i];
    }

    return *this;
}

CustomVector CustomVector::operator+(const double &rhs) const {
    CustomVector result {*this};
    result += rhs;
    return result;
}

CustomVector CustomVector::operator-(const double &rhs) const {
    CustomVector result {*this};
    result -= rhs;
    return result;
}

CustomVector CustomVector::operator*(const double &rhs) const {
    CustomVector result {*this};
    result *= rhs;
    return result;
}

CustomVector CustomVector::operator+(const CustomVector &rhs) const {
    CustomVector result {*this};
    result += rhs;
    return result;
}

CustomVector CustomVector::operator-(const CustomVector &rhs) const {
    CustomVector result {*this};
    result -= rhs;
    return result;
}

CustomVector CustomVector::operator*(const CustomVector &rhs) const {
    CustomVector result {*this};
    result *= rhs;
    return result;
}
