#include "structures.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <initializer_list>

using namespace coursework;

TEST(QueueTest, EmptyPopThrows) {
    Queue s; EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(QueueTest, SingleElement) {
    Queue s; s.push(42); EXPECT_EQ(s.pop(), 42); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(QueueTest, PreservesRequiredOrder) {
    Queue s; for (int x : {3, 1, 4, 2}) s.push(x); for (int x : {3, 1, 4, 2}) EXPECT_EQ(s.pop(), x); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(QueueTest, RetainsDuplicates) {
    Queue s; s.push(7); s.push(7); EXPECT_EQ(s.pop(), 7); EXPECT_EQ(s.pop(), 7); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(QueueTest, NegativeAndZero) {
    Queue s; for (int x : {-3, 0, -1}) s.push(x); for (int x : {-3, 0, -1}) EXPECT_EQ(s.pop(), x);
}

TEST(QueueTest, IntegerLimits) {
    Queue s; const int lo=std::numeric_limits<int>::min(); const int hi=std::numeric_limits<int>::max(); s.push(lo); s.push(hi); EXPECT_EQ(s.pop(), lo); EXPECT_EQ(s.pop(), hi);
}

TEST(QueueTest, InterleavesPushAndPop) {
    Queue s; s.push(2); s.push(5); EXPECT_EQ(s.pop(), 2); s.push(3); EXPECT_EQ(s.pop(), 5); EXPECT_EQ(s.pop(), 3);
}

TEST(QueueTest, ReusableAfterEmpty) {
    Queue s; s.push(1); EXPECT_EQ(s.pop(), 1); EXPECT_THROW(s.pop(), std::out_of_range); s.push(9); EXPECT_EQ(s.pop(), 9);
}

TEST(QueueTest, InstancesAreIndependent) {
    Queue a; Queue b; a.push(1); b.push(9); EXPECT_EQ(a.pop(), 1); EXPECT_EQ(b.pop(), 9);
}

TEST(QueueTest, ManyElements) {
    Queue s; for (int i=0;i<1000;++i) s.push(i); for (int i=0;i<1000;++i) EXPECT_EQ(s.pop(), i); EXPECT_THROW(s.pop(), std::out_of_range);
}
