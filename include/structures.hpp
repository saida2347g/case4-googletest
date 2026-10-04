#pragma once

#include <memory>
#include <stdexcept>

namespace coursework {

// FIFO: pop removes and returns the oldest element.
// Empty pop throws std::out_of_range and leaves the queue empty.
class Queue {
public:
    Queue();
    ~Queue();
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    void push(int value);
    int pop();
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

// Max-heap: pop removes and returns the largest element.
// Duplicates are retained. Empty pop throws std::out_of_range.
class Heap {
public:
    Heap();
    ~Heap();
    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;
    void push(int value);
    int pop();
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

// Binary search tree with set semantics: duplicate push is a no-op.
// pop(value) removes the key, returns true if found, false otherwise.
// search is read-only; missing keys do not cause exceptions.
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    void push(int value);
    bool pop(int value);
    bool search(int value) const;
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace coursework
