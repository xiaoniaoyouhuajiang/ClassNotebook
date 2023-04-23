class Solution {
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

      auto i = v.begin() + k + 1;
      auto j = v.end() - 1;

      while (i < j) {
        int sum = *i + *j + prev_k_val;
        if (sum == 0) {
          out.emplace_back(std::initializer_list<int>({prev_k_val, *i, *j}));
          i = lower_bound(i, j, *i + 1);
        } else  {
          if (i + 1 > j - 1)
            break;
          if (sum < 0) {
            i = lower_bound(i + 1, j - 1, -prev_k_val - *j);
          } else {
            j = lower_bound(i + 1, j - 1, -prev_k_val - *i);
          }
        }
      }
    }
    return out;
  }
};
