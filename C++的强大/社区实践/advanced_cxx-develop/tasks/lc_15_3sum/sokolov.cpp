class Solution
{
public:
    vector<vector<int> > threeSum(vector<int>& nums)
    {
        vector<vector<int> > setThreeSum;
        int n = nums.size();

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i <= n - 3; i++)
        {
            int a = nums[i];

            // skip sets with the same 'a'
            if (i)
                if (a == nums[i-1]) continue;

            int start = i + 1;
            int end = n-1;
            while (start < end)
            {
                int b = nums[start];
                int c = nums[end];
                int sum = a + b + c;
                if (sum == 0) // found a set
                {
                    std::vector<int> vec_abc(3);
                    vec_abc[0] = a; vec_abc[1] = b; vec_abc[2] = c;

                    setThreeSum.push_back(vec_abc);

                    if (b == nums[start+1])
                    {
                        while (start < end) // skip sets with the same 'b' coefficients
                        {
                            start++;
                            if (nums[start]!=nums[start-1]) break;
                        }
                    }
                    else
                    {
                        while (start < end)
                        {
                            end--;
                            if (nums[end]!=nums[end+1]) break;
                        }
                    }
                }
                else if (sum > 0) // sum is bigger than 0, so take the next sum in the descending order
                {
                    while (start < end)
                    {
                        end--;
                        if (nums[end]!=nums[end+1]) break;
                    }
                }
                else
                {
                    while (start < end)
                    {
                        start++;
                        if (nums[start]!=nums[start-1]) break;
                    }
                }
            }
        }

        return setThreeSum;
    }
};
