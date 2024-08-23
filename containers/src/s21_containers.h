#ifndef S21_CONTAINERS_MAIN_H_
#define S21_CONTAINERS_MAIN_H_

#include <gtest/gtest.h>

#include <chrono>
#include <initializer_list>
#include <iostream>
#include <list>
#include <queue>
#include <string>

#include "list/s21_list.h"
#include "queue/s21_queue.h"
// #include "vector/s21_vector.h"
// #include "array/s21_array.h"
// #include "stack/s21_stack.h"
// #include "map/s21_map.h"
// #include "set/s21_set.h"
// #include "multiset/s21_multiset.h"

/***************************************************************************/

template <typename T>
class QueueComparisonTest : public testing::Test {
 protected:
  s21::queue<T> myQueue;
  std::queue<T> stdQueue;
};

using TestTypes = testing::Types<short int, int, long, long long, float, double,
                                 long double, char>;
TYPED_TEST_SUITE(QueueComparisonTest, TestTypes);

TYPED_TEST(QueueComparisonTest, DefaultConstructor) {
  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

/***************************************************************************/

template <typename T>
class ListComparisonTest : public testing::Test {
 protected:
  s21::list<T> myList;
  std::list<T> stdList;
};

using TestTypes = testing::Types<short int, int, long, long long, float, double,
                                 long double, char>;
TYPED_TEST_SUITE(ListComparisonTest, TestTypes);

TYPED_TEST(ListComparisonTest, DefaultConstructor) {
  ASSERT_EQ(this->myList.size(), this->stdList.size());
}

/***************************************************************************/

#endif