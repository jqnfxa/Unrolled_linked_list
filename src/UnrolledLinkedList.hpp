#pragma once

#include <vector>
#include <iostream>
#include "Node.hpp"

class UnrolledLinkedList {
 private:
  const int capacity;
  const int half_full;
  int size_;

  Node *head;
  Node *tail;

  void balance(Node *node);
  [[nodiscard]] std::pair<Node *, int> get_relative_index(int absolute_index) const;
  void insert_in_node(Node *node, int relative_index, int value);
  void erase_node(Node *node);
  void erase_from_node(Node *node, int idx);

 public:
  explicit UnrolledLinkedList(int n_array = 4);
  ~UnrolledLinkedList();

  void insert(int absolute_index, int value);
  void push_back(int value);
  void push_front(int value);

  void pop_back();
  void pop_front();
  void erase(int absolute_index);
  void erase_by_value(int value);

  [[nodiscard]] int size() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] int at(int absolute_index) const;
  [[nodiscard]] int find(int value) const;

  std::ostream &print_raw(std::ostream &out, const std::string &sep = " ", const std::string &end = "") const;
  friend std::ostream &operator<<(std::ostream &out, const UnrolledLinkedList &unrolled_linked_list);
};