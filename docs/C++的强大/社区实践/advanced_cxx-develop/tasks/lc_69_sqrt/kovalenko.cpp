class Solution {
public:
    int mySqrt(int v) {
        long long l = 0;
        long long m = 0;
        long long r = v;
        
        if (v == 1)
        return 1;
        while (r - l > 0 ) {
            m = l + (r -l)/2;
            if (m == l)
                break;
            if (m * m > v) {
                r = m;
            } else 
                l = m;
        }
        return m;
    }
};
