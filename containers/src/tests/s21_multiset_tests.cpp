#include <random>

#include "../multiset/s21_multiset.h"
#include "gtest/gtest.h"

TEST(MultisetDefaultConstuctTest, test1) {
  using namespace s21_containersplus;
  multiset<int> prompt;
  EXPECT_EQ(prompt.empty(), true);
}

TEST(MultisetIninitializerListTest, test2) {
  using namespace s21_containersplus;
  multiset<int> prompt = {2, 1, 3, 1};
  EXPECT_EQ(prompt.size(), 4);
}

TEST(MultisetIninitializerListTest, test3) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {2, 1};
  EXPECT_EQ(prompt.size(), 2);
}

TEST(MultisetIninitializerListTest, test4) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {2, 3};
  EXPECT_EQ(prompt.size(), 2);
}

TEST(MultisetIninitializerListTest, test5) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {5};
  EXPECT_EQ(prompt.size(), 1);
}

TEST(MultisetIninitializerListTest, test6) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(prompt.size(), 6);
}

TEST(MultisetIninitializerListTest, test7) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {6, 5, 4, 3, 2, 1};
  EXPECT_EQ(prompt.size(), 6);
}

TEST(MultisetIninitializerListTest, test8) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {
      10, 1, 5, 3, 2, 4, 8, 7, 9, 6, 18, 13, 25, 22, 11, 15, 12, 16, 17};
  EXPECT_EQ(prompt.size(), 19);
}

TEST(MultisetIninitializerListTest, test9) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt = {
      10, 6,  11, 3,  8,  13, 1,  5,  7,  9,  12, 0, 2,
      4,  18, 16, 22, 15, 17, 20, 23, 19, 21, 25, 26};
  EXPECT_EQ(prompt.size(), 25);
}

TEST(MultisetIninitializerListTest, test10) {
  using namespace s21_containersplus;

  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);
  for (int i = 0; i < 10; ++i) prompt.insert(distr(gen));
  EXPECT_EQ(prompt.size(), 10);
}

TEST(MultisetCopyConstructorTest, test11) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);
  for (int i = 0; i < 10000; ++i) prompt.insert(distr(gen));

  s21_containersplus::multiset<int> prompt2(prompt);
  EXPECT_EQ(prompt.size(), prompt2.size());
}

TEST(MultisetCopyConstructorTest, test12) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  s21_containersplus::multiset<int> prompt2(prompt);

  EXPECT_EQ(prompt.size(), prompt2.size());
}

TEST(MultisetCopyConstructorTest, test13) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);
  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));
  size_t prompt_size = prompt.size();
  s21_containersplus::multiset<int> prompt2(std::move(prompt));
  EXPECT_EQ(prompt.size(), 0);
  EXPECT_EQ(prompt2.size(), prompt_size);
}

TEST(MultisetFindTest, test14) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  size_t count_42 = 0;
  for (int i = 0; i < 5000; ++i) {
    int aux = distr(gen);
    if (aux == 42) ++count_42;
    prompt.insert(aux);
  }

  prompt.insert(42);
  ++count_42;

  size_t counter = 0;
  auto it = prompt.find(42);
  while (*it++ == 42) counter++;

  EXPECT_TRUE(prompt.find(42) != prompt.end());

  EXPECT_EQ(counter, count_42);
}

TEST(MultisetEraseTest, test15) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt = {3, 2, 5};

  prompt.erase(prompt.find(2));

  EXPECT_TRUE(prompt.contains(3));
  EXPECT_TRUE(prompt.contains(5));
  EXPECT_FALSE(prompt.contains(2));
}

TEST(MultisetEraseTest, test16) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt = {3, 2, 5};

  prompt.erase(prompt.find(5));

  EXPECT_TRUE(prompt.contains(2));
  EXPECT_TRUE(prompt.contains(3));
  EXPECT_FALSE(prompt.contains(5));
}

TEST(MultisetEraseTest, test17) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt = {3, 2, 5};

  prompt.erase(prompt.find(3));

  EXPECT_TRUE(prompt.contains(2));
  EXPECT_TRUE(prompt.contains(5));
  EXPECT_FALSE(prompt.contains(3));
}

TEST(MultisetEraseTest, test18) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  size_t count_42 = 0;
  for (int i = 0; i < 1000; ++i) {
    int aux = distr(gen);
    if (aux == 42) ++count_42;
    prompt.insert(aux);
  }

  prompt.insert(42);

  prompt.erase(prompt.find(42));

  auto it = prompt.find(42);
  if (count_42)
    EXPECT_TRUE(it != prompt.end());
  else
    EXPECT_TRUE(it == prompt.end());
}

TEST(MultisetEraseTest, test19) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  size_t count_42 = 0;
  for (int i = 0; i < 1000; ++i) {
    int aux = distr(gen);
    if (aux == 42) ++count_42;
    prompt.insert(aux);
  }

  for (int i = 0; i < 10; ++i) {
    ++count_42;
    prompt.insert(42);
  }

  EXPECT_EQ(prompt.size(), 1010);

  while (count_42--) prompt.erase(prompt.find(42));

  EXPECT_EQ(prompt.size(), 1000);

  auto it = prompt.find(42);
  EXPECT_TRUE(it == prompt.end());
}

TEST(MultisetSwapTest, test20) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt, prompt1, result;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));

  for (int i = 0; i < 2000; ++i) prompt1.insert(distr(gen));

  result = prompt;
  prompt1.swap(prompt);

  EXPECT_EQ(prompt.size(), 2000);
  EXPECT_EQ(prompt1.size(), 1000);
  for (auto it = prompt1.cbegin(), it_end = prompt1.cend(); it != it_end; ++it)
    EXPECT_TRUE(result.contains(it.value()));
}

TEST(MultisetMergeTest, test21) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt, prompt1, buffer;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));

  for (int i = 0; i < 2000; ++i) prompt1.insert(distr(gen));

  buffer = prompt;
  prompt1.merge(prompt);

  EXPECT_EQ(prompt.size(), 0);
  EXPECT_EQ(prompt1.size(), 3000);
  for (auto it = buffer.cbegin(), it_end = buffer.cend(); it != it_end; ++it)
    EXPECT_TRUE(prompt1.contains(*it));
}

TEST(MultisetEqualRangeTest, test23) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));

  for (int i = 0; i < 10; ++i) prompt.insert(42000);

  auto tmp_pair = prompt.equal_range(42000);

  size_t count = 0;
  for (auto it = tmp_pair.first, it_end = tmp_pair.second; it != it_end;
       ++it, ++count)
    EXPECT_TRUE(prompt.contains(42000));

  EXPECT_EQ(count, 10);
}

TEST(MultisetEqualRangeTest, test24) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));

  auto tmp_pair = prompt.equal_range(42000);

  EXPECT_EQ(tmp_pair.first, prompt.end());
  EXPECT_EQ(tmp_pair.second, prompt.end());
}

TEST(MultisetLowerBoundTest, test25) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));
  prompt.insert(1);

  auto it_num = prompt.lower_bound(0);

  EXPECT_TRUE(it_num.value() >= 0. || it_num.value() < 1.);

  if (prompt.find(0) == prompt.end()) {
    prompt.insert(0);
    auto it = prompt.lower_bound(0);

    EXPECT_TRUE(*it == 0);
  }
}

TEST(MultisetUpperBoundTest, test26) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-1000, 1000);

  for (int i = 0; i < 1000; ++i) prompt.insert(distr(gen));
  prompt.insert(1);

  auto num = prompt.upper_bound(0);

  EXPECT_TRUE(*num == 1);

  if (prompt.find(0) == prompt.end()) {
    prompt.insert(0);
    auto it = prompt.upper_bound(0);

    EXPECT_TRUE(*it != 0);
  }
}

TEST(MultisetInsertManyTest, test27) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<double> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-100., 100.);

  for (int i = 0; i < 100; ++i) prompt.insert(distr(gen));

  auto num = prompt.insert_many(0.5, 1.5, 2.5, 3.5);

  for (double num = 0.5; num < 4; num += 1.) EXPECT_TRUE(prompt.contains(num));
}

TEST(MultisetInsertManyTest, test28) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<double> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-100., 100.);

  for (int i = 0; i < 100; ++i) prompt.insert(distr(gen));

  auto num = prompt.insert_many();
}

TEST(MultisetBracketOperatorOverloadTest, test29) {
  using namespace s21_containersplus;
  s21_containersplus::multiset prompt = {"peppa", "bebra", "aux", "Peppa",
                                         "BeBra"};

  EXPECT_TRUE(prompt["aux"] != prompt.end());
  EXPECT_TRUE(prompt["aUx"] == prompt.end());
}

TEST(MultisetInstantiationTest, test30) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<double> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-100., 100.);

  for (int i = 0; i < 100; ++i) prompt.insert(distr(gen));

  for (auto it = prompt.begin(), it_end = prompt.end(); it != it_end; it++)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.cbegin(), it_end = prompt.cend(); it != it_end; it++)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.max(), it_end = prompt.end(); it != it_end; it--)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.cmax(), it_end = prompt.cend(); it != it_end; it--)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.max(), it_end = prompt.end(); it != it_end; --it)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.cmax(), it_end = prompt.cend(); it != it_end; --it)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
}

TEST(MultisetInstantiationTest, test31) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt;
  std::mt19937 gen(1111);  // 1111 - seed
  std::uniform_real_distribution<> distr(-100, 100);

  for (int i = 0; i < 100; ++i) prompt.insert(distr(gen));

  for (auto it = prompt.min(), it_end = prompt.max(); it != it_end; it++)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);
  for (auto it = prompt.cmax(), it_end = prompt.cmin(); it != it_end; it--)
    EXPECT_TRUE(it.value() >= -100. && it.value() <= 100.);

  EXPECT_TRUE(prompt.max_size());
}

TEST(MultisetEraseTest, test32) {
  using namespace s21_containersplus;
  s21_containersplus::multiset<int> prompt, prompt1;

  for (int i = 0; i < 10; ++i) prompt.insert(i);
  prompt.erase(prompt.find(5));
  for (int i = 10; i; --i) prompt1.insert(i);
  prompt.erase(prompt.find(5));

  multiset<int>::iterator it1 = multiset<int>::iterator(prompt.find(1));
  multiset<int>::iterator it2 = prompt.find(2);
  it1 = it2;
  EXPECT_TRUE(*it1 == *it2);

  multiset<int>::const_iterator cit1 = prompt.cbegin();
  multiset<int>::const_iterator cit2 = prompt.cmax();
  cit1 = cit2;
  EXPECT_TRUE(*cit1 == *cit2);
}
