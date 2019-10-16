#include <iostream>
#include <string>
#include <vector>

#include <list>
#include <unordered_map>

using namespace std;

class LFUCache {
  using Key = int;
  using Value = int;
  using Frequency = int;

  /* 当前cache中数据。*/
  int size;
  /* cache 大小。*/
  int capacity;
  /* 当前最小frequency。 */
  int min_freq;
  /* key到CacheNode*的映射，实现O(1)查找。*/
  std::unordered_map<Key, std::pair<Value, Frequency>> map_key2pair_of_val_freq;
  /* frequency到std::list<Key>的映射关系。*/
  std::unordered_map<Frequency, std::list<Key>> map_freq2key_list;
  /* Key 到 std::list<Key>::iterator 的映射关系。 */
  std::unordered_map<Key, std::list<Key>::iterator> map_key2list_iter;

 public:
  void dump() {
    std::cout << "-----------------------" << std::endl;
    std::cout << " size:" << size << std::endl;
    std::cout << " capacity:" << capacity << std::endl;
    std::cout << " min_freq:" << min_freq << std::endl;

    std::cout << " dump map_key2pair_of_val_freq:\n";
    for (auto &e : map_key2pair_of_val_freq) {
      std::cout << " @key:" << e.first << " value:" << e.second.first
                << " freq:" << e.second.second << "\n";
    }
    std::cout << std::endl;

    std::cout << " dump map_freq2key_list:\n";
    for (auto &e : map_freq2key_list) {
      std::cout << " @freq:" << e.first << " list: [ ";
      for (auto &ee : e.second) {
        std::cout << ee << "<->";
      }
      std::cout << " ]\n";
    }
    std::cout << std::endl;

    std::cout << " dump map_key2list_iter:\n";
    for (auto &e : map_key2list_iter) {
      std::cout << " @key:" << e.first << " iter:" << &e.second << "\n";
    }
    std::cout << "-----------------------" << std::endl;
  }

 public:
  LFUCache(int cap) : size(0), capacity(cap), min_freq(0) {}

  int get(int key) {
    if (map_key2pair_of_val_freq.count(key) == 0) {
      return -1;
    }
    int &freq = map_key2pair_of_val_freq[key].second;

    // 从map_freq_list和map_list_iter中移除key对应的信息
    map_freq2key_list[freq].erase(map_key2list_iter[key]);
    map_key2list_iter.erase(key);

    freq++;

    // 更新到map_freq_list和map_list_iter中
    map_freq2key_list[freq].push_front(key);
    map_key2list_iter[key] = map_freq2key_list[freq].begin();

    // 更新min_freq
    if (map_freq2key_list[min_freq].size() == 0) {
      min_freq++;
    }

    return map_key2pair_of_val_freq[key].first;
  }

  void put(int key, int value) {
    if (capacity <= 0) {
      return;
    }

    if (get(key) != -1) {
      map_key2pair_of_val_freq[key].first = value;
      return;
    }

    if (size == capacity) {  // cache 已满，淘汰一个node
      auto &freq_list = map_freq2key_list[min_freq];
      int &key = freq_list.back();
      freq_list.pop_back();
      map_key2list_iter.erase(key);
      map_key2pair_of_val_freq.erase(key);
      size--;
    }

    // 加入一个新的node
    min_freq = 1;
    map_key2pair_of_val_freq[key] = {value, min_freq};
    map_freq2key_list[min_freq].push_front(key);
    map_key2list_iter[key] = map_freq2key_list[min_freq].begin();
    size++;
  }
};

int main() {
  LFUCache *cache = new LFUCache(3);
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
