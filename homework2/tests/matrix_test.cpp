#include "custom_vector.h"
#include "custom_matrix.h"
#include <gtest/gtest.h>

#define EPS 0.000001

TEST(custom_matrix, constructor_by_size) {
    CustomMatrix matr {5, 4};
    EXPECT_EQ(matr.num_rows(), 5);
    EXPECT_EQ(matr.num_cols(), 4);

    for (size_t i = 0; i < matr.num_rows(); i++) {
        for (size_t j = 0; j < matr.num_cols(); j++) {
            EXPECT_NEAR(matr.elem(i, j), 0, EPS);
        }
    }
}

TEST(custom_matrix, constructor_by_vector_and_shape) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    EXPECT_EQ(3, matr.num_rows());
    EXPECT_EQ(2, matr.num_cols());

    EXPECT_NEAR(matr.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr.elem(0, 1), 3, EPS);
    EXPECT_NEAR(matr.elem(1, 0), -4, EPS);
    EXPECT_NEAR(matr.elem(1, 1), 5, EPS);
    EXPECT_NEAR(matr.elem(2, 0), 0, EPS);
    EXPECT_NEAR(matr.elem(2, 1), 6, EPS);
}

TEST(custom_matrix, constructor_by_vector_and_shape_copy) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomMatrix matr_copy {matr};
    EXPECT_EQ(3, matr_copy.num_rows());
    EXPECT_EQ(2, matr_copy.num_cols());

    EXPECT_NEAR(matr_copy.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr_copy.elem(0, 1), 3, EPS);
    EXPECT_NEAR(matr_copy.elem(1, 0), -4, EPS);
    EXPECT_NEAR(matr_copy.elem(1, 1), 5, EPS);
    EXPECT_NEAR(matr_copy.elem(2, 0), 0, EPS);
    EXPECT_NEAR(matr_copy.elem(2, 1), 6, EPS);
}

TEST(custom_matrix, constructor_by_operator) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomMatrix matr_copy;
    matr_copy = matr;
    EXPECT_EQ(3, matr_copy.num_rows());
    EXPECT_EQ(2, matr_copy.num_cols());

    EXPECT_NEAR(matr_copy.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr_copy.elem(0, 1), 3, EPS);
    EXPECT_NEAR(matr_copy.elem(1, 0), -4, EPS);
    EXPECT_NEAR(matr_copy.elem(1, 1), 5, EPS);
    EXPECT_NEAR(matr_copy.elem(2, 0), 0, EPS);
    EXPECT_NEAR(matr_copy.elem(2, 1), 6, EPS);

    matr_copy.elem(0, 1) = 5;
    EXPECT_NEAR(matr_copy.elem(0, 1), 5, EPS);
    EXPECT_NEAR(matr.elem(0, 1), 3, EPS);
}

TEST(custom_matrix, constructor_by_vectors) {
    CustomVector v1 {{1, 5}};
    CustomVector v2 {{3, 0}};
    CustomVector v3 {{-4, 6}};

    CustomMatrix matr {{v1, v2, v3}};
    EXPECT_EQ(3, matr.num_rows());
    EXPECT_EQ(2, matr.num_cols());

    EXPECT_NEAR(matr.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr.elem(0, 1), 5, EPS);
    EXPECT_NEAR(matr.elem(1, 0), 3, EPS);
    EXPECT_NEAR(matr.elem(1, 1), 0, EPS);
    EXPECT_NEAR(matr.elem(2, 0), -4, EPS);
    EXPECT_NEAR(matr.elem(2, 1), 6, EPS);
}

TEST(custom_matrix, get_row_col_diag) {
    CustomVector v1 {{1, 5}};
    CustomVector v2 {{3, 0}};
    CustomVector v3 {{-4, 6}};

    CustomMatrix matr {{v1, v2, v3}};

    CustomVector col0 {{1, 3, -4}};
    CustomVector col1 {{5, 0, 6}};
    CustomVector diag {{1, 0}};

    for (size_t i = 0; i < matr.num_cols(); i++) {
        EXPECT_NEAR(matr.get_row(0)[i], v1[i], EPS);
        EXPECT_NEAR(matr.get_row(1)[i], v2[i], EPS);
        EXPECT_NEAR(matr.get_row(2)[i], v3[i], EPS);
    }

    for (size_t i = 0; i < matr.num_rows(); i++) {
        EXPECT_NEAR(matr.get_col(0)[i], col0[i], EPS);
        EXPECT_NEAR(matr.get_col(1)[i], col1[i], EPS);
    }

    for (size_t i = 0; i < std::min(matr.num_rows(), matr.num_cols()); i++) {
        EXPECT_NEAR(matr.get_diag()[i], diag[i], EPS);
    }
}

TEST(custom_matrix, operator_matrix_matrix) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomMatrix rhs_matr {{1, 0, -1, 1, 1, 2}, 3, 2};

    CustomMatrix matr_sum {matr + rhs_matr};
    CustomMatrix matr_sub {matr - rhs_matr};
    CustomMatrix matr_mult {matr * rhs_matr};

    EXPECT_NEAR(matr_sum.elem(0, 0), 2, EPS);
    EXPECT_NEAR(matr_sum.elem(0, 1), 3, EPS);
    EXPECT_NEAR(matr_sum.elem(1, 0), -5, EPS);
    EXPECT_NEAR(matr_sum.elem(1, 1), 6, EPS);
    EXPECT_NEAR(matr_sum.elem(2, 0), 1, EPS);
    EXPECT_NEAR(matr_sum.elem(2, 1), 8, EPS);

    EXPECT_NEAR(matr_sub.elem(0, 0), 0, EPS);
    EXPECT_NEAR(matr_sub.elem(0, 1), 3, EPS);
    EXPECT_NEAR(matr_sub.elem(1, 0), -3, EPS);
    EXPECT_NEAR(matr_sub.elem(1, 1), 4, EPS);
    EXPECT_NEAR(matr_sub.elem(2, 0), -1, EPS);
    EXPECT_NEAR(matr_sub.elem(2, 1), 4, EPS);

    EXPECT_NEAR(matr_mult.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr_mult.elem(0, 1), 0, EPS);
    EXPECT_NEAR(matr_mult.elem(1, 0), 4, EPS);
    EXPECT_NEAR(matr_mult.elem(1, 1), 5, EPS);
    EXPECT_NEAR(matr_mult.elem(2, 0), 0, EPS);
    EXPECT_NEAR(matr_mult.elem(2, 1), 12, EPS);
}

TEST(custom_matrix, operator_matrix_vector) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomVector rhs_vec_row {{1, 2}};
    CustomVector rhs_vec_col {{1, 2, 3}};

    CustomMatrix matr_sum_row {matr};
    matr_sum_row.add_vec(rhs_vec_row, 0);
    CustomMatrix matr_sum_col {matr};
    matr_sum_col.add_vec(rhs_vec_col, 1);

    EXPECT_NEAR(matr_sum_row.elem(0, 0), 2, EPS);
    EXPECT_NEAR(matr_sum_row.elem(0, 1), 5, EPS);
    EXPECT_NEAR(matr_sum_row.elem(1, 0), -3, EPS);
    EXPECT_NEAR(matr_sum_row.elem(1, 1), 7, EPS);
    EXPECT_NEAR(matr_sum_row.elem(2, 0), 1, EPS);
    EXPECT_NEAR(matr_sum_row.elem(2, 1), 8, EPS);

    EXPECT_NEAR(matr_sum_col.elem(0, 0), 2, EPS);
    EXPECT_NEAR(matr_sum_col.elem(0, 1), 4, EPS);
    EXPECT_NEAR(matr_sum_col.elem(1, 0), -2, EPS);
    EXPECT_NEAR(matr_sum_col.elem(1, 1), 7, EPS);
    EXPECT_NEAR(matr_sum_col.elem(2, 0), 3, EPS);
    EXPECT_NEAR(matr_sum_col.elem(2, 1), 9, EPS);

    CustomMatrix matr_sub_row {matr};
    matr_sub_row.sub_vec(rhs_vec_row, 0);
    CustomMatrix matr_sub_col {matr};
    matr_sub_col.sub_vec(rhs_vec_col, 1);

    EXPECT_NEAR(matr_sub_row.elem(0, 0), 0, EPS);
    EXPECT_NEAR(matr_sub_row.elem(0, 1), 1, EPS);
    EXPECT_NEAR(matr_sub_row.elem(1, 0), -5, EPS);
    EXPECT_NEAR(matr_sub_row.elem(1, 1), 3, EPS);
    EXPECT_NEAR(matr_sub_row.elem(2, 0), -1, EPS);
    EXPECT_NEAR(matr_sub_row.elem(2, 1), 4, EPS);

    EXPECT_NEAR(matr_sub_col.elem(0, 0), 0, EPS);
    EXPECT_NEAR(matr_sub_col.elem(0, 1), 2, EPS);
    EXPECT_NEAR(matr_sub_col.elem(1, 0), -6, EPS);
    EXPECT_NEAR(matr_sub_col.elem(1, 1), 3, EPS);
    EXPECT_NEAR(matr_sub_col.elem(2, 0), -3, EPS);
    EXPECT_NEAR(matr_sub_col.elem(2, 1), 3, EPS);
}

TEST(custom_matrix, operator_matrix_double) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomMatrix matr_add {1 + matr + 1};
    CustomMatrix matr_sub {1 - matr + 1};
    CustomMatrix matr_mult {2 * matr * 2};

    EXPECT_NEAR(matr_add.elem(0, 0), 3, EPS);
    EXPECT_NEAR(matr_add.elem(0, 1), 5, EPS);
    EXPECT_NEAR(matr_add.elem(1, 0), -2, EPS);
    EXPECT_NEAR(matr_add.elem(1, 1), 7, EPS);
    EXPECT_NEAR(matr_add.elem(2, 0), 2, EPS);
    EXPECT_NEAR(matr_add.elem(2, 1), 8, EPS);

    EXPECT_NEAR(matr_sub.elem(0, 0), 1, EPS);
    EXPECT_NEAR(matr_sub.elem(0, 1), -1, EPS);
    EXPECT_NEAR(matr_sub.elem(1, 0), 6, EPS);
    EXPECT_NEAR(matr_sub.elem(1, 1), -3, EPS);
    EXPECT_NEAR(matr_sub.elem(2, 0), 2, EPS);
    EXPECT_NEAR(matr_sub.elem(2, 1), -4, EPS);

    EXPECT_NEAR(matr_mult.elem(0, 0), 4, EPS);
    EXPECT_NEAR(matr_mult.elem(0, 1), 12, EPS);
    EXPECT_NEAR(matr_mult.elem(1, 0), -16, EPS);
    EXPECT_NEAR(matr_mult.elem(1, 1), 20, EPS);
    EXPECT_NEAR(matr_mult.elem(2, 0), 0, EPS);
    EXPECT_NEAR(matr_mult.elem(2, 1), 24, EPS);
}

TEST(custom_matrix, mult_matrix_vector) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomVector vec {{3, -2}};

    CustomVector result {matr.dot(vec)};

    EXPECT_NEAR(result[0], -3, EPS);
    EXPECT_NEAR(result[1], -22, EPS);
    EXPECT_NEAR(result[2], -12, EPS);
}

TEST(custom_matrix, mult_matrix_matrix) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};
    CustomMatrix matr_rhs {{3, 1, -2, 1}, 2, 2};

    CustomMatrix result {matr.dot(matr_rhs)};

    EXPECT_NEAR(result.elem(0, 0), -3, EPS);
    EXPECT_NEAR(result.elem(0, 1), 4, EPS);
    EXPECT_NEAR(result.elem(1, 0), -22, EPS);
    EXPECT_NEAR(result.elem(1, 1), 1, EPS);
    EXPECT_NEAR(result.elem(2, 0), -12, EPS);
    EXPECT_NEAR(result.elem(2, 1), 6, EPS);
}

TEST(custom_matrix, matrix_transpose) {
    CustomMatrix matr {{1, 3, -4, 5, 0, 6}, 3, 2};

    CustomMatrix result {matr.T()};

    EXPECT_NEAR(result.elem(0, 0), 1, EPS);
    EXPECT_NEAR(result.elem(1, 0), 3, EPS);
    EXPECT_NEAR(result.elem(0, 1), -4, EPS);
    EXPECT_NEAR(result.elem(1, 1), 5, EPS);
    EXPECT_NEAR(result.elem(0, 2), 0, EPS);
    EXPECT_NEAR(result.elem(1, 2), 6, EPS);
}

TEST(custom_matrix, matrix_det) {
    CustomMatrix matr {{1, 2, 0, 0, 3, 1, 1, 1, 1}, 3, 3};

    EXPECT_NEAR(matr.det(), 4, EPS);
}

TEST(custom_matrix, matrix_inverse) {
    CustomMatrix matr {{1, 2, 0, 0, 3, 1, 1, 1, 1}, 3, 3};

    CustomMatrix matr_inv {matr.inv()};

    matr_inv *= 4;

    EXPECT_NEAR(matr_inv.elem(0, 0), 2, EPS);
    EXPECT_NEAR(matr_inv.elem(0, 1), -2, EPS);
    EXPECT_NEAR(matr_inv.elem(0, 2), 2, EPS);
    EXPECT_NEAR(matr_inv.elem(1, 0), 1, EPS);
    EXPECT_NEAR(matr_inv.elem(1, 1), 1, EPS);
    EXPECT_NEAR(matr_inv.elem(1, 2), -1, EPS);
    EXPECT_NEAR(matr_inv.elem(2, 0), -3, EPS);
    EXPECT_NEAR(matr_inv.elem(2, 1), 1, EPS);
    EXPECT_NEAR(matr_inv.elem(2, 2), 3, EPS);
}
