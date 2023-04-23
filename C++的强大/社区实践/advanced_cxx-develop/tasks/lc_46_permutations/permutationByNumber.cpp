class Solution {
public:
    int factorial(int n)
    {
	    int result = 1;
	    for(int i = 1; i <= n; i++)
	    {    
		    result *= i;
	    }
	    return result;
    }
    void swap(std::vector<int>& nums, int i, int j)
    {
	    int tmp = nums[i];
	    nums[i] = nums[j];
	    nums[j] = tmp; 
    }
    std::vector<int> getNPernutation(std::vector<int> nums, int position, int n)
    {
	    int k = position;
	    int nPost = n;  // how many ellements after i-ellement
	    for(int i = 0; i < n; i++)
	    {
		    std::sort(nums.begin()+i,nums.end());
		    for(int j=1;j<nPost+1;j++)
		    {
			    if(k <= j*factorial(nPost-1))
			    {
				    swap(nums,i,i+j-1);
				    if(k >= (j-1)*factorial(nPost-1))
				      k = k - (j-1)*factorial(nPost-1);
           			    nPost -= 1;   
				    break;
			    }
		    }
	    }
	    return nums;
    }
    std::vector<vector<int>> permute(vector<int>& nums) {
       	int n = nums.size();
        int numberOfPerm = factorial(n);
       	std::vector< vector<int> > result;
        for(int i=1;i<numberOfPerm+1;i++)
		    {
		      std::vector<int> vNum = getNPernutation(nums, i, n);
		      result.push_back(vNum);
		    } 
        return result;
    }

};
