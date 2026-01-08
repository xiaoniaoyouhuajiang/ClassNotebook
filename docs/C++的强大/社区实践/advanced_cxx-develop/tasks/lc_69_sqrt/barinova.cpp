class Solution {
public:
    int mySqrt(int x) {
        if (x < 0) {
            return std::numeric_limits<int>::min();
        }
        int upper_bound = x / 2 + 2;
        int lower_bound = 0;
        int sqrt_value = 0;
        while (lower_bound < upper_bound - 1) {            
            sqrt_value = lower_bound + (upper_bound - lower_bound) / 2;
            
            if ((sqrt_value == 0) || (sqrt_value <= x / sqrt_value)) {
                lower_bound = sqrt_value;
            } else {
                upper_bound = sqrt_value;
                --sqrt_value;
            }
        }
        return sqrt_value;
    }
};
