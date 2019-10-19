/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 *
 * https://leetcode.com/problems/lru-cache/description/
 *
 * algorithms
 * Medium (27.74%)
 * Likes:    3756
 * Dislikes: 152
 * Total Accepted:    366.3K
 * Total Submissions: 1.3M
 * Testcase Example:
 * '["LRUCache","put","put","get","put","get","put","get","get","get"]\n[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put.
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reached its capacity, it should invalidate the least recently
 * used item before inserting a new item.
 *
 * The cache is initialized with a positive capacity.
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 * Example:
 *
 *
 * LRUCache cache = new LRUCache(2);
 *
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 *
 *
 *
 *
 */

#include <iostream>

#include <list>
#include <unordered_map>

using namespace std;

// @lc code=start
class LRUCache {
  typedef std::pair<int, int> Node;

  int capacity_;
  std::list<Node> data_;  // !必须是kv pair，其中的k用于从hashmap中反查节点指针
  unordered_map<int, std::list<Node>::iterator> map_key2node_;

 public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    auto search = map_key2node_.find(key);
    // 1. 先查key
    if (search != map_key2node_.end()) {
      // 1.1. 找到key，更新key对应节点位置
      data_.splice(data_.begin(), data_, search->second);
      map_key2node_[key] = data_.begin();
      return data_.front().second;
    }
    // 1.2 否则返回-1
    return -1;
  }

  void put(int key, int value) {
    // 1. 先查找key
    if (get(key) != -1) {
      // 找到key，更新key对应的值
      map_key2node_[key]->second = value;
      return;
    }
    // 2. 否者判断cache容量
    if (capacity_ == 0) {
      // 容量不够删除尾节点
      map_key2node_.erase(data_.back().first);
      data_.pop_back();
    } else {
      // 还有容量，容量值减一
      capacity_--;
    }
    // 3. 插入新的节点
    data_.emplace_front(Node(key, value));
    map_key2node_.emplace(key, data_.begin());

    return;
  }

  void dump(bool reset = false) {
    static int counter = 0;
    if (reset) {
      counter = 0;
    }
    printf("%2dst@ ", counter);
    for (auto iter = data_.begin(); iter != data_.end(); iter++) {
      std::cout << " " << iter->first << ":" << iter->second;
    }
    std::cout << std::endl;
    counter++;
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

void cache_get(LRUCache *cache, int key) {
  std::cout << "get " << key << ":" << cache->get(key) << std::endl;  // returns 3
  cache->dump();
}

void cache_put(LRUCache *cache, int key, int value) {
  cache->put(key, value);
  std::cout << "put " << key << ":" << value << std::endl;  // returns 3
  cache->dump();
}


void test_lru_case00() {
  LRUCache* cache = new LRUCache(2);
  cache->dump(true);
  cache_put(cache, 1, 1);
  cache_put(cache, 2, 2);
  cache_get(cache, 1);
  cache_put(cache, 3, 3);
  cache_get(cache, 2);
  cache_put(cache, 4, 4);
  cache_get(cache, 1);
  cache_get(cache, 3);
  cache_get(cache, 4);

  delete cache;
}

void test_lru_case01() {
  /**
   *["LRUCache","put","get","put","get","get"]
   *[[1],[2,1],[2],[3,2],[2],[3]]
   */
  LRUCache* cache = new LRUCache(1);
  cache->dump(true);
  cache_put(cache, 2, 1);
  cache_get(cache, 2);
  cache_put(cache, 3, 2);
  cache_get(cache, 2);
  cache_get(cache, 3);
  delete cache;
}

int main() {
  test_lru_case00();
  test_lru_case01();
  return 0;
}
