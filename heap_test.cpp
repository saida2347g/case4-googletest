#include "structures.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <initializer_list>

using namespace coursework;

TEST(HeapTest, EmptyPopThrows) {
    Heap s; EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(HeapTest, SingleElement) {
    Heap s; s.push(42); EXPECT_EQ(s.pop(), 42); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(HeapTest, PreservesRequiredOrder) {
    Heap s; for (int x : {3, 1, 4, 2}) s.push(x); for (int x : {4, 3, 2, 1}) EXPECT_EQ(s.pop(), x); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(HeapTest, RetainsDuplicates) {
    Heap s; s.push(7); s.push(7); EXPECT_EQ(s.pop(), 7); EXPECT_EQ(s.pop(), 7); EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(HeapTest, NegativeAndZero) {
    Heap s; for (int x : {-3, 0, -1}) s.push(x); for (int x : {0, -1, -3}) EXPECT_EQ(s.pop(), x);
}

TEST(HeapTest, IntegerLimits) {
    Heap s; const int lo=std::numeric_limits<int>::min(); const int hi=std::numeric_limits<int>::max(); s.push(lo); s.push(hi); EXPECT_EQ(s.pop(), hi); EXPECT_EQ(s.pop(), lo);
}

TEST(HeapTest, InterleavesPushAndPop) {
    Heap s; s.push(2); s.push(5); EXPECT_EQ(s.pop(), 5); s.push(3); EXPECT_EQ(s.pop(), 3); EXPECT_EQ(s.pop(), 2);
}

TEST(HeapTest, ReusableAfterEmpty) {
    Heap s; s.push(1); EXPECT_EQ(s.pop(), 1); EXPECT_THROW(s.pop(), std::out_of_range); s.push(9); EXPECT_EQ(s.pop(), 9);
}

TEST(HeapTest, InstancesAreIndependent) {
    Heap a; Heap b; a.push(1); b.push(9); EXPECT_EQ(a.pop(), 1); EXPECT_EQ(b.pop(), 9);
}

TEST(HeapTest, ManyElements) {
    Heap s; for (int i=0;i<1000;++i) s.push(i); for (int i=999;i>=0;--i) EXPECT_EQ(s.pop(), i); EXPECT_THROW(s.pop(), std::out_of_range);
}
