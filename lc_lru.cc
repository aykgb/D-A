#include <iostream>
#include <limits>
#include <vector>

#include <list>
#include <unordered_map>

using namespace std;

/* 使用LRU1算法
 * */
class LRUCache {
  /* 链表，实际保存数据 */
  struct CacheNode {
    int key;
    int value;

    CacheNode *next, *prev;
    CacheNode(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
  } * cache;  // 这是一个dummy的假头节点
  CacheNode *tail;

  void remove(CacheNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
  }

  void insert_from_head(CacheNode *node) {
    node->next = cache->next;
    node->prev = cache;
    cache->next = node;
    node->next->prev = node;
  }

  void move_to_head(CacheNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    insert_from_head(node);
  }

  /* 用于减计数缓存空间，初始大小为capacity，每put一个node减1，remove一个node加1.
   */
  int counter;

  /* 用于查询，和实现在list中O(1)的插入删除数据. */
  std::unordered_map<int, CacheNode *> cache_map;

 public:
  LRUCache(int capacity) : counter(capacity) {
    // 一个cache中最少包含2个节点，用于简化逻辑
    cache = new CacheNode(-1, -1);
    tail = new CacheNode(-1, -1);
    cache->next = tail;
    tail->prev = cache;
  }

  ~LRUCache() {
    while (cache) {
      CacheNode *curr = cache;
      cache = cache->next;
      delete curr;
    }
  }

  int get(int key) {
    auto iter = cache_map.find(key);
    if (iter == cache_map.end()) {
      return -1;
    }

    // 将查询到的节点移动到头部
    CacheNode *node = iter->second;
    move_to_head(node);

    return node->value;
  }

  void put(int key, int value) {
    if (get(key) != -1) {
      CacheNode *node = cache_map[key];
      node->value = value;
      return;
    }

    // 将数据加入cache
    CacheNode *node = new CacheNode(key, value);
    insert_from_head(node);
    // 更新cache_map
    cache_map.emplace(key, node);
    // 更新计数
    if (counter) {
      counter--;
    } else {
      CacheNode *node = tail->prev;
      cache_map.erase(node->key);
      remove(node);
    }
  }
};

int main() {
  LRUCache *cache = new LRUCache(2);
  cache->put(2, 1);
  cache->put(1, 1);
  cache->put(2, 3);
  cache->put(4, 1);
  std::cout << cache->get(1) << std::endl;
  std::cout << cache->get(2) << std::endl;

  return 0;
}
