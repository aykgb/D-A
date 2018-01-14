#include <iostream>
#include <vector>
#include <functional>
#include <utility>

using namespace std;

using IsLeaf = std::function<bool(int)>;
using IsGoal = std::function<bool(int)>;

// find if there is any possible solution.
bool solve0(vector<int>& nums, int i, IsLeaf is_leaf, IsGoal is_goal) {
    if(is_leaf(nums[i])) {
        if(is_goal(nums[i])) {
            return true;
        } else {
            return false;
        }
    } else {
        if(solve0(nums, i + 1, is_leaf, is_goal)) {
            return true;
        } else {
            return false;
        }
    }

}

// find how many solution of this problem.
void solve1(vector<int>& nums, int i, IsLeaf is_leaf, IsGoal is_goal, int& cnt) {
    if(is_leaf(nums[i])) {
        if(is_goal(nums[i])) {
            cnt++;
            return;
        } else {
            return;
        }
    } else {
        return solve1(nums, i + 1, is_leaf, is_goal, cnt);
    }
}

// find and record all solution of the probles.
void solve2(vector<int>& nums, int i, IsLeaf is_leaf, IsGoal is_goal, vector<vector<int>> result) {
    vector<int> this_result;
    if(is_leaf(nums[i])) {
        if(is_goal(nums[i])) {
            this_result.emplace_back(nums[i]);
            return;
        } else {
            return;
        }
    } else {
        return solve2(nums, i + 1, is_leaf, is_goal, result);
    }
}

int main()
{
    return 0;
}
