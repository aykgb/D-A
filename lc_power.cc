#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        int64_t N = n;
        if(n < 0) {
            x = 1/x;
            N = -N;
        }

        double ans = 1;
        double production_factor = x;
        /* 2^10
         *
        */
        for(int64_t i = N; i > 0 ; i /= 2) {
            if(i % 2 == 1) {
                ans *= production_factor;
            }

            production_factor *= production_factor;
        }

        return ans;
    }
};

int main()
{
    std::cout << Solution().myPow(2.0, 10) << std::endl;

    return 0;
}
