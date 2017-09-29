#include <iostream>
#include <vector>

using namespace std;


/* i, j indicates the range of subsequence which is continuous.
 *
 */
int MaxSubSequenceSum_0(std::vector<int> &A)
{
    int MaxSum = 0, ThisSum;
    for(size_t i = 0; i < A.size(); ++i) {
        for(size_t j = i; j < A.size(); ++j) {
            ThisSum = 0;
            for(size_t k = i; k <= j; k++) {
                ThisSum += A[k];

                if(ThisSum > MaxSum)
                    MaxSum = ThisSum;
            }
        }
    }

    return MaxSum;
}

int MaxSubSequenceSum_1(std::vector<int> &A)
{
    int MaxSum = 0, ThisSum = 0;
    for(size_t i = 0; i < A.size(); ++i) {
        for(size_t j = i; j < A.size(); ++j) {
            ThisSum += A[j];
            if(ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }

    return ThisSum;
}



int main()
{

    return 0;
}

