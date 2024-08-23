#include "../s21_containersplus.h"
#include "gtest/gtest.h"

TEST(ArrayDefaultConstuctTest, test1) {
  using namespace s21_containersplus;
  s21_containersplus::array<int, 0> prompt;
  EXPECT_EQ(prompt.empty(), true);
}

TEST(ArrayDefaultConstuctTest, test2) {
  using namespace s21_containersplus;
  s21_containersplus::array<int, 1> prompt;
  EXPECT_EQ(prompt.size(), 1);
  EXPECT_EQ(prompt[0], 0);
}

TEST(ArrayIninitializerListConstuctTest, test3) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 3> prompt{1, 2, 3};
  EXPECT_EQ(prompt.size(), 3);
  for (size_t i = 0; i < prompt.size(); ++i) EXPECT_EQ(prompt[i], i + 1);
}

TEST(ArrayIninitializerListConstuctTest, test4) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 3> prompt = {1, 2, 3};
  EXPECT_EQ(prompt.size(), 3);
  for (size_t i = 0; i < prompt.size(); ++i) EXPECT_EQ(prompt[i], i + 1);
}

TEST(ArrayIninitializerListConstuctTest, test5) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 3> prompt = {};
  EXPECT_EQ(prompt.size(), 3);
  for (size_t i = 0; i < prompt.size(); ++i) EXPECT_EQ(prompt[i], 0);
}

TEST(ArrayCopyConstuctTest, test6) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 4> prompt = {1, 2, 3, 4};
  s21_containersplus::array<size_t, 4> result(prompt);
  EXPECT_EQ(result.size(), 4);
  for (size_t i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], i + 1);
}

TEST(ArrayCopyConstuctTest, test7) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 4> prompt = {1, 2, 3, 4};
  auto result(prompt);
  EXPECT_EQ(result.size(), 4);
  for (size_t i = 0; i < 4; ++i) EXPECT_EQ(result[i], i + 1);
}

TEST(ArrayMoveConstuctTest, test8) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 4> prompt = {1, 2, 3, 4};
  auto result(std::move(prompt));
  EXPECT_EQ(result.size(), 4);
  for (size_t i = 0; i < 4; ++i) EXPECT_EQ(result[i], i + 1);
}

TEST(ArrayAssignmentTest, test9) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 4> prompt = {1, 2, 3, 4};
  auto result = prompt;
  EXPECT_EQ(result.size(), 4);
  for (size_t i = 0; i < 4; ++i) EXPECT_EQ(result[i], i + 1);
}

TEST(ArrayAssignmentTest, test10) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 4> prompt = {1, 2, 3, 4};
  auto result = std::move(prompt);
  EXPECT_EQ(result.size(), 4);
  for (size_t i = 0; i < 4; ++i) EXPECT_EQ(result[i], i + 1);
}

TEST(ArrayStaticSwapTest, test11) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {5, 4, 3, 2, 1};
  s21_containersplus::array<size_t, 5> prompt1 = {1, 2, 3, 4, 5};
  array<size_t, 5>::swap(prompt, prompt1);

  EXPECT_EQ(prompt1.size(), 5);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(prompt1[i], 5 - i);

  EXPECT_EQ(prompt.size(), 5);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(prompt[i], i + 1);
}

TEST(ArrayAtTest, test12) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {1, 2, 3, 4, 5};

  EXPECT_EQ(prompt[4], 5);
  EXPECT_EQ(prompt.at(4), 5);
  EXPECT_THROW(prompt.at(5), std::out_of_range);
}

TEST(ArrayFrontBackTest, test12) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {1, 2, 3, 4, 5};

  EXPECT_EQ(prompt.front(), 1);
  EXPECT_EQ(prompt.back(), 5);
}

TEST(ArrayDataTest, test13) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {1, 2, 3, 4, 5};

  auto ptr = prompt.data();
  for (size_t i = 0, i_max = prompt.size(); i < i_max; ++i)
    EXPECT_EQ(ptr[i], i + 1);
}

TEST(ArrayBeginEndTest, test14) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {1, 2, 3, 4, 5};

  auto it_begin = prompt.begin();
  auto it_end = prompt.end();

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(*(--it_end), 5);
}

TEST(ArrayBeginEndTest, test15) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 0> prompt;

  auto it_begin = prompt.begin();
  auto it_end = prompt.end();

  EXPECT_EQ(it_begin, it_end);
}

TEST(ArraySizeTest, test16) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {1, 2, 3, 4, 5};

  EXPECT_EQ(prompt.size(), 5);
  EXPECT_EQ(prompt.max_size(), 5);
}

TEST(ArraySizeTest, test17) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 0> prompt;

  EXPECT_EQ(prompt.size(), 0);
  EXPECT_EQ(prompt.max_size(), 0);
}

TEST(ArraySwapTest, test18) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {5, 4, 3, 2, 1};
  s21_containersplus::array<size_t, 5> prompt1 = {1, 2, 3, 4, 5};
  prompt.swap(prompt1);

  EXPECT_EQ(prompt1.size(), 5);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(prompt1[i], 5 - i);

  EXPECT_EQ(prompt.size(), 5);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(prompt[i], i + 1);
}

TEST(ArrayFillTest, test19) {
  using namespace s21_containersplus;
  s21_containersplus::array<size_t, 5> prompt = {5, 4, 3, 2, 1};
  prompt.fill(42);

  EXPECT_EQ(prompt.size(), 5);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(prompt[i], 42);
}

TEST(ArrayInstantiationTest, test20) {
  using namespace s21_containersplus;
  char str0[] = {"First text"};
  char str1[] = {"Next part of text"};
  char str2[] = {"PeppaPeppaPeppa"};
  s21_containersplus::array<char*, 3> prompt = {str0, str1, str2};

  std::swap(prompt[1], prompt[2]);

  for (size_t i = 0; str0[i] && str2[i]; ++i)
    *(prompt[2] + i) = *(prompt[0] + i);
}
