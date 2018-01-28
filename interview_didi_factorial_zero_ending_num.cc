#include <iostream>
#include <vector>

using namespace std;

/*输入一个正整数n,求n!(即阶乘)末尾有多少个0？ 比如: n = 10; n! = 3628800,所以答案为2
 */

int solution(int n) {
    int result = 0;
    for(int i = 5; n / i > 0; i *= 5) {
        result += n / i;
    }

    return result;
}

int main()
{

    std::cout << solution(100) << std::endl;
    return 0;
}
