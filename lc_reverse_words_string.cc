#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    void reverseWord(string& s, int head, int tail) {
        while(head < tail) {
            char tmp = s[head];
            s[head++] = s[tail];
            s[tail--] = tmp;
        }
    }

    void trimSpace(string &s) {
        int i = 0;
        /* trim 掉字符串前面的空格 */
        while(s[i] == ' ') { i++; }
        s.erase(0 , i);
    }

    void reverseWords(string& s) {
        trimSpace(s);

        const int N = s.size();
        int i = 0;
        /* 逐个翻转整个字符串中所有单字。*/
        while(true) {
            // 找word的头索引
            while(s[i] == ' ' && i < N) { i++; }
            int word_head = i;

            // 找word的尾索引
            while(s[i] != ' ' && i < N) { i++; }
            int word_tail = i - 1;

            if(word_head < word_tail) {
                reverseWord(s, word_head, word_tail);
            }

            if(i > N - 1) {
                break;
            }
        }

        /* 把整个字符串当做一个单字翻转整个字符串 */
        reverseWord(s, 0, N - 1);

        trimSpace(s);
    }
};

int main()
{
    string s = "  a   b   ";
    std::cout << s << std::endl;
    Solution().reverseWords(s);
    std::cout << "|" << s << "|" << std::endl;

    return 0;
}
