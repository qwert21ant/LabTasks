#pragma once

int* LowerBound(int* first, int const* last, int value) {
  int* mid = nullptr;

  while (last - first > 0) {
    mid = first + (last - first) / 2;

    if (*mid < value) {
      first = mid + 1;
    } else {
      last = mid;
    }
  }

  return first;
}
