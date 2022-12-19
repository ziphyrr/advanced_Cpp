#include "custom_vector.h"
#include "custom_matrix.h"
#include <gtest/gtest.h>

#define EPS 0.000001

TEST(custom_vector, constructor_by_size) {
    CustomVector vec {5};
    EXPECT_EQ(vec.size(), 5);

    for (size_t i = 0; i < vec.size(); i++)
    {
        EXPECT_NEAR(vec[i], 0, EPS);
    }
}

TEST(custom_vector, constructor_by_vector) {
    CustomVector vec {{1, 0.5, 2, 0.25, -2}};
    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 1, EPS);
    EXPECT_NEAR(vec[1], 0.5, EPS);
    EXPECT_NEAR(vec[2], 2, EPS);
    EXPECT_NEAR(vec[3], 0.25, EPS);
    EXPECT_NEAR(vec[4], -2, EPS);
}

TEST(custom_vector, constructor_by_vector_copy) {
    CustomVector vec {{1, 0.5, 2, 0.25, -2}};
    CustomVector vec_copy {vec};
    EXPECT_EQ(5, vec_copy.size());

    EXPECT_NEAR(vec_copy[0], 1, EPS);
    EXPECT_NEAR(vec_copy[1], 0.5, EPS);
    EXPECT_NEAR(vec_copy[2], 2, EPS);
    EXPECT_NEAR(vec_copy[3], 0.25, EPS);
    EXPECT_NEAR(vec_copy[4], -2, EPS);
}

TEST(custom_vector, constructor_by_operator) {
    CustomVector vec {{1, 0.5, 2, 0.25, -2}};
    CustomVector vec_copy;
    vec_copy = vec;
    EXPECT_EQ(5, vec_copy.size());

    EXPECT_NEAR(vec_copy[0], 1, EPS);
    EXPECT_NEAR(vec_copy[1], 0.5, EPS);
    EXPECT_NEAR(vec_copy[2], 2, EPS);
    EXPECT_NEAR(vec_copy[3], 0.25, EPS);
    EXPECT_NEAR(vec_copy[4], -2, EPS);
}

TEST(custom_vector, operator_plus_equal) {
    CustomVector vec = CustomVector({1, 0.5, 2, 0.25, -2});

    vec += CustomVector({1, 0, 2, -1, 2});

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 2, EPS);
    EXPECT_NEAR(vec[1], 0.5, EPS);
    EXPECT_NEAR(vec[2], 4, EPS);
    EXPECT_NEAR(vec[3], -0.75, EPS);
    EXPECT_NEAR(vec[4], 0, EPS);

    vec += 5;

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 7, EPS);
    EXPECT_NEAR(vec[1], 5.5, EPS);
    EXPECT_NEAR(vec[2], 9, EPS);
    EXPECT_NEAR(vec[3], 4.25, EPS);
    EXPECT_NEAR(vec[4], 5, EPS);
}

TEST(custom_vector, operator_minus_equal) {
    CustomVector vec = CustomVector({1, 0.5, 2, 0.25, -2});

    vec -= CustomVector({1, 0, 2, -1, 2});

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 0, EPS);
    EXPECT_NEAR(vec[1], 0.5, EPS);
    EXPECT_NEAR(vec[2], 0, EPS);
    EXPECT_NEAR(vec[3], 1.25, EPS);
    EXPECT_NEAR(vec[4], -4, EPS);

    vec -= 5;

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], -5, EPS);
    EXPECT_NEAR(vec[1], -4.5, EPS);
    EXPECT_NEAR(vec[2], -5, EPS);
    EXPECT_NEAR(vec[3], -3.75, EPS);
    EXPECT_NEAR(vec[4], -9, EPS);
}

TEST(custom_vector, operator_mult_equal) {
    CustomVector vec = CustomVector({1, 0.5, 2, 0.25, -2});

    vec *= CustomVector({1, 0, 2, -1, 2});

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 1, EPS);
    EXPECT_NEAR(vec[1], 0, EPS);
    EXPECT_NEAR(vec[2], 4, EPS);
    EXPECT_NEAR(vec[3], -0.25, EPS);
    EXPECT_NEAR(vec[4], -4, EPS);

    vec *= 5;

    EXPECT_EQ(5, vec.size());

    EXPECT_NEAR(vec[0], 5, EPS);
    EXPECT_NEAR(vec[1], 0, EPS);
    EXPECT_NEAR(vec[2], 20, EPS);
    EXPECT_NEAR(vec[3], -1.25, EPS);
    EXPECT_NEAR(vec[4], -20, EPS);
}

TEST(vector, dot_matrix) {
    CustomVector vec {{1, 3}};
    CustomMatrix matr {{1, 2, 0, 1, 0, 3, 1, 1}, 2, 4};
    CustomVector res_vec = vec.dot(matr);
    EXPECT_EQ(4, res_vec.size());
    EXPECT_NEAR(res_vec[0], 1, EPS);
    EXPECT_NEAR(res_vec[1], 11, EPS);
    EXPECT_NEAR(res_vec[2], 3, EPS);
    EXPECT_NEAR(res_vec[3], 4, EPS);
}
