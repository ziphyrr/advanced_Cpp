#include "set.h"
#include <gtest/gtest.h>
#include <vector>

// BLOCK 1: constructors

//Set();
//Set(InputIt first, InputIt last);
//Set(std::initializer_list<T> l);
//Set(const Set &rhs);

TEST(set, default_constructor) {
    Set <int> a;
    EXPECT_EQ(1, a.empty());
    EXPECT_EQ(0, a.size());

    //basic functionality
    a.insert(2);
    a.insert(3);
    a.insert(1);
    a.insert(0);

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(0, a.empty());

    auto it = a.begin();
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(it, a.end());
}

TEST(set, iter_constructor) {
    std::vector <int> v = {3, 1, 2, 0, 5, 6, -1};
    Set <int> a {v.begin(), v.end()};
    auto it = a.begin();
    EXPECT_EQ(*it++, -1);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 5);
    EXPECT_EQ(*it++, 6);
    EXPECT_EQ(it, a.end());
}

TEST(set, list_constructor) {
    Set <int> a = {3, 1, 2, 0, 5, 6, -1};
    auto it = a.begin();
    EXPECT_EQ(*it++, -1);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 5);
    EXPECT_EQ(*it++, 6);
    EXPECT_EQ(it, a.end());
}

TEST(set, from_set_constructor) {
    Set <int> a = {3, 1, 2, 0, 5, 6, -1};
    Set <int> b = a;
    auto it = b.begin();
    EXPECT_EQ(*it++, -1);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 5);
    EXPECT_EQ(*it++, 6);
    EXPECT_EQ(it, b.end());
}

TEST(set, copy_operator) {
    Set <int> a = {3, 1, 2, 0, 5, 6, -1};
    Set <int> b;
    b = a;
    auto it = b.begin();
    EXPECT_EQ(*it++, -1);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 5);
    EXPECT_EQ(*it++, 6);
    EXPECT_EQ(it, b.end());
}

// BLOCK 2: iterator

//set begin, end and ++, --, =, ==, !=

TEST(set, iter_begin_end_and_operators) {
    std::vector <int> v = {3, 1, 2, 0};
    Set <int> a = {v.begin(), v.end()};
    auto it = a.begin();
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(it, a.end());

    EXPECT_EQ(*--it, 3);
    EXPECT_EQ(*--it, 2);
    EXPECT_EQ(*--it, 1);
    EXPECT_EQ(*--it, 0);
    EXPECT_EQ(it, a.begin());

    EXPECT_EQ(*++it, 1);
    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*++it, 3);
    EXPECT_EQ(++it, a.end());

    it--;
    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*it--, 2);
    EXPECT_EQ(*it--, 1);
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(it, a.begin());

    EXPECT_EQ(it == a.begin(), 1);
    EXPECT_EQ(it != a.begin(), 0);

    EXPECT_EQ(it == a.end(), 0);
    EXPECT_EQ(it != a.end(), 1);

}

// BLOCK 2: set methods

//set insert, erase, size, empty
//find, lower_bound

TEST(set, insert_erase_and_size_empty) {
    Set <int> a;
    EXPECT_EQ(1, a.empty());
    EXPECT_EQ(0, a.size());

    a.insert(1);
    a.insert(6);
    a.insert(4);
    a.insert(9);
    a.insert(5);
    a.erase(4);
    a.erase(3);
    a.erase(1);

    EXPECT_EQ(0, a.empty());
    EXPECT_EQ(3, a.size());

    a.erase(5);
    a.erase(9);
    a.erase(6);

    EXPECT_EQ(1, a.empty());
    EXPECT_EQ(0, a.size());
}

TEST(set, find_and_lower_bound) {
    std::vector <int> v = {1, 2, 3};
    Set <int> a {v.begin(), v.end()};
    auto it = a.begin();
    EXPECT_EQ(a.find(1), it);
    it++;
    EXPECT_EQ(a.find(2), it);
    EXPECT_EQ(*(a.lower_bound(0)), 1);
    EXPECT_EQ(a.find(3), --a.end());
}
