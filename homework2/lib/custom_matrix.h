#pragma once // NOLINT

#include <memory>
#include <vector>

class CustomVector;

class CustomMatrix {
 public:
    // конструкторы
    CustomMatrix();
    CustomMatrix(size_t num_rows, size_t num_cols);
    CustomMatrix(const CustomMatrix &rhs);
    CustomMatrix(CustomMatrix &&rhs);
    CustomMatrix(const std::vector<double> &rhs, size_t num_rows, size_t num_cols);
    explicit CustomMatrix(const std::vector<std::vector <double>> &rhs);

    // метод вывода количества строк и столбцов
    size_t num_rows() const;
    size_t num_cols() const;

    // возвращение элементов по  двум индексам
    double &elem(size_t i, size_t j);
    const double &elem(size_t i, size_t j) const;

    // присваивание с копированием и перемещением
    CustomMatrix &operator=(const CustomMatrix &rhs);
    CustomMatrix &operator=(CustomMatrix &&rhs);

    // возвращение диагонали, столбца и строки
    CustomVector get_row(size_t i) const;
    CustomVector get_col(size_t j) const;
    CustomVector get_diag() const;

    // сложение и вычитание матриц
    CustomMatrix &operator+=(const CustomMatrix &rhs);
    CustomMatrix &operator-=(const CustomMatrix &rhs);
    CustomMatrix operator+(const CustomMatrix &rhs) const;
    CustomMatrix operator-(const CustomMatrix &rhs) const;

    // сложение, вычитание и умножение на число
    CustomMatrix &operator+=(const double &rhs);
    CustomMatrix &operator-=(const double &rhs);
    CustomMatrix &operator*=(const double &rhs);
    CustomMatrix operator+(const double &rhs) const;
    CustomMatrix operator-(const double &rhs) const;
    CustomMatrix operator*(const double &rhs) const;


 private:
    size_t _num_rows;
    size_t _num_cols;
    std::unique_ptr<double[]> _data;
};
