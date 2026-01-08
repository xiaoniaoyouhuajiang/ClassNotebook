class Solution {
 public:
  void process(vector<vector<int>>& out, const unordered_map<int, int>& m, int i, int j, int j_count) {
    if (i == j && j_count == 1)
      return;

    int sum = i + j;
    auto k = m.find(-sum);

    bool add = false;
    if (k != m.end()) {
      if (k->first < j)
        return;

      if (i == j) {
        if (k->first > j || k->first == j && j_count >= 3) {
          add = true;
        }
      } else {
        if (k->first > j || k->first == j && j_count >= 2) {
          add = true;
        }
      }

      if (add) {
        out.emplace_back(initializer_list<int>({i, j, k->first}));
      }
    }
  }

  vector<vector<int>> threeSum(vector<int>& nums) {
    unordered_map<int, int> m;
    vector<vector<int>> out;

    for (const int& val: nums) {
      ++m[val];
    }

    for (auto i = m.begin(); i != m.end(); ++i) {
      for (auto j = m.begin(); j != m.end(); ++j) {
        if (i->first <= j->first) {
          process(out, m, i->first, j->first, j->second);
        }
      }
    }

    return out;
  }
};
