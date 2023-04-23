#include "vector.h"

using namespace stepik;
using std::cout;

int main(){
    vector<int> vec1(5);
    vec1[0] = 0;
    vec1[1] = 1;
    vec1[2] = 2;
    vec1[3] = 3;
    vec1[4] = 4;
    cout << "step 1: " << vec1;
    vec1.erase(vec1.end());
    cout << "step 2: " << vec1;
    vec1.push_back(585);
    cout << "step 3: " << vec1;
    vector<int> vec2(vec1);
    cout << "step 4: " << vec2;
    vector<int> vec3(1);
    vec3 = vec1;
    cout << "step 5: " << vec3;
    vec1.insert(vec1.begin() + 1, vec2.begin(), vec2.end());
    cout << "step 6: " << vec1;
    return 0;
}
