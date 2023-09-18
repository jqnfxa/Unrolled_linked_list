#pragma once

#include <vector>

class Node {
 public:
  int size;
  Node *next;
  Node *prev;
  std::vector<int> elements;

  explicit Node(int maxElements, Node *previous = nullptr, Node *next = nullptr);
};