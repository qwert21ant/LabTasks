template <typename T>
T Min(T val) {
  return val;
}

template <typename T, typename... Args>
T Min(T val1, T val2, Args... args) {
  return Min(val1 < val2 ? val1 : val2, args...);
}

const int kN3 = 3;
const int kN4 = 4;

int** MakeSpiral(int n) {
  int** m = new int*[n];
  for (int i = 0; i < n; ++i) {
    m[i] = new int[n];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int dist = Min(i, j, n - i + 1, n - j + 1) - 1;
      int k = n - 2 * dist;
      int ci = i - dist;
      int cj = j - dist;
      int pos;

      if (ci == 1) {
        pos = cj;
      } else if (ci == k) {
        pos = kN3 * k - cj - 1;
      } else if (cj == 1) {
        pos = kN4 * k - ci - 2;
      } else {
        pos = k + ci - 1;
      }

      int off = kN4 * dist * (n - dist);
      m[i - 1][j - 1] = off + pos;
    }
  }
  return m;
}