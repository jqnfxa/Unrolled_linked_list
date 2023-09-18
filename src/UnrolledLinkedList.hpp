#include <vector>
#include <iostream>
#include "Node.hpp"

class UnrolledLinkedList {
 private:
  const int capacity;
  Node *head;
  Node *tail;

 public:
  ~UnrolledLinkedList();
  explicit UnrolledLinkedList(int n_array = 4);
  void insert(int value);
  void erase(int value);
  [[nodiscard]] std::pair<Node *, int> find(int value) const;
  friend std::ostream &operator<<(std::ostream &out, const UnrolledLinkedList &ulst);
 private:
  void erase_node(Node *node);
  void insert_in_node(Node *node, int value);
  Node *find_node_to_insert(int value);
  void balance(Node *node);
};
