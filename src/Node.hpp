#pragma once

#include <vector>

class Node {
 public:
  int size;
  Node *next;
  Node *prev;

  std::vector<int> elements;

  explicit Node(int max_elements, Node *previous = nullptr, Node *next = nullptr);
  Node *insert_node(Node *old);
  [[nodiscard]] bool is_full() const;
  [[nodiscard]] bool empty() const;
};