class Solution {
  void moveRight(vector<int>::iterator& i, const vector<int>::iterator& end) {
      int prev_i = *i;
      ++i;
      while (i != end && prev_i == *i)
        ++i;
  }

  void moveLeft(const vector<int>::iterator& begin, vector<int>::iterator& i) {
      int prev_i = *i;
      --i;
      while (i != begin && prev_i == *i)
        --i;
  }

 public:
  vector<vector<int>> threeSum(vector<int>& v) {
    vector<vector<int>> out;

    if (v.size() < 3)
      return out;

    sort(v.begin(), v.end());

    int prev_k_val = v[0] - 1;

    for (int k = 0; k < v.size() - 2; ++k) {
      while (k < v.size() - 2 && prev_k_val == v[k]) {
        ++k;
      }

      if (k >= v.size() - 2)
        break;

      prev_k_val = v[k];

      auto i = v.begin() + k;
      ++i;
      auto j = v.end();
      --j;

      while (i < j) {
        int sum = *i + *j + prev_k_val;
        if (sum == 0) {
          out.emplace_back(std::initializer_list<int>({ prev_k_val, *i, *j }));
          moveRight(i, j);
        } else if (sum < 0) {
          moveRight(i, j);
        } else {
          moveLeft(i, j);
        }
      }
    }
    return out;
  }
};
