#include <chrono>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_DISPLAY_SIZE = 20;
void print_result(vector<int>& arr, int begin, int pos, int end);

int partition(vector<int>& arr, int begin, int end);
int partition2(vector<int>& arr, int begin, int end);
void quick_sort(vector<int>& arr, int begin, int end) {
  if (begin < end) {
    int p = partition(arr, begin, end);
    print_result(arr, begin, p, end);
    quick_sort(arr, begin, p);
    quick_sort(arr, p + 1, end);
  }
}

void quick_sort2(vector<int>& arr, int begin, int end) {
  if (begin < end) {
    int p = partition2(arr, begin, end);
    print_result(arr, begin, p, end);
    quick_sort2(arr, begin, p);
    quick_sort2(arr, p + 1, end);
  }
}

// 使用栈的非递归方法
void quick_sort3(vector<int>& arr) {
  if (arr.size() < 2) {
    return;
  }
  auto beg = 0;
  auto end = arr.size();
  auto pos = partition2(arr, beg, end);
  print_result(arr, beg, pos, end);
  auto stk = std::stack<int>();
  if (pos > beg) {
    stk.push(beg);
    stk.push(pos);
  }
  if (pos < end - 1) {
    stk.push(pos + 1);
    stk.push(end);
  }

  while (!stk.empty()) {
    end = stk.top();  // !取出beg/end与它们的入栈顺序相反
    stk.pop();
    beg = stk.top();
    stk.pop();
    pos = partition2(arr, beg, end);
    print_result(arr, beg, pos, end);
    if (pos > beg) {
      stk.push(beg);
      stk.push(pos);
    }
    if (pos < end - 1) {
      stk.push(pos);
      stk.push(end);
    }
  }
}

// 算法导论版
int partition(vector<int>& arr, int begin, int end) {
  auto idx = begin + std::rand() % (end - begin);
  std::swap(arr[begin], arr[idx]);

  int pos = begin;
  int pivot = arr[begin];
  for (int i = begin + 1; i != end; i++) {
    if (arr[i] <= pivot) {
      pos++;
      if (pos != i) {
        std::swap(arr[pos], arr[i]);
      }
    }
  }
  std::swap(arr[pos], arr[begin]);
  return pos;
}

// 双指针法，不需要使用交换函数
int partition2(vector<int>& arr, int begin, int end) {
  auto idx = begin + std::rand() % (end - begin);
  std::swap(arr[begin], arr[idx]);
  auto pivot = arr[begin];
  while (begin < end) {
    while (begin < end && arr[--end] > pivot)
      ;
    arr[begin] = arr[end];
    while (begin < end && arr[++begin] <= pivot)
      ;
    arr[end] = arr[begin];
  }
  arr[begin] = pivot;
  return begin;
}

void test_quick_sort(int length, int method = 1) {
  vector<int> arr;
  for (auto i = 0; i < length; i++) {
    auto e = std::rand() % length;
    arr.emplace_back(e);
  }
  print_result(arr, 0, -1, arr.size());

  auto start = std::chrono::steady_clock().now();
  if (method == 1) {
    quick_sort(arr, 0, arr.size());
  } else if (method == 2) {
    quick_sort2(arr, 0, arr.size());
  } else {
    quick_sort3(arr);
  }
  auto duration = std::chrono::steady_clock().now() - start;
  printf("quick sort %d int numbers cost %lld.%03lld seconds\n", length,
         duration / chrono::seconds(1),
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

  test_quick_sort(size);
  test_quick_sort(size, 2);
  test_quick_sort(size, 3);
  return 0;
}

// * 非递归方法由于使用了栈，实际性能差很多
/**
quick sort 100000000 int numbers cost 11.502 seconds
result: 1 2 3 6 6 6 13 13 13 15  ... 99999991 99999991 99999991 99999991
99999993 99999993 99999994 99999996 99999998 99999998

quick sort 100000000 int numbers cost 11.313 seconds
result: 0 0 1 1 1 3 3 3 3 4  ... 99999994 99999994 99999994 99999995 99999996
99999996 99999997 99999998 99999999 99999999

quick sort 100000000 int numbers cost 16.602 seconds
result: 0 1 1 1 2 5 7 8 9 9  ... 99999992 99999992 99999993 99999994 99999995
99999996 99999996 99999996 99999997 99999999

 */