#pragma once
#include <vector>

std::vector<int> Factorize(int n) {
  std::vector<int> res;

  for (int i = 2; n != 1; ++i) {
    while (n % i == 0) {
      res.push_back(i);
      n /= i;
    }
  }

  return res;
}