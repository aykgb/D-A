/*
 * @lc app=leetcode id=460 lang=cpp
 *
 * [460] LFU Cache
 *
 * https://leetcode.com/problems/lfu-cache/description/
 *
 * algorithms
 * Hard (30.61%)
 * Likes:    872
 * Dislikes: 89
 * Total Accepted:    50.1K
 * Total Submissions: 163.7K
 * Testcase Example:
 * '["LFUCache","put","put","get","put","get","get","put","get","get","get"]\n[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]'
 *
 * Design and implement a data structure for Least Frequently Used (LFU) cache.
 * It should support the following operations: get and put.
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reaches its capacity, it should invalidate the least
 * frequently used item before inserting a new item. For the purpose of this
 * problem, when there is a tie (i.e., two or more keys that have the same
 * frequency), the least recently used key would be evicted.
 *
 * Note that the number of times an item is used is the number of calls to the
 * get and put functions for that item since it was inserted. This number is
 * set to zero when the item is removed.
 *
 *
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 *
 *
 * Example:
 *
 *
 * LFUCache cache = new LFUCache(2); // 2 is capacity
 *
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.get(3);       // returns 3.
 * cache.put(4, 4);    // evicts key 1.
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 *
 */

#include <iostream>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;

// @lc code=start
class LFUCache {
 public:
  int count_;
  int capacity_;
  int min_frequency_;

  struct Node {
    int key;
    int value;
    int frequency;
    Node(int k, int v, int f) : key(k), value(v), frequency(f) {}
  };
  std::unordered_map<int, std::list<Node>> map_freq_data_;
  std::unordered_map<int, std::list<Node>::iterator> map_key_node_;

  LFUCache(int capacity) : count_(0), capacity_(capacity), min_frequency_(0) {}

  int get(int key) {
    // 1. 查找key
    // 2. 找到key，调整key对应节点位置，并返回
    // 3. 找不到key，返回-1
    auto search = map_key_node_.find(key);
    if (search != map_key_node_.end()) {
      auto& from_list = map_freq_data_[search->second->frequency++];
      auto& to_list = map_freq_data_[search->second->frequency];
      to_list.splice(to_list.begin(), from_list, search->second);
      map_key_node_[key] = to_list.begin();
      if (from_list.empty()) {
        if (min_frequency_ == search->second->frequency - 1) {
          min_frequency_++;  // !如果删除的是min_frequency_对应的list，则min_frequency_需要加1
        }
        map_freq_data_.erase(search->second->frequency - 1);
      }
      return to_list.front().value;
    }
    return -1;
  }

  void put(int key, int value) {
    if (capacity_ == 0 && count_ == 0) {
      return;
    }

    if (get(key) != -1) {
      map_key_node_[key]->value = value;
      return;
    }

    if (capacity_ == 0) {
      auto key_to_del = map_freq_data_[min_frequency_].back().key;
      map_freq_data_[min_frequency_].pop_back();
      map_key_node_.erase(key_to_del);
    } else {
      capacity_--;
      count_++;
    }

    min_frequency_ = 1;
    map_freq_data_[min_frequency_].emplace_front(
        Node(key, value, min_frequency_));
    map_key_node_.emplace(key, map_freq_data_[min_frequency_].begin());
  }

  void dump(bool reset = false) {
    static int counter = 0;
    if (reset) {
      counter = 0;
    }
    printf("%2dst@ \n", counter);
    struct Cmp {
      bool operator()(const int k1, const int k2) const { return k1 > k2; }
    };
    std::map<int, std::list<Node>, Cmp> map_freq_data_sorted_;
    for (auto iter = map_freq_data_.begin(); iter != map_freq_data_.end();
         iter++) {
      map_freq_data_sorted_.emplace(iter->first, iter->second);
    }

    for (auto iter = map_freq_data_sorted_.begin();
         iter != map_freq_data_sorted_.end(); iter++) {
      std::cout << "  freq " << iter->first << " -> ";
      auto data = iter->second;
      for (auto iter2 = data.begin(); iter2 != data.end(); iter2++) {
        std::cout << iter2->key << ":" << iter2->value << ":"
                  << iter2->frequency << " ";
      }
      std::cout << std::endl;
    }

    counter++;
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

void cache_get(LFUCache* cache, int key) {
  std::cout << "get " << key << ":" << cache->get(key) << std::endl;
  cache->dump();
}

void cache_put(LFUCache* cache, int key, int value) {
  cache->put(key, value);
  std::cout << "put " << key << ":" << value << std::endl;
  cache->dump();
}

/**
 * ["LFUCache","put","put","get","put","get","get","put","get","get","get"]
 * [[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
 */
void test_lfu_case01() {
  LFUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cache.get(1);
  cache.dump();
  cache.put(3, 3);
  cache.get(2);
  cache.get(3);
  cache.dump();
  cache.put(4, 4);
  cache.get(1);
  cache.get(3);
  cache.get(4);
  cache.dump();
}

void test_lfu_case00() {
  LFUCache cache(10);
  for (auto i = 0; i < 10; i++) {
    cache.put(i, i);
  }
  cache.dump();

  cache.get(0);
  cache.get(1);
  cache.get(2);
  cache.dump();

  cache.put(10, 10);
  cache.dump();

  cache.get(10);
  cache.get(9);
  cache.get(9);
  cache.get(4);
  cache.get(4);
  cache.dump();
}

int main() {
  // test_lfu_case00();
  test_lfu_case01();

  return 0;
}
