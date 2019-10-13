#include <algorithm>
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
  Heap() : count(0) {}

  int top() {}

  void pop() {}

  void push(int i) {}

  void clear() {}

 protected:
  void siftUp(int i) {}

  void siftDown(int i) {}

 private:
  std::vector<int> data_;
  int count;
};

void test_heap_sort(int length, int method = 1) {
  vector<int> arr;
  for (auto i = 0; i < length; i++) {
    auto e = std::rand() % length;
    arr.emplace_back(e);
  }
  print_result(arr, 0, -1, arr.size());

  auto start = std::chrono::steady_clock().now();
  if (method == 1) {
    // bubble_sort(arr);
  } else if (method == 2) {
    // select_sort(arr);
  } else {
    // insert_sort(arr);
  }
  auto duration = std::chrono::steady_clock().now() - start;
  printf("simple sort method %d total %d elements cost %lld.%03lld seconds\n",
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
  static int count;
  if (pos == -1) {
    count = 0;
  }
  printf("%2d@ ", count);
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
  count++;
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
  test_heap_sort(size, 2);
  test_heap_sort(size, 3);

  return 0;
}
