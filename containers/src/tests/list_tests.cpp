#include "../s21_containers.h"

/*
 *
 *
 *
 *
 *
 *
 *    CLASS LIST : CONSTRUCTS
 *
 *
 *
 *
 *
 *
 */

TEST(ConstructorTest, DEFAULT_CONSTRUCTOR) {
  s21::list<int> test_list;
  EXPECT_EQ(test_list.getHead(), nullptr);
}

TEST(ConstructorTest, CREATED_LIST_IN_SIZE_N) {
  int numTest = 10;
  s21::list<int> test_list(numTest);
  int num = 0;

  for (const auto &element : test_list) {
    if (element == 0) {
      num++;
    }
  }

  EXPECT_EQ(numTest, num);
}

TEST(ConstructorTest, INIT_LIST) {
  int size = 5;
  int sizeTest = 0;
  s21::list<int> test_list = {1, 2, 3, 4, 5};

  for (auto it = test_list.begin(), it_end = test_list.end(); it != it_end;
       ++it) {
    // std::cout << element;
    sizeTest++;
  }

  EXPECT_EQ(size, sizeTest);
}

TEST(ConstructorTest, COPY_LIST) {
  s21::list<int> originalList = {1, 2, 3, 4, 5};

  s21::list<int> copiedList = originalList;

  std::string origList;
  std::string copList;

  for (const auto &element : originalList) {
    origList += std::to_string(element) + " ";
  }

  for (const auto &element : copiedList) {
    copList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}

TEST(ConstructorTest, MOVE_DATA_LIST) {
  std::string origList;
  std::string copList;

  s21::list<int> originalList = {1, 2, 3, 4, 5};

  for (const auto &element : originalList) {
    origList += std::to_string(element) + " ";
  }

  s21::list<int> newList(std::move(originalList));

  for (const auto &element : newList) {
    copList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}

/*
 *
 *
 *
 *
 *
 *
 *    CLASS LIST : METHODS
 *
 *
 *
 *
 *
 *
 */

TEST(MethodsTestList, clear) {
  s21::list<int> test_list = {1, 2, 3, 4, 5};

  test_list.clear();

  EXPECT_EQ(test_list.getHead(), nullptr);
}

TEST(MethodsTestList, insert) {
  s21::list<int> test_list = {1, 2, 3, 4, 5};
  std::string origList;
  std::string newString = "1 2 666 3 4 5 ";

  s21::list<int>::iterator it = test_list.begin();
  it++;
  it++;
  test_list.insert(it, 666);

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }
  EXPECT_EQ(origList, newString);
}

TEST(MethodsTestList, erase) {
  s21::list<int> test_list = {1, 2, 3, 4, 5};
  std::string origList;
  std::string newString = "1 2 4 5 ";

  s21::list<int>::iterator it = test_list.begin();
  it++;
  it++;
  test_list.erase(it);

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }
  EXPECT_EQ(origList, newString);
}

TEST(MethodsTestList, push_back) {
  std::string origList;
  std::string copList = "0 0 0 0 0 10 ";

  s21::list<int> test_list(5);
  test_list.push_back(10);

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}

TEST(MethodsTestList, push_front) {
  std::string origList;
  std::string copList = "10 0 0 0 0 0 ";

  s21::list<int> test_list(5);
  test_list.push_front(10);

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}
TEST(MethodsTestList, pop_front) {
  std::string origList;
  std::string copList = "2 3 ";

  s21::list<int> test_list = {1, 2, 3};
  test_list.pop_front();

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}
TEST(MethodsTestList, pop_back) {
  std::string origList;
  std::string copList = "1 2 ";

  s21::list<int> test_list = {1, 2, 3};
  test_list.pop_back();

  for (const auto &element : test_list) {
    origList += std::to_string(element) + " ";
  }

  EXPECT_EQ(origList, copList);
}

TEST(MethodsTestList, swap) {
  s21::list<int> test_list1 = {1, 2, 3};
  s21::list<int> test_list2 = {4, 5, 6};
  std::string origList = "1 2 3 ";
  std::string origList2;
  std::string copList = "4 5 6 ";
  std::string copList2;

  test_list1.swap(test_list2);

  for (const auto &element : test_list1) {
    origList2 += std::to_string(element) + " ";
  }

  for (const auto &element : test_list2) {
    copList2 += std::to_string(element) + " ";
  }

  EXPECT_EQ(copList, origList2);
  EXPECT_EQ(origList, copList2);
}

TEST(MethodsTestList, merge) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6};

  list1.merge(list2);

  std::string res = "1 2 3 4 5 6 ";
  std::string result;
  for (const auto &item : list1) {
    result += std::to_string(item) + " ";
  }

  EXPECT_EQ(res, result);
}

TEST(MethodsTestList, splice) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  std::string resultTRUE = "1 4 5 6 2 3 ";
  std::string result;

  auto it = list1.c_begin();
  ++it;
  list1.splice(it, list2);

  for (const auto &item : list1) {
    result += std::to_string(item) + " ";
  }

  std::list<int> list1RRR = {1, 2, 3};
  std::list<int> list2RRR = {4, 5, 6};
  std::string resultTRUERRR = "1 4 5 6 2 3 ";
  std::string resultRRR;

  auto itR = list1RRR.begin();
  ++itR;
  list1RRR.splice(itR, list2RRR);

  for (const auto &item : list1RRR) {
    resultRRR += std::to_string(item) + " ";
  }

  EXPECT_EQ(result, resultRRR);
  EXPECT_TRUE(list2.empty());
}

TEST(MethodsTestList, reverse) {
  s21::list<int> list1 = {1, 2, 3, 4, 5};
  std::string resultTRUE = "5 4 3 2 1 ";
  std::string result;

  list1.reverse();

  for (const auto &item : list1) {
    result += std::to_string(item) + " ";
  }

  EXPECT_EQ(resultTRUE, result);
}

TEST(MethodsTestList, unique) {
  s21::list<int> list1 = {1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 5};
  std::string resultTRUE = "1 2 3 4 5 ";
  std::string result;

  list1.unique();

  for (const auto &item : list1) {
    result += std::to_string(item) + " ";
  }

  EXPECT_EQ(resultTRUE, result);
}

TEST(MethodsTestList, sort) {
  s21::list<int> list1 = {1, 2, 2, 3, 4, 33, 24, 75, 5, 5, 5};

  list1.sort();
  std::string resultTRUE = "1 2 2 3 4 5 5 5 24 33 75 ";
  std::string result;

  for (const auto &item : list1) {
    result += std::to_string(item) + " ";
  }
  EXPECT_EQ(resultTRUE, result);
}

TEST(ListTest, SortWithHeadSwap) {
  s21::list<int> myList = {2, 1, 3};
  myList.sort();
  std::vector<int> expected = {1, 2, 3};
  auto it = myList.begin();
  for (int num : expected) {
    ASSERT_EQ(*it, num);
    ++it;
  }
}
TEST(ListTest, SpliceEmptyIntoNonEmpty) {
  s21::list<int> myList = {1, 2, 3};
  s21::list<int> emptyList;
  myList.splice(myList.c_begin(), emptyList);
  ASSERT_TRUE(myList.size() == 3);
}
TEST(ListTest, SpliceAtBeginning) {
  s21::list<int> myList = {1, 2, 3};
  s21::list<int> otherList = {4, 5, 6};
  myList.splice(myList.c_begin(), otherList);
  ASSERT_EQ(myList.front(), 4);
}
TEST(ListTest, MergeFirstListEndsEarly) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6, 7, 8};
  list1.merge(list2);
  ASSERT_TRUE(list1.size() == 8);
}
TEST(ListTest, PopBackWithSingleElement) {
  s21::list<int> myList = {1};
  myList.pop_back();
  ASSERT_TRUE(myList.empty());
}
TEST(ListTest, PushFrontToEmptyList) {
  s21::list<int> myList;
  myList.push_front(5);
  ASSERT_EQ(myList.front(), 5);
}
TEST(ListTest, EraseFirstElement) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  myList.erase(it);
  ASSERT_EQ(myList.front(), 2);
}

TEST(ListTest, InsertIntoEmptyList) {
  s21::list<int> myList;
  try {
    myList.insert(myList.begin(), 5);
    ASSERT_EQ(myList.front(), 5);
  } catch (const std::invalid_argument &e) {
  }
}

TEST(ListTest, InsertIntoMiddleOfList) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(4);
  auto it = myList.begin();
  ++it;
  myList.insert(it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
}

TEST(ListTest, InsertIntoInvalidPosition) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  auto it = myList.end();
  ASSERT_THROW(myList.insert(it, 3), std::invalid_argument);
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

TYPED_TEST(ListComparisonTest, ParameterizedConstructor) {
  const size_t size = 5;

  s21::list<TestTypes> myList(size);
  std::list<TestTypes> stdList(size);

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, ParameterizedConstructor2) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, CopyConstructor) {
  s21::list<TypeParam> original = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdOriginal = {1, 2, 3, 4, 5};

  s21::list<TypeParam> myList(original);
  std::list<TypeParam> stdList(stdOriginal);

  ASSERT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}

TYPED_TEST(ListComparisonTest, MoveConstructor) {
  s21::list<TypeParam> original = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdOriginal = {1, 2, 3, 4, 5};

  s21::list<TypeParam> myList(std::move(original));
  std::list<TypeParam> stdList(std::move(stdOriginal));

  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_TRUE(original.empty());
  ASSERT_TRUE(stdOriginal.empty());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}
TYPED_TEST(ListComparisonTest, MoveAssignmentOperator) {
  s21::list<TypeParam> original = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdOriginal = {1, 2, 3, 4, 5};

  s21::list<TypeParam> myList;
  std::list<TypeParam> stdList;

  myList = std::move(original);
  stdList = std::move(stdOriginal);

  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_TRUE(original.empty());
  ASSERT_TRUE(stdOriginal.empty());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}

TYPED_TEST(ListComparisonTest, FrontMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.front(), stdList.front());

  s21::list<TypeParam> emptyList;
  ASSERT_THROW(emptyList.front(), std::out_of_range);
}

TYPED_TEST(ListComparisonTest, BackMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.back(), stdList.back());

  s21::list<TypeParam> emptyList;
  ASSERT_THROW(emptyList.back(), std::out_of_range);
}

TYPED_TEST(ListComparisonTest, BeginMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(*myList.begin(), *stdList.begin());
}

TYPED_TEST(ListComparisonTest, EndMethodA) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();

  while (myIt != myList.end() && stdIt != stdList.end()) {
    ASSERT_EQ(*myIt, *stdIt);
    ++myIt;
    ++stdIt;
  }
}

TYPED_TEST(ListComparisonTest, EmptyMethod) {
  s21::list<TypeParam> emptyList;
  std::list<TypeParam> stdEmptyList;

  ASSERT_EQ(emptyList.empty(), stdEmptyList.empty());

  s21::list<TypeParam> myList = {1};
  std::list<TypeParam> stdList = {1};

  ASSERT_EQ(myList.empty(), stdList.empty());
}

TYPED_TEST(ListComparisonTest, SizeMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, MaxSizeMethod) {
  s21::list<TypeParam> myList;
  std::list<TypeParam> stdList;

  ASSERT_TRUE(myList.max_size() > 0);
  ASSERT_TRUE(stdList.max_size() > 0);

  ASSERT_TRUE(myList.max_size() <= std::numeric_limits<size_t>::max());
  ASSERT_TRUE(stdList.max_size() <= std::numeric_limits<size_t>::max());
}

TYPED_TEST(ListComparisonTest, ClearMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  myList.clear();
  stdList.clear();

  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_TRUE(myList.empty() && stdList.empty());
}

TYPED_TEST(ListComparisonTest, InsertMethod) {
  s21::list<TypeParam> myList = {1, 2, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 4, 5};

  auto myIt = myList.insert(++myList.begin(), 3);
  auto stdIt = stdList.insert(++stdList.begin(), 3);

  ASSERT_EQ(*myIt, *stdIt);
  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, EraseMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};

  myList.erase(++myList.begin());
  stdList.erase(++stdList.begin());

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, PushBackMethod) {
  s21::list<TypeParam> myList;
  std::list<TypeParam> stdList;

  myList.push_back(1);
  stdList.push_back(1);

  ASSERT_EQ(myList.back(), stdList.back());
  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, PopBackMethod) {
  s21::list<TypeParam> myList = {1, 2, 3};
  std::list<TypeParam> stdList = {1, 2, 3};

  myList.pop_back();
  stdList.pop_back();

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, PushFrontMethod) {
  s21::list<TypeParam> myList;
  std::list<TypeParam> stdList;

  myList.push_front(1);
  stdList.push_front(1);

  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, PopFrontMethod) {
  s21::list<TypeParam> myList = {1, 2, 3};
  std::list<TypeParam> stdList = {1, 2, 3};

  myList.pop_front();
  stdList.pop_front();

  ASSERT_EQ(myList.size(), stdList.size());
}

TYPED_TEST(ListComparisonTest, SwapMethod) {
  s21::list<TypeParam> myList = {1, 2, 3};
  s21::list<TypeParam> myOtherList = {4, 5, 6};
  std::list<TypeParam> stdList = {1, 2, 3};
  std::list<TypeParam> stdOtherList = {4, 5, 6};

  myList.swap(myOtherList);
  stdList.swap(stdOtherList);

  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myOtherList.size(), stdOtherList.size());
}

TYPED_TEST(ListComparisonTest, MergeMethod) {
  s21::list<TypeParam> myList = {1, 3, 5};
  s21::list<TypeParam> otherList = {2, 4, 6};
  myList.merge(otherList);

  std::list<TypeParam> stdList = {1, 3, 5};
  std::list<TypeParam> stdOtherList = {2, 4, 6};
  stdList.merge(stdOtherList);

  ASSERT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}

TYPED_TEST(ListComparisonTest, ReverseMethod) {
  s21::list<TypeParam> myList = {1, 2, 3, 4, 5};
  myList.reverse();

  std::list<TypeParam> stdList = {1, 2, 3, 4, 5};
  stdList.reverse();

  ASSERT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}

TYPED_TEST(ListComparisonTest, UniqueMethod) {
  s21::list<TypeParam> myList = {1, 1, 2, 2, 3, 3};
  myList.unique();

  std::list<TypeParam> stdList = {1, 1, 2, 2, 3, 3};
  stdList.unique();

  ASSERT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();
  for (; myIt != myList.end() && stdIt != stdList.end(); ++myIt, ++stdIt) {
    ASSERT_EQ(*myIt, *stdIt);
  }
}

TYPED_TEST(ListComparisonTest, MoveAssignmentOperatorFAWF) {
  // Create a temporary object with some data
  s21::list<TypeParam> temp_list = {1, 2, 3, 4, 5};

  s21::list<TypeParam> myList;

  ASSERT_TRUE(myList.empty());

  myList = std::move(temp_list);

  ASSERT_EQ(myList.size(), 5u);
  for (TypeParam i = 1; i <= 5; ++i) {
    ASSERT_EQ(myList.front(), i);
    myList.pop_front();
  }

  ASSERT_NO_THROW(temp_list.size());

  std::list<TypeParam> std_temp_list = {1, 2, 3, 4, 5};
  std::list<TypeParam> stdList;
  stdList = std::move(std_temp_list);

  ASSERT_EQ(stdList.size(), 5u);
  for (TypeParam i = 1; i <= 5; ++i) {
    ASSERT_EQ(stdList.front(), i);
    stdList.pop_front();
  }

  ASSERT_TRUE(std_temp_list.empty());
}

/*
 * BONUS METHODS
 */

TYPED_TEST(ListComparisonTest, InsertManyIntoMiddleOfList) {
  s21::list<TypeParam> myList;
  myList.push_back(1);
  myList.push_back(5);
  auto it = myList.c_begin();
  ++it;
  myList.insert_many(it, 2, 3, 4);
  it = myList.c_begin();
  for (int i = 1; i <= 5; ++i, ++it) {
    ASSERT_EQ(*it, i);
  }
}

TYPED_TEST(ListComparisonTest, InsertManyBack) {
  s21::list<TypeParam> myList;
  myList.insert_many_back(1, 2, 3, 4, 5);
  auto it = myList.begin();
  for (int i = 1; i <= 5; ++i, ++it) {
    ASSERT_EQ(*it, i);
  }
}

TYPED_TEST(ListComparisonTest, InsertManyFront) {
  s21::list<TypeParam> myList;
  myList.insert_many_front(5, 4, 3, 2, 1);
  auto it = myList.begin();
  for (int i = 1; i <= 5; ++i, ++it) {
    ASSERT_EQ(*it, i);
  }
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//
//   return RUN_ALL_TESTS();
// }