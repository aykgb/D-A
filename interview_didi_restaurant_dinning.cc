#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*某餐馆有n张桌子，每张桌子有一个参数：a 可容纳的最大人数； 有m批客人，每批客人有两个参数:b人数，c预计消费金额。
 * 在不允许拼桌的情况下，请实现一个算法选择其中一部分客人，使得总预计消费金额最大
 */

/*方案：贪心算法，对客人按money降序排序，对桌子按可容纳人数升序排序，优先满足money最大的一批用户。*/

using namespace std;

struct Guest {
    int num;
    int money;
};

bool compatator(const Guest& g1, const Guest& g2) {
    if(g1.money > g2.money) {
        return true;
    } else if(g1.money < g2.money) {
        return false;
    } else {
        if(g1.num > g2.num) {
            return true;
        } else {
            return false;
        }
    }
}

int main()
{
    vector<Guest> guests{{10, 1000}, {2, 200}, {3, 400}, {5, 800}, {2, 150}, {3, 300}, {9, 1200}};
    multiset<int> tables{2, 2, 4, 4, 4 ,4, 6, 6, 6, 6, 9, 9, 9, 12, 12};
    std::sort(guests.begin(), guests.end(), compatator);

    int capital = 0;
    for(size_t i = 0; i < guests.size(); i++) {
        if(tables.empty()) {
            break;
        }

        auto table = tables.lower_bound(guests[i].num);
        if(table != tables.end()) {
            capital += guests[i].money;
            std::cout << "Arrangment: guest {" << guests[i].num << ", " << guests[i].money << "}"
                      << " table: " << *table << std::endl;
            tables.erase(table);
        }
    }
    std::cout << "capital: " << capital << std::endl;
#if 0
    auto print_guests =  [&]() {
        std::cout << "{";
        for(auto &g : guests) {
            std::cout << "{" << g.num << ", " << g.money << "}, ";
        }
        std::cout << "}" <<  std::endl;
    };
    print_guests();
#endif

    return 0;
}
