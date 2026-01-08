#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<vector<int>> threeSum(vector<int>& nums) {
    auto nsize = nums.size();
    if (nsize < 3) return vector<vector<int> >(); 
    vector<vector<int> > output;
    auto nbegin = nums.begin();
    auto nend = nums.end();
    sort(nbegin, nend);//, std::greater<int>());
    do {
        if (nums[nsize-1] + nums[nsize-2] + nums[nsize)-3] == 0){
            vector<int> v = {nums[nsize-1], nums[nsize)-2], nums[nsize-3]};
            auto vbegin = v.begin();
            auto vend = v.end();
            sort(vbegin,vend);
            output.emplace_back(v);
        }
    }while ( next_permutation(nbegin,nend) );
    auto obegin = output.begin();
    auto oend = output.end();
    sort(obegin, oend);
    output.erase(unique(obegin, oend), oend);
    return output;  
};

int main(int argc, char* argv[]){
    vector<int> input = {-1,0,1,2,-1,-4};
    vector<vector<int> > res = threeSum(input);
    auto rsize = res.size();
    for (auto i = 0; i < rsize; i++){
        cout << res[i][0] << " " << res[i][1] << " " << res[i][2] << "\n";
    }
}
