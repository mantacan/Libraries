#include "../s21_containers.h"

TYPED_TEST(QueueComparisonTest, PushAndPop) {
  this->myQueue.push(1);
  this->stdQueue.push(1);

  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());

  this->myQueue.pop();
  this->stdQueue.pop();

  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

TYPED_TEST(QueueComparisonTest, FrontAndBack) {
  this->myQueue.push(1);
  this->myQueue.push(2);
  this->stdQueue.push(1);
  this->stdQueue.push(2);

  ASSERT_EQ(this->myQueue.front(), this->stdQueue.front());
  ASSERT_EQ(this->myQueue.back(), this->stdQueue.back());
}

TEST(QueueComparisonTest, DefaultConstructor1) {
  s21::queue<int> q;

  ASSERT_TRUE(q.empty());
  ASSERT_EQ(q.size(), 0);
}

TEST(QueueComparisonTest, InitConstructor) {
  s21::queue<int> castomQ({1, 2, 3, 4});
  std::queue<int> realQ({1, 2, 3, 4});
  std::string realQS;
  std::string castomQS;

  while (!castomQ.empty()) {
    castomQS += std::to_string(castomQ.front());
    castomQ.pop();
  }
  std::cout << std::endl;

  while (!realQ.empty()) {
    realQS += std::to_string(realQ.front());
    realQ.pop();
  }

  ASSERT_EQ(realQS, castomQS);
}

TEST(QueueComparisonTest, CopyConstructor) {
  s21::queue<int> castomQ({1, 2, 3, 4});
  std::queue<int> realQ({1, 2, 3, 4});

  s21::queue<int> copyCastom(castomQ);
  std::queue<int> copyReal(realQ);

  std::string realQS;
  std::string castomQS;

  while (!copyCastom.empty()) {
    castomQS += std::to_string(copyCastom.front());
    copyCastom.pop();
  }
  std::cout << std::endl;

  while (!copyReal.empty()) {
    realQS += std::to_string(copyReal.front());
    copyReal.pop();
  }

  ASSERT_EQ(realQS, castomQS);
}

TEST(QueueComparisonTest, MoveConstructor) {
  s21::queue<int> castomQ({1, 2, 3, 4});
  std::queue<int> realQ({1, 2, 3, 4});

  s21::queue<int> moveCastom(std::move(castomQ));
  std::queue<int> moveReal(std::move(realQ));

  std::string realQS;
  std::string castomQS;

  while (!moveCastom.empty()) {
    castomQS += std::to_string(moveCastom.front());
    moveCastom.pop();
  }
  std::cout << std::endl;

  while (!moveReal.empty()) {
    realQS += std::to_string(moveReal.front());
    moveReal.pop();
  }

  ASSERT_TRUE(castomQ.empty());
  ASSERT_TRUE(realQ.empty());

  ASSERT_EQ(realQS, castomQS);
}

TEST(QueueComparisonTest, operatorConstructor) {
  std::string castomQQQ = "456";
  std::string castomQS;

  s21::queue<int> originalQueue;
  originalQueue.push(1);
  originalQueue.push(2);
  originalQueue.push(3);

  s21::queue<int> movedQueue;
  movedQueue.push(4);
  movedQueue.push(5);
  movedQueue.push(6);

  originalQueue = std::move(movedQueue);

  while (!originalQueue.empty()) {
    castomQS += std::to_string(originalQueue.front());
    originalQueue.pop();
  }
  /*************/

  std::string castomQQQA = "456";
  std::string castomQSA;

  s21::queue<int> originalQueueA;
  originalQueueA.push(1);
  originalQueueA.push(2);
  originalQueueA.push(3);

  s21::queue<int> movedQueueA;
  movedQueueA.push(4);
  movedQueueA.push(5);
  movedQueueA.push(6);

  originalQueueA = std::move(movedQueueA);

  while (!originalQueueA.empty()) {
    castomQSA += std::to_string(originalQueueA.front());
    originalQueueA.pop();
  }

  ASSERT_EQ(castomQS, castomQSA);
  ASSERT_TRUE(movedQueue.empty());
  ASSERT_TRUE(movedQueueA.empty());
}

TEST(MethodsTestQueue, front) {
  s21::queue<int> myQueue;
  std::queue<int> CmyQueue;
  std::string s21str;
  std::string stdstr;

  myQueue.push(10);
  myQueue.push(20);
  myQueue.push(30);
  CmyQueue.push(10);
  CmyQueue.push(20);
  CmyQueue.push(30);

  s21str += std::to_string(myQueue.front());
  stdstr += std::to_string(CmyQueue.front());

  ASSERT_EQ(s21str, stdstr);
}

TEST(MethodsTestQueue, back) {
  s21::queue<int> myQueue;
  std::queue<int> CmyQueue;
  std::string s21str;
  std::string stdstr;

  myQueue.push(10);
  myQueue.push(20);
  myQueue.push(30);
  CmyQueue.push(10);
  CmyQueue.push(20);
  CmyQueue.push(30);

  s21str += std::to_string(myQueue.back());
  stdstr += std::to_string(CmyQueue.back());

  ASSERT_EQ(s21str, stdstr);
}

TEST(MethodsTestQueue, empty) {
  s21::queue<int> myQueue;
  std::queue<int> CmyQueue;

  s21::queue<int> myQueueNN({1, 2, 3, 4});
  std::queue<int> CmyQueueNN({1, 2, 3, 4});

  ASSERT_EQ(myQueue.empty(), CmyQueue.empty());
  ASSERT_EQ(myQueueNN.empty(), CmyQueueNN.empty());
}

TEST(MethodsTestQueue, size) {
  s21::queue<int> myQueue({1, 2, 3, 4, 5});
  std::queue<int> CmyQueue({1, 2, 3, 4, 5});

  ASSERT_EQ(myQueue.size(), CmyQueue.size());
}

TEST(MethodsTestQueue, push) {
  s21::queue<int> myQueue({1, 2, 3, 4, 5});
  std::queue<int> CmyQueue({1, 2, 3, 4, 5});

  std::string s21str;
  std::string stdstr;

  myQueue.push(15);
  CmyQueue.push(15);

  s21str += std::to_string(myQueue.back());
  stdstr += std::to_string(CmyQueue.back());

  ASSERT_EQ(s21str, stdstr);
}
TEST(MethodsTestQueue, pop) {
  s21::queue<int> myQueue({1, 2, 3, 4, 5});
  std::queue<int> CmyQueue({1, 2, 3, 4, 5});

  std::string s21str;
  std::string stdstr;

  myQueue.pop();
  CmyQueue.pop();

  s21str += std::to_string(myQueue.front());
  stdstr += std::to_string(CmyQueue.front());

  ASSERT_EQ(s21str, stdstr);
}
TEST(MethodsTestQueue, swap) {
  s21::queue<int> myQueue({1, 2, 3, 4, 5});
  s21::queue<int> myQueueFFF({6, 7, 8, 9, 0});

  std::queue<int> CmyQueue({1, 2, 3, 4, 5});
  std::queue<int> CmyQueueFFF({6, 7, 8, 9, 0});

  std::string s21str;
  std::string stdstr;

  myQueue.swap(myQueueFFF);
  CmyQueue.swap(CmyQueueFFF);

  while (!myQueue.empty()) {
    s21str += std::to_string(myQueue.front());
    myQueue.pop();
  }

  while (!CmyQueue.empty()) {
    stdstr += std::to_string(CmyQueue.front());
    CmyQueue.pop();
  }

  ASSERT_EQ(s21str, stdstr);
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  ASSERT_TRUE(q.empty()) << "Queue should be empty after default construction.";
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q({10, 20, 30});
  ASSERT_EQ(q.front(), 10)
      << "Front element should match the first in the initializer list.";
  ASSERT_EQ(q.back(), 30)
      << "Back element should match the last in the initializer list.";
  ASSERT_EQ(q.size(), 3)
      << "Size should match the number of elements in the initializer list.";
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> original({10, 20, 30});
  s21::queue<int> copy(original);
  ASSERT_FALSE(copy.empty()) << "Copied queue should not be empty.";
  ASSERT_EQ(copy.size(), original.size())
      << "Copied queue should have the same size as the original.";
  ASSERT_EQ(copy.front(), original.front())
      << "Front of copied queue should match the original.";
  ASSERT_EQ(copy.back(), original.back())
      << "Back of copied queue should match the original.";
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original({10, 20, 30});
  s21::queue<int> moved(std::move(original));
  ASSERT_TRUE(original.empty())
      << "Original queue should be empty after moving.";
  ASSERT_EQ(moved.size(), 3)
      << "Moved queue should have the elements from the original queue.";
}

TEST(QueueTest, MoveAssignment) {
  s21::queue<int> original({10, 20, 30});
  s21::queue<int> moved;
  moved = std::move(original);
  ASSERT_TRUE(original.empty())
      << "Original queue should be empty after move assignment.";
  ASSERT_EQ(moved.size(), 3)
      << "Moved queue should have the elements from the original queue.";
}

TEST(QueueTest, FrontOnEmptyQueue) {
  s21::queue<int> q;
  ASSERT_THROW(q.front(), std::out_of_range)
      << "Accessing front on an empty queue should throw an exception.";
}

TEST(QueueTest, BackOnEmptyQueue) {
  s21::queue<int> q;
  ASSERT_THROW(q.back(), std::out_of_range)
      << "Accessing back on an empty queue should throw an exception.";
}

TEST(QueueTest, PopOnEmptyQueue) {
  s21::queue<int> q;
  ASSERT_THROW(q.pop(), std::out_of_range)
      << "Popping from an empty queue should throw an exception.";
}

TEST(QueueTest, SwapQueues) {
  s21::queue<int> q1({10, 20, 30});
  s21::queue<int> q2({40, 50, 60});
  q1.swap(q2);
  ASSERT_EQ(q1.front(), 40) << "Front of q1 should be 40 after swap.";
  ASSERT_EQ(q2.front(), 10) << "Front of q2 should be 10 after swap.";
}

TYPED_TEST(QueueComparisonTest, DefaultConstructorf1) {
  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

TYPED_TEST(QueueComparisonTest, InitializerListConstructor) {
  s21::queue<TypeParam> myQueueInit = {1, 2, 3};
  std::queue<TypeParam> stdQueueInit(std::deque<TypeParam>{1, 2, 3});

  ASSERT_EQ(myQueueInit.size(), stdQueueInit.size());

  while (!myQueueInit.empty() && !stdQueueInit.empty()) {
    ASSERT_EQ(myQueueInit.front(), stdQueueInit.front());
    myQueueInit.pop();
    stdQueueInit.pop();
  }

  ASSERT_EQ(myQueueInit.empty(), stdQueueInit.empty());
}

TYPED_TEST(QueueComparisonTest, CopyConstructor4) {
  s21::queue<TypeParam> myQueueOrig = {1, 2, 3};
  s21::queue<TypeParam> myQueueCopy(myQueueOrig);

  std::queue<TypeParam> stdQueueOrig(std::deque<TypeParam>{1, 2, 3});
  std::queue<TypeParam> stdQueueCopy(stdQueueOrig);

  ASSERT_EQ(myQueueCopy.size(), stdQueueCopy.size());

  while (!myQueueCopy.empty() && !stdQueueCopy.empty()) {
    ASSERT_EQ(myQueueCopy.front(), stdQueueCopy.front());
    myQueueCopy.pop();
    stdQueueCopy.pop();
  }

  ASSERT_EQ(myQueueCopy.empty(), stdQueueCopy.empty());
}

TYPED_TEST(QueueComparisonTest, MoveConstructorgdf) {
  s21::queue<TypeParam> myQueueOrig = {1, 2, 3};
  s21::queue<TypeParam> myQueueMoved(std::move(myQueueOrig));

  std::queue<TypeParam> stdQueueOrig(std::deque<TypeParam>{1, 2, 3});
  std::queue<TypeParam> stdQueueMoved(std::move(stdQueueOrig));

  ASSERT_EQ(myQueueMoved.size(), stdQueueMoved.size());

  while (!myQueueMoved.empty() && !stdQueueMoved.empty()) {
    ASSERT_EQ(myQueueMoved.front(), stdQueueMoved.front());
    myQueueMoved.pop();
    stdQueueMoved.pop();
  }

  ASSERT_EQ(myQueueMoved.empty(), stdQueueMoved.empty());
  ASSERT_TRUE(myQueueOrig.empty());
  ASSERT_TRUE(stdQueueOrig.empty());
}

TYPED_TEST(QueueComparisonTest, CopyAssignmentOperatorg) {
  s21::queue<TypeParam> myQueueOrig = {1, 2, 3};
  s21::queue<TypeParam> myQueueCopy;
  myQueueCopy = std::move(myQueueOrig);

  std::queue<TypeParam> stdQueueOrig(std::deque<TypeParam>{1, 2, 3});
  std::queue<TypeParam> stdQueueCopy;
  stdQueueCopy = stdQueueOrig;

  ASSERT_EQ(myQueueCopy.size(), stdQueueCopy.size());

  while (!myQueueCopy.empty() && !stdQueueCopy.empty()) {
    ASSERT_EQ(myQueueCopy.front(), stdQueueCopy.front());
    myQueueCopy.pop();
    stdQueueCopy.pop();
  }

  ASSERT_EQ(myQueueCopy.empty(), stdQueueCopy.empty());
}

TYPED_TEST(QueueComparisonTest, MoveAssignmentOperator) {
  s21::queue<TypeParam> myQueueOrig = {1, 2, 3};
  s21::queue<TypeParam> myQueueMoved;
  myQueueMoved = std::move(myQueueOrig);

  std::queue<TypeParam> stdQueueOrig(std::deque<TypeParam>{1, 2, 3});
  std::queue<TypeParam> stdQueueMoved;
  stdQueueMoved = std::move(stdQueueOrig);

  ASSERT_EQ(myQueueMoved.size(), stdQueueMoved.size());

  while (!myQueueMoved.empty() && !stdQueueMoved.empty()) {
    ASSERT_EQ(myQueueMoved.front(), stdQueueMoved.front());
    myQueueMoved.pop();
    stdQueueMoved.pop();
  }

  ASSERT_EQ(myQueueMoved.empty(), stdQueueMoved.empty());
  ASSERT_TRUE(myQueueOrig.empty());
  ASSERT_TRUE(stdQueueOrig.empty());
}

TYPED_TEST(QueueComparisonTest, FrontAccess) {
  this->myQueue.push(1);
  this->myQueue.push(2);
  this->stdQueue.push(1);
  this->stdQueue.push(2);

  ASSERT_EQ(this->myQueue.front(), this->stdQueue.front());
}

TYPED_TEST(QueueComparisonTest, BackAccess) {
  this->myQueue.push(1);
  this->myQueue.push(2);
  this->stdQueue.push(1);
  this->stdQueue.push(2);

  ASSERT_EQ(this->myQueue.back(), this->stdQueue.back());
}

TYPED_TEST(QueueComparisonTest, EmptyCheck) {
  ASSERT_EQ(this->myQueue.empty(), this->stdQueue.empty());

  this->myQueue.push(1);
  this->stdQueue.push(1);

  ASSERT_EQ(this->myQueue.empty(), this->stdQueue.empty());
}

TYPED_TEST(QueueComparisonTest, SizeCheck) {
  this->myQueue.push(1);
  this->myQueue.push(2);
  this->stdQueue.push(1);
  this->stdQueue.push(2);

  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

TYPED_TEST(QueueComparisonTest, PushElement) {
  this->myQueue.push(1);
  this->stdQueue.push(1);

  ASSERT_EQ(this->myQueue.back(), this->stdQueue.back());
  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

TYPED_TEST(QueueComparisonTest, PopElement) {
  this->myQueue.push(1);
  this->myQueue.push(2);
  this->stdQueue.push(1);
  this->stdQueue.push(2);

  this->myQueue.pop();
  this->stdQueue.pop();

  ASSERT_EQ(this->myQueue.front(), this->stdQueue.front());
  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
}

TYPED_TEST(QueueComparisonTest, SwapQueues) {
  s21::queue<TypeParam> otherMyQueue;
  std::queue<TypeParam> otherStdQueue;

  this->myQueue.push(1);
  this->myQueue.push(2);
  otherMyQueue.push(3);
  otherMyQueue.push(4);

  this->stdQueue.push(1);
  this->stdQueue.push(2);
  otherStdQueue.push(3);
  otherStdQueue.push(4);

  this->myQueue.swap(otherMyQueue);
  this->stdQueue.swap(otherStdQueue);

  ASSERT_EQ(this->myQueue.size(), this->stdQueue.size());
  ASSERT_EQ(otherMyQueue.size(), otherStdQueue.size());

  while (!this->myQueue.empty() && !this->stdQueue.empty()) {
    ASSERT_EQ(this->myQueue.front(), this->stdQueue.front());
    this->myQueue.pop();
    this->stdQueue.pop();
  }
}

TYPED_TEST(QueueComparisonTest, InsertManyBack) {
  s21::queue<int> myQueue;
  myQueue.push(1);
  myQueue.insert_many_back(2, 3, 4, 5);

  ASSERT_EQ(myQueue.front(), 1);
  myQueue.pop();

  ASSERT_EQ(myQueue.front(), 2);
  myQueue.pop();
  ASSERT_EQ(myQueue.front(), 3);
  myQueue.pop();
  ASSERT_EQ(myQueue.front(), 4);
  myQueue.pop();
  ASSERT_EQ(myQueue.front(), 5);
  myQueue.pop();

  ASSERT_TRUE(myQueue.empty());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//
//   return RUN_ALL_TESTS();
// }
