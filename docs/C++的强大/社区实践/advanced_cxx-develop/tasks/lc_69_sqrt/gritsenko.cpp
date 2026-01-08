class Solution {
public:
  int mySqrt(int x){
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;

    int l = 0;
    int r = std::min(x, 46340 + 1);
    int m = 0;
    while (r != l+1)
    {
        m = l + (r - l) / 2;
        if (x < m*m)
        {
            r = m;
        }
        else if (x > m*m)
        {
            l = m;
        }
        else
        {
            return m;
        }
    }
    return l;
}
};
