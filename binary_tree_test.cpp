#include "structures.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <initializer_list>

using namespace coursework;

TEST(BinaryTreeTest, EmptySearch) {
    BinaryTree t; EXPECT_FALSE(t.search(1));
}

TEST(BinaryTreeTest, EmptyRemoval) {
    BinaryTree t; EXPECT_FALSE(t.pop(1)); EXPECT_FALSE(t.search(1));
}

TEST(BinaryTreeTest, InsertAndSearch) {
    BinaryTree t; for (int x : {8, 3, 12, 1, 6}) t.push(x); for (int x : {8, 3, 12, 1, 6}) EXPECT_TRUE(t.search(x)); EXPECT_FALSE(t.search(5));
}

TEST(BinaryTreeTest, SearchDoesNotRemove) {
    BinaryTree t; t.push(8); const BinaryTree& view=t; EXPECT_TRUE(view.search(8)); EXPECT_TRUE(view.search(8)); EXPECT_TRUE(t.pop(8)); EXPECT_FALSE(t.search(8));
}

TEST(BinaryTreeTest, DuplicateIsIgnored) {
    BinaryTree t; t.push(5); t.push(5); EXPECT_TRUE(t.pop(5)); EXPECT_FALSE(t.search(5)); EXPECT_FALSE(t.pop(5));
}

TEST(BinaryTreeTest, RemoveLeaf) {
    BinaryTree t; for (int x : {8, 3, 12}) t.push(x); EXPECT_TRUE(t.pop(3)); EXPECT_FALSE(t.search(3)); EXPECT_TRUE(t.search(8)); EXPECT_TRUE(t.search(12));
}

TEST(BinaryTreeTest, RemoveNodeWithLeftChild) {
    BinaryTree t; for (int x : {8, 3, 1, 12}) t.push(x); EXPECT_TRUE(t.pop(3)); EXPECT_FALSE(t.search(3)); for (int x : {8, 1, 12}) EXPECT_TRUE(t.search(x));
}

TEST(BinaryTreeTest, RemoveNodeWithRightChild) {
    BinaryTree t; for (int x : {8, 3, 6, 12}) t.push(x); EXPECT_TRUE(t.pop(3)); EXPECT_FALSE(t.search(3)); for (int x : {8, 6, 12}) EXPECT_TRUE(t.search(x));
}

TEST(BinaryTreeTest, RemoveNodeWithTwoChildren) {
    BinaryTree t; for (int x : {10, 5, 15, 3, 8, 6, 9, 7}) t.push(x); EXPECT_TRUE(t.pop(5)); EXPECT_FALSE(t.search(5)); for (int x : {10, 15, 3, 8, 6, 9, 7}) EXPECT_TRUE(t.search(x));
}

TEST(BinaryTreeTest, RemoveRootWithTwoChildren) {
    BinaryTree t; for (int x : {8, 3, 12, 10, 14, 11}) t.push(x); EXPECT_TRUE(t.pop(8)); EXPECT_FALSE(t.search(8)); for (int x : {3, 12, 10, 14, 11}) EXPECT_TRUE(t.search(x));
}

TEST(BinaryTreeTest, RemoveRootWithOneChild) {
    BinaryTree t; t.push(8); t.push(3); EXPECT_TRUE(t.pop(8)); EXPECT_FALSE(t.search(8)); EXPECT_TRUE(t.search(3));
}

TEST(BinaryTreeTest, RemoveOnlyRootAndReuse) {
    BinaryTree t; t.push(8); EXPECT_TRUE(t.pop(8)); EXPECT_FALSE(t.search(8)); EXPECT_FALSE(t.pop(8)); t.push(2); EXPECT_TRUE(t.search(2));
}

TEST(BinaryTreeTest, MissingRemovalPreservesKeys) {
    BinaryTree t; for (int x : {8, 3, 12}) t.push(x); EXPECT_FALSE(t.pop(7)); for (int x : {8, 3, 12}) EXPECT_TRUE(t.search(x));
}

TEST(BinaryTreeTest, IntegerLimits) {
    BinaryTree t; for (int x : {std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max()}) t.push(x); for (int x : {std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max()}) { EXPECT_TRUE(t.search(x)); EXPECT_TRUE(t.pop(x)); EXPECT_FALSE(t.search(x)); }
}

TEST(BinaryTreeTest, SortedInputAndCompleteRemoval) {
    BinaryTree t; for(int i=0;i<100;++i) t.push(i); for(int i=99;i>=0;--i) { EXPECT_TRUE(t.search(i)); EXPECT_TRUE(t.pop(i)); EXPECT_FALSE(t.search(i)); } EXPECT_FALSE(t.pop(0));
}

TEST(BinaryTreeTest, InstancesAreIndependent) {
    BinaryTree a; BinaryTree b; a.push(1); b.push(9); EXPECT_FALSE(a.search(9)); EXPECT_FALSE(b.search(1)); EXPECT_TRUE(a.search(1)); EXPECT_TRUE(b.search(9));
}
