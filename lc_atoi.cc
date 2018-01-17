#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

#include <climits>

using namespace std;

class Solution {
public:
    int char2int(const char& c) {
        if(c >= '0' || c <= '9') return c - '0';
        return 0;
    }

    bool is_digit(const char& c) {
        if(c < '0' || c > '9') return false;
        return true;
    }

    int myAtoi(string str) {
        int pos = 0;
        int space = 0;      // 计数空格
        int flag = +1;      // 符号位
        while(str[pos] == ' ') {    // 跳过空格
            pos++;
            space++;
        }

        while(!is_digit(str[pos])) {
            if(str[pos] == '-') {
                flag = -1;
            } else if(str[pos] == '+') {

            } else {
                return 0;
            }

            pos++;

            if(pos > 1 + space) {
                return 0;
            }
        }

        int len = str.size();
        if(len == 0) {
            return 0;
        }

        long long int sum = 0;
        for(int i = pos; i < len; i++) {
            sum = sum * 10 + char2int(str[i]);
            if(sum * flag > INT_MAX) {
                return INT_MAX;
            }
            if(sum * flag < INT_MIN) {
                return INT_MIN;
            }
        }

        return sum * flag;
    }

    int myAtoi2(string str) {
        int sign = 1;
        // 跳过空格
        int pos = str.find_first_not_of(' ');
        // 检查符号位
        if(str[pos] == '-' || str[pos] == '+') {
            sign = (str[pos++] == '-') ? -1 : 1;
        }
        // 逐位累加
        int res = 0;
        while(isdigit(str[pos])) { // 遇到非数字字符会自动跳过
            res = res * 10 + (str[pos++] - '0');
            if(res > INT_MAX) {
                return sign > 0 ? INT_MAX : INT_MIN;
            }
        }
        return sign * res;
    }

};

int main()
{
    int res = Solution().myAtoi2("   010");
    std::cout << res << std::endl;

    return 0;
}
