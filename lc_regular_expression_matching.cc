#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p) {
        if(p.empty()) return s.empty();
        if('*' == p[1])
            return (isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)));
        else
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }

};

int main()
{
    std::cout << Solution().isMatch("aaa", ".*") << std::endl;      // true
    std::cout << Solution().isMatch("aaab", "a*b") << std::endl;    // true;
    std::cout << Solution().isMatch("b", "a*b") << std::endl;       // true
    std::cout << Solution().isMatch("b", "*b") << std::endl;        // false
    std::cout << Solution().isMatch("*b", "*b") << std::endl;       // true

    return 0;
}

