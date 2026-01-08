class Solution {
public:
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    if(nums.size() < 3)
        return result;
    std::sort(nums.begin(), nums.end());
    std::vector<int>::iterator itbeg = nums.begin();
    std::vector<int>::iterator itend = nums.end() - 1;
    int prevbeg;
    int prevend;
    int j = 0;
    bool firstItend = true;
    while(itend != nums.begin())
    {
        if(firstItend || *itend != prevend)
        {
            itbeg = nums.begin();
            prevbeg = *(nums.begin() + (nums.size() - 1));
            bool firstItbeg = true;
            while(itbeg != itend)
            {
                if((firstItbeg || *itbeg != prevbeg) && (std::binary_search(itbeg+1, itend, -1*(*itbeg + *itend))))
                {
                    result.push_back({*itbeg, *itend, -1*(*itbeg + *itend)});
                }
                prevbeg = *itbeg;
                itbeg++;
                firstItbeg = false;
            }
        }
        prevend = *itend;
        itend--;
        firstItend = false;
    }

    return result;
}

};
