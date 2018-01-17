#include <iostream>
#include <vector>
#include <string>

#include <list>
#include <unordered_map>

using namespace std;

class LFUCache {
    using Key = int;
    using Value = int;
    using Frequency = int;

    struct CacheNode {
        Key key = -1;
        Value value = -1;
        Frequency frequency = 1;
        CacheNode(int k, int v): key(k), value(v) {}
    };

    int counter;
    /* 当前最小frequency。 */
    int min_freq;
    /* key到CacheNode*的映射，实现O(1)查找。*/
    std::unordered_map<Key, CacheNode*> map_node;
    /* frequency到std::list<Key>的映射关系。*/
    std::unordered_map<Frequency, std::list<Key>> map_list;
    /* Key 到 std::list<Key>::iterator 的映射关系。 */
    std::unordered_map<Key, std::list<Key>::iterator> map_iter;
public:
    LFUCache(int capacity): counter(capacity), min_freq(0) {

    }

    int get(int key) {
        auto iter_node = map_node.find(key);
        if(iter_node == map_node.end()) {
            return -1;
        }

        int &freq = iter_node->second->frequency;
        // 找到对应frequency的list
        auto &freq_list = map_list.find(freq)->second;
        // 找到对应frequency的list
        auto &iter = map_iter.find(key)->second;

        // 移除list中的key
        freq_list.erase(iter);
        // 更新node的frequency
        freq++;
        // 加入新的freq_list
        map_list[freq].push_front(key);

        if(map_list.find(min_freq) == map_list.end()) {
            min_freq++;
        }

        return iter_node->second->value;
    }

    void put(int key, int value) {
        if(get(key) != -1) {
            map_node[key]->value = value;
            return;
        }

        CacheNode *node = new CacheNode(key, value);
        map_node[key] = node;
        min_freq = 1;

        if(counter) {
            counter--;
            map_list[min_freq].push_front(key);
            map_iter[key] = map_list[min_freq].begin();
        } else { // 淘汰一个node
            auto& freq_list = map_list[min_freq];
            auto& key = freq_list.back();
            auto& iter = map_iter[key];

            freq_list.erase(iter);
            map_iter.erase(key);
            map_node.erase(key);
        }
    }
};


int main()
{
    LFUCache* cache = new LFUCache(2);
    cache->put(2, 1);
    cache->put(1, 1);
    cache->put(2, 3);
    cache->put(4, 1);
    std::cout << cache->get(2) << std::endl;

    return 0;
}
