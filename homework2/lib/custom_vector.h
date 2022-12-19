#pragma once // NOLINT

#include <vector>
#include <memory>

class CustomMatrix;

class CustomVector {
 public:
    // конструкторы
    CustomVector();
    explicit CustomVector(size_t size);
    CustomVector(const CustomVector &rhs);
    CustomVector(CustomVector &&rhs);
    explicit CustomVector(const std::vector<double> &rhs);

    // метод size
    size_t size() const;

    // оператор обращения по индексу
    double &operator[](size_t i);
    const double &operator[](size_t i) const;

    // оператор присваивания
    CustomVector &operator=(const CustomVector &rhs);
    CustomVector &operator=(CustomVector &&rhs);

    // унарные операторы
    const CustomVector &operator+() const;
    CustomVector &operator+();
    CustomVector operator-() const;


    // операторы += и подобные для вектора и числа
    CustomVector &operator+=(const double &rhs);
    CustomVector &operator-=(const double &rhs);
    CustomVector &operator*=(const double &rhs);

    // операторы += и подобные для двух векторов
    CustomVector &operator+=(const CustomVector &rhs);
    CustomVector &operator-=(const CustomVector &rhs);
    CustomVector &operator*=(const CustomVector &rhs);

    // операторы сложения и подобные для вектора и числа
    CustomVector operator+(const double &rhs) const;
    CustomVector operator-(const double &rhs) const;
    CustomVector operator*(const double &rhs) const;

    // операторы сложения и подобные для двух векторов
    CustomVector operator+(const CustomVector &rhs) const;
    CustomVector operator-(const CustomVector &rhs) const;
    CustomVector operator*(const CustomVector &rhs) const;

    CustomVector dot(const CustomMatrix &rhs) const;
 private:
    size_t _size;
    std::unique_ptr<double[]> _data;
};

CustomVector operator+(const double &lhs, const CustomVector &rhs);
CustomVector operator-(const double &lhs, const CustomVector &rhs);
CustomVector operator*(const double &lhs, const CustomVector &rhs);
