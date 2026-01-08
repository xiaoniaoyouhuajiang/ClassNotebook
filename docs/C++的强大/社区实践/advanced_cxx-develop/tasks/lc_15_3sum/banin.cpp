#include <set>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        using std::set;
        using std::vector;
        auto begin = nums.begin();
        auto end = nums.end();
        sort(begin, end);
        set<vector<int>> ans;
        // Might want to squash repetitions for nums with many repeating values
        // $O(n^2)$ search * $O(\log n)$ binary search and set insertion
        for(auto it = begin; it != end; ++it){
            // Not iteration with :, since you can't quite cut corners as effectively
            for(auto jt = it + 1; jt != end; ++jt){
                int a = *it, b = *jt, target = -(a + b);
                auto kt = lower_bound(jt + 1, end, target);
                if(kt != end && *kt == target){
                    ans.insert(vector<int>{a, b, *kt}); // Modern brace initializer
                }
            }
        }
        auto abegin = ans.begin();
        auto aend = ans.end();
        return vector<vector<int>>(abegin, aend);
    }
};
