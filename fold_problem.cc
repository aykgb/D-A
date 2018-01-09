#include <iostream>
#include <vector>

using namespace std;

/* 思路：输出结果可表示为一棵树
 *           down
 *          /    \
 *        down   up
 *       /  \   /   \
 *      down up down  up
 *  规律：
 *  所有左子树的头部都是down的
 *  所有右子树的头部都是up的
 *  从（纸的）上到下输出折痕结果是一个先序遍历的过程（左根右）

 *  n: 总共需要折几次， 1-base
 *  i: 当前所在的折痕是第几次折叠产生的，0-base
 *  flag：是down 还是 up
 */
void print_result(int n, int i, bool flag) {
    if(i < n) {
        i++;
        print_result(n, i, true);   // 这里迭代到左子树
        if(flag) {                  // 这里是输出当前层结果。
            std::cout << " down ";
        } else {
            std::cout << " up";
        }
        print_result(n, i, false);  // 这里迭代到右子树
    }
}

int main()
{
    print_result(3, 0, true);

    return 0;
}
