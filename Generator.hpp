#pragma once

#include <vector>

class Generator {
  Generator();
 public:
  static int pick_num(int from, int to);
  [[nodiscard]] static std::vector<int> gen_range(int size, int from, int to);
};
