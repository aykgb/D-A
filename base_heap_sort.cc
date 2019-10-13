#include <assert.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_DISPLAY_SIZE = 20;
void print_result(vector<int>& arr, int begin, int pos, int end);

static int lhs(int i) { return 2 * i + 1; }
static int rhs(int i) { return 2 * i + 2; }
static int parent(int i) { return (i - 1) / 2; }

class Heap {
 public:
  Heap() : count_(0) {}
  Heap(vector<int>&& data) : data_(data) {  //! 移动构造函数
    /**
     * 加入一个二叉树有N(>1)个节点，那么按层遍历，这棵树的最后一个非叶子
     * 节点是第N/2个，线性结构存储索引为N/2 - 1
     */
    count_ = data_.size();
    for (auto i = count_ / 2 - 1; i > -1; i--) {
      siftDown(i);
    }
  }

  bool empty() const { return (0 == count_); }

  int top() { return data_[0]; }

  void pop() {
    data_[0] = data_[--count_];
    data_.resize(count_);
    siftDown(0);
  }

  void push(int item) {
    auto i = count_++;
    data_.emplace_back(item);
    siftUp(i);
  }

  void clear() {
    count_ = 0;
    data_.resize(0);
  }

 protected:
  void siftUp(int i) {
    assert(i < count_);
    while (i > 0) {
      int p = parent(i);
      if (data_[i] < data_[p]) {
        std::swap(data_[i], data_[p]);
        i = p;
      } else {
        break;
      }
    }
  }

  void siftDown(int i) {
    // print_result(data_, 0, i, count_);
    while (i < count_) {
      auto li = lhs(i);
      auto ri = rhs(i);
      auto smallest = i;  //! 求一个最小子树中的最小的节点索引
      if (li < count_ && data_[smallest] > data_[li]) {
        smallest = li;
      }
      if (ri < count_ && data_[smallest] > data_[ri]) {
        smallest = ri;
      }
      if (smallest != i) {
        std::swap(data_[i], data_[smallest]);
      } else {
        break;
      }
      i = smallest;
    }
  }

  void take(vector<int>& data) {
    data = std::move(data_);
    count_ = 0;
    data.resize(0);
  }

 private:
  std::vector<int> data_;
  int count_;
};

void heap_sort(vector<int>& arr) {
  Heap heap(std::move(arr));
  arr.resize(0);
  while (!heap.empty()) {
    arr.emplace_back(heap.top());
    heap.pop();
    // print_result(arr, 0, -1, arr.size());
  }
}

void test_heap_sort(int length, int method = 1) {
  vector<int> arr;
  for (auto i = 0; i < length; i++) {
    auto e = std::rand() % length;
    arr.emplace_back(e);
  }
  print_result(arr, 0, -1, arr.size());

  auto start = std::chrono::steady_clock().now();
  if (method == 1) {
    heap_sort(arr);
  } else if (method == 2) {
    // select_sort(arr);
  } else {
    // insert_sort(arr);
  }
  auto duration = std::chrono::steady_clock().now() - start;
  printf("heap sort method %d total %d elements cost %lld.%03lld seconds\n",
         method, length, duration / chrono::seconds(1),
         duration % chrono::seconds(1) / chrono::milliseconds(1));

  printf("result: ");
  if (arr.size() <= MAX_DISPLAY_SIZE) {
    for (auto i = 0; i < arr.size(); i++) {
      std::cout << arr[i] << " ";
    }
  } else {
    for (auto i = 0; i < MAX_DISPLAY_SIZE / 2; i++) {
      std::cout << arr[i] << " ";
    }
    std::cout << " ... ";
    for (auto i = 0; i < MAX_DISPLAY_SIZE / 2; i++) {
      std::cout << arr[arr.size() - 10 + i] << " ";
    }
  }
  std::cout << "\n\n";
  return;
}

void print_result(vector<int>& arr, int begin, int pos, int end) {
  if (arr.size() > MAX_DISPLAY_SIZE) {
    return;
  }
  static int count_;
  if (pos == -1) {
    count_ = 0;
  }
  printf("%2d@ ", count_);
  for (auto i = 0; i < arr.size(); i++) {
    if (i == begin) {
      std::cout << "( ";
    }
    if (i != pos) {
      std::cout << arr[i] << " ";
    } else {
      std::cout << "[" << arr[i] << "] ";
    }
    if (i + 1 == end) {
      std::cout << ") ";
    }
  }
  printf("  #begin:%d pos:%d end:%d", begin, pos, end);
  count_++;
  std::cout << endl;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "parameter error.\n";
    return -1;
  }
  auto para = argv[1];
  auto size = std::stoi(string(para));

  test_heap_sort(size);

  return 0;
}
