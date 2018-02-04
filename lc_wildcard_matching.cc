#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int NS = s.size();
        int NP = p.size();

        int i, j;
        for(i = 0, j = 0; i < NS, j < NP; i++, j++) {
            if(p[j] != '*') {
                if(s[i] == p[j] || p[j] == '?') {
                    continue;
                } else {
                    return false;
                }
            } else {
                if(j == NP - 1) { // 如果*在p的结尾处，直接匹配成功
                    return true;
                }

                // 找到s中与p[j + 1] 相同的字符来尝试匹配
                while(s[i++] != p[j + 1]) {
                    if(i > NS) {
                        return false;
                    }
                }

                isMatch()
            }
        }

        if(i != NS || j != NP) { return false; }

        return true;
    }
};

int main()
{
    std::cout << Solution().isMatch("abefcdgiescdfimde", "ab*cd?i*de") << std::endl;

    return 0;
}
