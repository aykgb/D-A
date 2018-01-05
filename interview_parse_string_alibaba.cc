#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

/* eg: "[ 0 [ 1 2 ] [ 3 4 [ 5 6 ] ] 7 ]"
 * 解析到内存，根据用户指定的坐标访问其中的数据.
 * 说明：[] 的深度代表维度，如:
 *      访问6，其坐标是{2, 2, 1}
 *      访问2，使用坐标{1, 2}
 * */

// 一个闭合的[]抽象为一个Cell
struct Cell{
    /* 代表这个cell所处的维度 */
    int dimension;

    /*表示在该维度下当前可插入的slot索引
     *            [ 1 2 3 [ 4 5 6 ] ]
     *              ^ ^ ^     ^
     *slot_id:   0 1 2     3
    */
    int slot_id; // slot index 指向下一个可用slot的索引

    std::unordered_map<int, string> direct_access; // 可直接access的元素，说明在该维度存在
    std::unordered_map<int, Cell*> high_dimension; // 存在比该维度更高的维度之上，需要递归到高维度cell上去

    Cell(): dimension(0), slot_id(0) {  }

    std::string find(std::vector<int> coordinate) {
        if(coordinate.empty()) {
            return "invalid coordinate.";
        }

        int ind = coordinate[0];
        if(direct_access.count(ind)) {
            return direct_access[ind];
        } else {
            if(coordinate.size() == 1) { // 不再向下递归
                if(high_dimension.count(ind)) {
                    return high_dimension[ind]->traversal_itself();
                } else {
                    return "invalid coordinate.";
                }
            }
            return high_dimension[ind]->find({coordinate.begin() + 1, coordinate.end()});
        }
    }

    // 使用递归的方式，遇到可direct_access的元素就直接访问，遇到不可direct_access的元素递归的traversal
    string traversal_itself() {
        string result;
        result.append("[ ");
        for(int i = 0; i < slot_id; i++) {
            if(direct_access.count(i)) {
                result.append(direct_access[i]);
                result.push_back(' ');
            } else {
                result.append(high_dimension[i]->traversal_itself());
            }
        }

        result.append("] ");

        return result;
    }
};

Cell* parse_expression(const std::vector<string>& vec_str) {
    std::stack<Cell*> cell_stack;

    int i = 1;   // 表示当前指向的字符串的索引
    int dim = 0; // 表示当前所处的维度
    Cell *root = new Cell;
    cell_stack.push(root);
    while(!cell_stack.empty()) {
        if(vec_str[i] == "[") {
            dim++;

            Cell *cur = new Cell;
            cur->dimension = dim;

            Cell *parent = cell_stack.top();
            parent->high_dimension.emplace(parent->slot_id, cur);
            parent->slot_id++;

            cell_stack.push(cur);

        } else if(vec_str[i] == "]") {
            dim--;
            cell_stack.pop();
        } else {
            Cell * cur = cell_stack.top();
            cur->direct_access.emplace(cur->slot_id, vec_str[i]);
            cur->slot_id++;
        }

        i++;
    }

    return root;
}

int main()
{
    const std::string str = "[ 0 [ 1 2 ] [ 3 4 [ 5 6 ] ] 7 [ [ [ [ 8 ] ] ] ] ]";
    std::istringstream iss(str);
    std::vector<string> out;

    std::copy(istream_iterator<string>(iss),
            istream_iterator<string>(),
            std::back_inserter(out));

    Cell *root = parse_expression(out);
    // std::vector<int> coordinate{2, 2};
    // std::vector<int> coordinate{2, 2, 1};
    // std::vector<int> coordinate{2, 2, 2};
    std::vector<int> coordinate{4, 0, 0, 0, 0};
    string fetch = root->find(coordinate);

    std::cout << "input string: " << str << std::endl;
    std::cout << "input coordinate: " << "( ";
    for(auto & e: coordinate) {
        std::cout << e << ", ";
    }
    std::cout << ")" << std::endl;
    std::cout << fetch << std::endl;

    return 0;
}
