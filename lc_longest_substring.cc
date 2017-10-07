#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <assert.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max_sub_length = 0;
        int max_sub_index = 0;

        int sub_length= 0; // current substring length.
        int sub_index = 0; // current substring started sub_index.
        std::unordered_map<char, int> visited; // the total characters is limited to 128.
        for(size_t i = 0; i < s.length(); i++) {
            auto search = visited.find(s[i]);
            if(search != visited.end()) {  // line A
                int repeated_pos = search->second; // the position of repeated character in the substring.
                if(sub_length > max_sub_length) {
                    max_sub_length = sub_length;
                    max_sub_index = sub_index;
                    std::cout << "substr: ";
                    for(size_t j = sub_index; j < i; j++) {
                        std::cout << s[j] << " ";
                    }
                    std::cout << std::endl;
                }
                for(int j = sub_index; j < repeated_pos; j++){ // update visited;
                    visited.erase(s[j]);
                }

                sub_index = repeated_pos + 1; // update sub_index;
                sub_length = i - repeated_pos; // update sub_length;
                visited[s[i]] = i;  // update the character position in map.
           } else {
                sub_length++;
                visited[s[i]] = i;
            }
        }

        if(sub_length > max_sub_length) {
            max_sub_length = sub_length;
            max_sub_index = sub_index;
            std::cout << "substr: ";
            for(int i = max_sub_index; i < sub_index + sub_length; i++) {
                std::cout << s[i] << " ";
            }
            std::cout << std::endl;
        }

        return max_sub_length;
    }
};

/* Sliding Window. */
class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        std::unordered_set<int> hash_set;
        int ans = 0, i = 0, j = 0;
        while(i < n && j < n) {
            auto search = hash_set.find(s[j]);
            if(search == hash_set.end()) {
                hash_set.emplace(s[j++]);
                ans = std::max(ans, j - i);
            } else {
                hash_set.erase(s[i++]);
            }
        }

        return ans;
    }
};
/* eg:
 * s = "abcdbefgch"
 * when i = 0, j = 4, s[j] is 'b', hash_set is {'a', 'b', 'c', 'd'} and contains 'b',
 * so erase s[i](i = 0, 1) from hash_set until it does not contain 'b', and do emplace s[j] again.
 * */
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0, len = 0, max_len = 0;
        std::unordered_set<char> window; // the total characters is limited to 128.
        for(size_t i = 0; i < s.length(); i++) {
            auto search = window.find(s[i]);
            if(search != window.end()) {
                while(s[start] != s[i]) { // find new start position.
                    window.erase(s[start++]);  // update hash_set
                }

                len = i - start + 1; // update len
            } else {
                window.emplace(s[i]);
                len++;
                if(len > max_len) {
                    max_len = len;
                }
            }
        }

        return max_len;
    }
};



string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (size_t i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

// input eg: "abbaceabcefghc"
int main() {
    string line;
    while (getline(cin, line)) {
        string s = stringToString(line);
        std::cout << "s: " << s << std::endl;

        int ret = Solution2().lengthOfLongestSubstring(s);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
