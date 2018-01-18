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
        Key key;
        Value value;
        Frequency frequency;
        std::list<Key>::iterator iter;

        CacheNode(int k, int v):
            key(k), value(v), frequency(1) {  }
    };

    /* 当前cache中数据。*/
    int size;
    /* cache 大小。*/
    int capacity;
    /* 当前最小frequency。 */
    int min_freq;
    /* key到CacheNode*的映射，实现O(1)查找。*/
    std::unordered_map<Key, CacheNode*> map_key_node;
    /* frequency到std::list<Key>的映射关系。*/
    std::unordered_map<Frequency, std::list<Key>> map_freq_list;
public:
    void dump() {
        std::cout << "-----------------------" << std::endl;
        std::cout << " size:" << size << std::endl;
        std::cout << " capacity:" << capacity << std::endl;
        std::cout << " min_freq:" << min_freq << std::endl;

        std::cout << " dump cache:\n";
        for(auto &e : map_key_node) {
            std::cout << " @key:" << e.first
                      << " value:" << e.second->value
                      << " frequency:" << e.second->frequency
                      << " iter: " << &e.second->iter << "\n";
        }
        std::cout << std::endl;

        std::cout << " dump map_freq_list:\n";
        for(auto &e: map_freq_list) {
            std::cout << " @freq:" << e.first
                      << " list: [ ";
            for(auto &ee : e.second) {
                std::cout << ee << "<->";
            }
            std::cout << " ]\n";
        }
        std::cout << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

public:
    LFUCache(int cap): size(0), capacity(cap), min_freq(0) {

    }

    ~LFUCache() {
        for(auto &e : map_key_node) {
            CacheNode *node = e.second;
            delete node;
        }
    }

    int get(int key) {
        if(map_key_node.count(key) == 0) {
            return -1;
        }

        CacheNode *node = map_key_node[key];
        // 从map_freq_list中移除key对应的信息
        map_freq_list[node->frequency].erase(node->iter);

        node->frequency++;

        // 更新到map_freq_list和map_list_iter中
        map_freq_list[node->frequency].push_front(key);
        node->iter = map_freq_list[node->frequency].begin();

        // 更新min_freq
        if(map_freq_list[min_freq].size() == 0) {
            min_freq++;
        }

        return node->value;
    }

    void put(int key, int value) {
        if(capacity <= 0) {
            return;
        }

        if(get(key) != -1) {
            map_key_node[key]->value = value;
            return;
        }

        if(size == capacity) { // cache 已满，淘汰一个node
            auto& freq_list = map_freq_list[min_freq];
            int key = freq_list.back();
            freq_list.pop_back();

            auto node = map_key_node[key];
            delete node;

            map_key_node.erase(key);
            size--;
        }

        // 加入一个新的node
        min_freq = 1;
        map_key_node[key] = new CacheNode(key, value);
        map_freq_list[min_freq].push_front(key);
        map_key_node[key]->iter = map_freq_list[min_freq].begin();
        size++;
    }
};


int main()
{
    LFUCache* cache = new LFUCache(3);
    cache->put(2, 2);
    cache->put(1, 1);
    cache->dump();
    std::cout << cache->get(2) << std::endl;
    std::cout << cache->get(1) << std::endl;
    std::cout << cache->get(2) << std::endl;
    cache->put(3, 3);
    cache->put(4, 4);
    std::cout << cache->get(3) << std::endl;
    std::cout << cache->get(2) << std::endl;
    std::cout << cache->get(1) << std::endl;
    std::cout << cache->get(4) << std::endl;
    cache->dump();

    return 0;
}
