class Solution {
public:
    vector<vector<int>> threeSum(const vector<int>& nums) {
        vector<vector<int>> result;
        unordered_map<int, int> negative;
        unordered_map<int, int> nonNegative;

        // Fill negative and non-negative hash maps
        fillMaps(negative, nonNegative, nums);

        auto nonNegEnd(nonNegative.end());
        // Searching the sum of two each element of negative map in non-negative
        findAndPushTriplet(negative.begin(), negative.end(), nonNegative, result);
        // Searching the sum of two each element of non-negative map in negative
        findAndPushTriplet(nonNegative.begin(), nonNegEnd, negative, result);

        // Corner case for three zeros
        auto zeroIt(nonNegative.find(0));
        if (zeroIt != nonNegEnd && zeroIt->second > 2)
        {
            result.push_back({ 0, 0, 0 });
        }
        return result;
    }
private:
    void fillMaps(unordered_map<int, int>& negative, unordered_map<int, int>& nonNegative, const vector<int>& nums) const;
    template <typename Begin, typename End>
    void findAndPushTriplet(Begin&& begin, End&& end, const unordered_map<int, int>& oposite, vector<vector<int>>& result);
};

void Solution::fillMaps(unordered_map<int, int>& negative, unordered_map<int, int>& nonNegative, const vector<int>& nums) const
{
    for (auto& a : nums)
    {
        if (a < 0)
        {
            ++negative[a];
        }
        else
        {
            ++nonNegative[a];
        }
    }
}

template <typename Begin, typename End>
void Solution::findAndPushTriplet(Begin&& begin, End&& end, const unordered_map<int, int>& oposite, vector<vector<int>>& result)
{
    auto opositeEnd(oposite.end());
    for (auto it(begin); it != end; ++it)
    {
        // Checking number count in original input for solutions like [1,1,-2]
        if (it->second > 1)
        {
            auto opositeIt(oposite.find(-(it->first * 2)));
            if (opositeIt != opositeEnd)
            {
                result.emplace_back(std::initializer_list<int>{it->first, it->first, opositeIt->first });
            }
        }
        // calculate sum of two for each element in map.
        auto it2(it);
        ++it2;
        for (; it2 != end; ++it2)
        {
            auto sum(it2->first + it->first);
            auto opositeIt(oposite.find(-sum));
            if (opositeIt != opositeEnd)
            {
                result.emplace_back(std::initializer_list<int>{ it->first, it2->first, opositeIt->first });
            }
        }
    }
}
