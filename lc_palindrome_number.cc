#include <iostream>
#include <string>
#include <vector>

extern "C" {
#include <limits.h>
}

// 注：需要处理整数溢出
int64_t interger_power(int64_t x, int exp) {
    if(x == 0) {
        return 0;
    }

    if(exp == 0) {
        return 1;
    }

    int64_t result = x;
    for(int i = 1; i < exp; i++) {
        result *= x;
    }
    return result;
}

// 获取输入x的任意一位上的数的大小，其中pos指向输入的位数 1-base 如：1234 4在1位
int get_digit_on_position(int x, int pos) {
    x = x % interger_power(10, pos); // 先余再除 如： 获得4312 中第4位数字 534312 % 10000 = 4312, 4312 / 1000 = 4
    x = x / interger_power(10, pos - 1);

    return x;
}

class Solution {
public:
    bool isPalindrome(int x) {
        // 边界值处理  -(-2147483648) == -2147483648 ????
        if( x == INT_MIN ) {
            return false;
        }

        // 只处理正整数
        if(x < 0) {
            return false;
        }

        // 只有一位，直接返回
        if(x / 10 == 0) {
            return true;
        }

        // 计算输入整数的长度
        int nums = 0;
        int x1 = x;
        while(x1) {
            nums++;
            x1 = x1 / 10;
        }

        // 使用双指针法，分别从头和尾迭代到中间，逐次比较是否相同，若有一个不相同，就不是回文数
        for(int i = 1; i <= nums/2; i++) {
            int low = get_digit_on_position(x, i);
            int high = get_digit_on_position(x, nums - i + 1);
            if( low != high) {
                return false;
            }
        }

        return true;
    }
};

bool isPalindrome(int x) {
    int sum = 0;
    while(x > 0) {
        sum = sum * 10 + x % 10;
        if(x == sum) {
            return true;
        }
        x = x / 10;
        if(x == sum) {
            return true;
        }
    }

    return false;
}

int main()
{
    int x = -1410110141;
    x = 1111;
    std::cout << (x == INT_MIN) << std::endl;

    Solution solution;
    bool flag = solution.isPalindrome(x);
    flag = isPalindrome(x);

    std::cout << flag << std::endl;

    return 0;
}
