#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        std::string reve;
        std::string integral = std::to_string(x);
        bool symbol = false;
        for(auto it = integral.rbegin(); it != integral.rend(); it++) {
            reve.push_back(*it);
        }

        if(reve.back() == '-') {
            symbol = true;
            reve = reve.substr(0, reve.length() - 1);
        }

        int res = 0;
        try {
            res = std::stoi(reve);
        } catch (std::out_of_range) {
            return 0;
        }

        return symbol ? -res : res;
    }
};

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line;
    while (getline(cin, line)) {
        int x = stringToInteger(line);

        int ret = Solution().reverse(x);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
