#include <gtest/gtest.h>

#include <iostream>

#include "../map/s21_map.h"

#define COMMON_LIST_INIT                                                      \
  std::initializer_list<std::pair<const int, std::string>> common_init_list = \
      {{5249, "Value 5249"}, {7596, "Value 7596"}, {4719, "Value 4719"},      \
       {8212, "Value 8212"}, {3347, "Value 3347"}, {6634, "Value 6634"},      \
       {4688, "Value 4688"}, {3468, "Value 3468"}, {3092, "Value 3092"},      \
       {2859, "Value 2859"}, {8308, "Value 8308"}, {5755, "Value 5755"},      \
       {6967, "Value 6967"}, {7525, "Value 7525"}, {8416, "Value 8416"},      \
       {7606, "Value 7606"}, {9059, "Value 9059"}, {5847, "Value 5847"},      \
       {4428, "Value 4428"}, {1403, "Value 1403"}};
#define INITIALIZATION_TESTS_TEMPLATE(map) \
  EXPECT_EQ(map[5249], "Value 5249");      \
  EXPECT_EQ(map[7596], "Value 7596");      \
  EXPECT_EQ(map[4719], "Value 4719");      \
  EXPECT_EQ(map[8212], "Value 8212");      \
  EXPECT_EQ(map[3347], "Value 3347");      \
  EXPECT_EQ(map[6634], "Value 6634");      \
  EXPECT_EQ(map[4688], "Value 4688");      \
  EXPECT_EQ(map[3468], "Value 3468");      \
  EXPECT_EQ(map[3092], "Value 3092");      \
  EXPECT_EQ(map[2859], "Value 2859");      \
  EXPECT_EQ(map[8308], "Value 8308");      \
  EXPECT_EQ(map[5755], "Value 5755");      \
  EXPECT_EQ(map[6967], "Value 6967");      \
  EXPECT_EQ(map[7525], "Value 7525");      \
  EXPECT_EQ(map[8416], "Value 8416");      \
  EXPECT_EQ(map[7606], "Value 7606");      \
  EXPECT_EQ(map[9059], "Value 9059");      \
  EXPECT_EQ(map[5847], "Value 5847");      \
  EXPECT_EQ(map[4428], "Value 4428");      \
  EXPECT_EQ(map[1403], "Value 1403");      \
  EXPECT_ANY_THROW(map.at(11111));         \
  EXPECT_EQ(map.size(), 20);

#define AT_TESTS_TEMPLATE(map)           \
  EXPECT_EQ(map.at(5249), "Value 5249"); \
  EXPECT_EQ(map.at(7596), "Value 7596"); \
  EXPECT_EQ(map.at(4719), "Value 4719"); \
  EXPECT_EQ(map.at(8212), "Value 8212"); \
  EXPECT_EQ(map.at(3347), "Value 3347"); \
  EXPECT_EQ(map.at(6634), "Value 6634"); \
  EXPECT_EQ(map.at(4688), "Value 4688"); \
  EXPECT_EQ(map.at(3468), "Value 3468"); \
  EXPECT_EQ(map.at(3092), "Value 3092"); \
  EXPECT_EQ(map.at(2859), "Value 2859"); \
  EXPECT_EQ(map.at(8308), "Value 8308"); \
  EXPECT_EQ(map.at(5755), "Value 5755"); \
  EXPECT_EQ(map.at(6967), "Value 6967"); \
  EXPECT_EQ(map.at(7525), "Value 7525"); \
  EXPECT_EQ(map.at(8416), "Value 8416"); \
  EXPECT_EQ(map.at(7606), "Value 7606"); \
  EXPECT_EQ(map.at(9059), "Value 9059"); \
  EXPECT_EQ(map.at(5847), "Value 5847"); \
  EXPECT_EQ(map.at(4428), "Value 4428"); \
  EXPECT_EQ(map.at(1403), "Value 1403"); \
  EXPECT_ANY_THROW(map.at(11111));       \
  EXPECT_EQ(map.size(), 20);

class S21MapTests : public testing::Test {};

TEST(S21MapTests, InitializationAndDestruction_empty) {
  s21::map<int, std::string> empty_initialization;
  size_t expected_empty_size = 0;
  s21::BinaryTree<int, std::string> *expected_empty_tree_ptr = nullptr;
  EXPECT_EQ(expected_empty_size, empty_initialization.size());
  EXPECT_EQ(empty_initialization.begin().getNodePtr(), expected_empty_tree_ptr);
  empty_initialization.~map();
  EXPECT_EQ(empty_initialization.begin().getNodePtr(), expected_empty_tree_ptr);
}

TEST(S21MapTests, InitializationAndDestruction_list) {
  COMMON_LIST_INIT
  s21::map<int, std::string> list_initialization(common_init_list);
  INITIALIZATION_TESTS_TEMPLATE(list_initialization);
  list_initialization.~map();
  EXPECT_ANY_THROW(list_initialization.at(1));
  EXPECT_EQ(list_initialization.size(), 0);
}

TEST(S21MapTests, InitializationAndDestruction_other) {
  COMMON_LIST_INIT
  s21::map<int, std::string> list_initialization(common_init_list);
  s21::map<int, std::string> from_map_initialization(list_initialization);
  INITIALIZATION_TESTS_TEMPLATE(from_map_initialization)
  from_map_initialization.~map();
  EXPECT_ANY_THROW(from_map_initialization.at(1));
  EXPECT_EQ(from_map_initialization.size(), 0);
}

TEST(S21MapTests, InitializationAndDestruction_move) {
  COMMON_LIST_INIT
  s21::map<int, std::string> list_initialization(common_init_list);
  s21::map<int, std::string> move_initialization(
      std::move(list_initialization));
  INITIALIZATION_TESTS_TEMPLATE(move_initialization)
  move_initialization.~map();
  EXPECT_ANY_THROW(move_initialization.at(1));
  EXPECT_EQ(move_initialization.size(), 0);
}

TEST(S21MapTests, OperatorEq) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> second_empty_map;
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  empty_map = valid_map;
  INITIALIZATION_TESTS_TEMPLATE(empty_map);
  empty_map = second_empty_map;
  EXPECT_EQ(empty_map.size(), 0);
  EXPECT_ANY_THROW(empty_map.at(-2));
  empty_map = second_empty_map;
  EXPECT_EQ(empty_map.size(), 0);
  EXPECT_ANY_THROW(empty_map.at(-2));
  valid_map = valid_map;
  INITIALIZATION_TESTS_TEMPLATE(valid_map);
}

TEST(S21MapTests, At_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  AT_TESTS_TEMPLATE(valid_map)
  valid_map.at(5847) = "test";
  EXPECT_EQ(valid_map.at(5847), "test");
}

TEST(S21MapTests, At_empty) {
  s21::map<int, std::string> empty;
  EXPECT_ANY_THROW(empty.at(5847));
  EXPECT_EQ(empty.size(), 0);
}

TEST(S21MapTests, ByKey_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  INITIALIZATION_TESTS_TEMPLATE(valid_map)
  valid_map[5847] = "test";
  EXPECT_EQ(valid_map[5847], "test");
}

TEST(S21MapTests, ByKey_empty) {
  s21::map<int, std::string> empty;
  empty[5847] = "tttteeee";
  EXPECT_EQ(empty[5847], "tttteeee");
  EXPECT_EQ(empty.size(), 1);
}

TEST(S21MapTests, IteratorBegin_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ((*(valid_map.begin())).first, 1403);
}

TEST(S21MapTests, IteratorBegin_empty) {
  s21::map<int, std::string> empty;
  EXPECT_EQ(empty.begin(), nullptr);
}

TEST(S21MapTests, IteratorEnd_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ((*(valid_map.end())).first, 9059);
}

TEST(S21MapTests, IteratorEnd_empty) {
  s21::map<int, std::string> empty;
  EXPECT_EQ(empty.end(), nullptr);
}

TEST(S21MapTests, isEmpty_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ(valid_map.empty(), 0);
}

TEST(S21MapTests, isEmpty_empty) {
  s21::map<int, std::string> empty;
  EXPECT_EQ(empty.empty(), 1);
}

TEST(S21MapTests, size_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ(valid_map.size(), 20);
}

TEST(S21MapTests, size_empty) {
  s21::map<int, std::string> empty;
  EXPECT_EQ(empty.size(), 0);
}

TEST(S21MapTests, size_valid_merged_with_itself) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  valid_map.merge(valid_map);
  EXPECT_EQ(valid_map.size(), 20);
}

TEST(S21MapTests, size_valid_merged_with_same) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::map<int, std::string> valid_map_2(common_init_list);
  valid_map.merge(valid_map_2);
  EXPECT_EQ(valid_map.size(), 20);
}

TEST(S21MapTests, max_capacity) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ(valid_map.max_size(), std::numeric_limits<size_t>::max());
}

TEST(S21MapTests, clear_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  valid_map.clear();
  EXPECT_TRUE(valid_map.empty());
  EXPECT_EQ(valid_map.getRoot(), nullptr);
}

TEST(S21MapTests, clear_empty) {
  s21::map<int, std::string> empty;
  empty.clear();
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(empty.getRoot(), nullptr);
}

TEST(S21MapTests, insert_value_to_init) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  std::pair<int, std::string> value_to_insert;
  value_to_insert.first = 4444;
  value_to_insert.second = "Value 4444";
  valid_map.insert(value_to_insert);
  EXPECT_EQ(valid_map[4444], "Value 4444");
}

TEST(S21MapTests, insert_value_to_empty) {
  s21::map<int, std::string> empty;
  std::pair<int, std::string> value_to_insert;
  value_to_insert.first = 4444;
  value_to_insert.second = "Value 4444";
  empty.insert(value_to_insert);
  EXPECT_EQ(empty[4444], "Value 4444");
}

TEST(S21MapTests, insert_key_value_to_init) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  valid_map.insert(4444, "Value 4444");
  EXPECT_EQ(valid_map[4444], "Value 4444");
}

TEST(S21MapTests, insert_key_value_to_empty) {
  s21::map<int, std::string> empty;
  empty.insert(4444, "Value 4444");
  EXPECT_EQ(empty[4444], "Value 4444");
}

TEST(S21MapTests, insert_or_assign_to_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  valid_map.insert_or_assign(4444, "Value 4444");
  EXPECT_EQ(valid_map[4444], "Value 4444");
  valid_map.insert_or_assign(4444, "Hiya");
  EXPECT_EQ(valid_map[4444], "Hiya");
}

TEST(S21MapTests, insert_or_assign_to_empty) {
  s21::map<int, std::string> empty;
  empty.insert_or_assign(4444, "Value 4444");
  EXPECT_EQ(empty[4444], "Value 4444");
  empty.insert_or_assign(4444, "Hiya");
  EXPECT_EQ(empty[4444], "Hiya");
}

TEST(S21MapTests, insert_many) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  std::pair<int, std::string> value_to_insert;
  value_to_insert.first = 4444;
  value_to_insert.second = "Value 4444";
  std::pair<int, std::string> value_to_insert_2;
  value_to_insert_2.first = 4445;
  value_to_insert_2.second = "Value 4445";
  valid_map.insert_many(value_to_insert, value_to_insert_2);
  EXPECT_EQ(valid_map[4444], "Value 4444");
  EXPECT_EQ(valid_map[4445], "Value 4445");
}

TEST(S21MapTests, erase_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::MapIterator<int, std::string> iterator = valid_map.begin();
  iterator.goToKey(3092);
  valid_map.erase(iterator);
  EXPECT_ANY_THROW(valid_map.begin().goToKey(3092));
  EXPECT_EQ(valid_map.size(), 19);
  iterator = valid_map.begin();
  iterator.goToKey(1403);
  valid_map.erase(iterator);
  EXPECT_ANY_THROW(valid_map.begin().goToKey(1403));
  EXPECT_EQ(valid_map.size(), 18);
  iterator = valid_map.begin();
  iterator.goToKey(9059);
  valid_map.erase(iterator);
  EXPECT_ANY_THROW(valid_map.begin().goToKey(9059));
  EXPECT_EQ(valid_map.size(), 17);
  iterator = valid_map.begin();
  iterator.goToKey(5249);
  valid_map.erase(iterator);
  EXPECT_ANY_THROW(valid_map.begin().goToKey(5249));
  EXPECT_EQ(valid_map.size(), 16);
  iterator = valid_map.begin();
  iterator.goToKey(4688);
  valid_map.erase(iterator);
  EXPECT_ANY_THROW(valid_map.begin().goToKey(4688));
  EXPECT_EQ(valid_map.size(), 15);
}

TEST(S21MapTests, erase_empty) {
  s21::map<int, std::string> empty;
  s21::MapIterator<int, std::string> iterator = empty.begin();
  EXPECT_ANY_THROW(empty.erase(iterator));
}

TEST(S21MapTests, swap_valid_with_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::map<int, std::string> valid_map_2;
  valid_map_2.insert(4444, "Value 4444");
  valid_map.swap(valid_map_2);
  EXPECT_EQ(valid_map.at(4444), "Value 4444");
  EXPECT_ANY_THROW(valid_map.at(8212));
  EXPECT_EQ(valid_map.size(), 1);
  EXPECT_EQ(valid_map_2.at(8212), "Value 8212");
  EXPECT_ANY_THROW(valid_map_2.at(4444));
  EXPECT_EQ(valid_map_2.size(), 20);
}

TEST(S21MapTests, swap_valid_with_empty) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::map<int, std::string> valid_map_2;
  valid_map.swap(valid_map_2);
  EXPECT_ANY_THROW(valid_map.at(8212));
  EXPECT_EQ(valid_map.size(), 0);
  EXPECT_EQ(valid_map_2.at(8212), "Value 8212");
  EXPECT_ANY_THROW(valid_map_2.at(4444));
  EXPECT_EQ(valid_map_2.size(), 20);
}

TEST(S21MapTests, merge_valid_with_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::map<int, std::string> valid_map_2;
  valid_map_2.insert(4444, "Value 4444");
  valid_map.merge(valid_map_2);
  EXPECT_EQ(valid_map.at(4444), "Value 4444");
  EXPECT_EQ(valid_map.at(8212), "Value 8212");
  EXPECT_EQ(valid_map.size(), 21);
}

TEST(S21MapTests, merge_valid_with_empty) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  s21::map<int, std::string> empty;
  valid_map.merge(empty);
  EXPECT_EQ(valid_map.at(8212), "Value 8212");
  EXPECT_EQ(valid_map.size(), 20);
}

TEST(S21MapTests, contains_valid) {
  COMMON_LIST_INIT
  s21::map<int, std::string> valid_map(common_init_list);
  EXPECT_EQ(valid_map.contains(8212), 1);
  EXPECT_EQ(valid_map.contains(4444), 0);
  EXPECT_EQ(valid_map.contains(9059), 1);
}

TEST(S21MapTests, contains_empty) {
  s21::map<int, std::string> empty;
  EXPECT_EQ(empty.contains(8212), 0);
  EXPECT_EQ(empty.contains(4444), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}