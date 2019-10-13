#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_DISPLAY_SIZE = 20;
void print_result(vector<int>& arr, int begin, int pos, int end);

/**
 * 冒泡排序：
 * 遍历元素，不断比较上滤，总共需要排N-1趟，每排完一趟，下次遍历的元素个数就少一个
 */
void bubble_sort(vector<int>& arr) {
  int size = arr.size();
  bool swaped = false;
  for (int i = 0; i < size - 1; i++) {   //! 需要排size-1趟
    for (int j = 0; j < size - i - 1; j++) { //! 需要比较size - i次
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swaped = true;
      }
    }

    if (!swaped) {  // 如果其中有一次未发生交换，说明已经完全排序好了
      break;
    }
    swaped = false;
  }
}

/**
 * 选择排序：
 * 遍历未排序分组，找到最大元素的位置，放到未排序分组的最后一个位置，这样总共需要遍历N-1趟
 */
void select_sort(vector<int>& arr) {
  int size = arr.size();
  for (int i = 0; i < size - 1; i++) {    //! 需要排size-1趟
    int pos_max = 0;
    for (int j = 0; j < size - i; j++) {  //! 需要比较size - i次
      if (arr[j] > arr[pos_max]) {
        pos_max = j;
      }
    }
    std::swap(arr[pos_max], arr[size - i - 1]);
  }
}

/**
 * 插入排序：
 * 1. 外层遍历待排序元素
 * 2. 内层倒序遍历已排序元素
 *  2.1 如果待排序元素 小于 遍历到的已排序元素，将该已排序元素后移
 *  2.2 否则说明找到合适的位置，跳出循环
 * 3. 将该待排序元素插入找到的位置
 */
void insert_sort(vector<int>& arr) {
  int size = arr.size();
  for (int i = 1; i < size; i++) {
    int ele = arr[i];
    int j = i - 1;
    for (; j > -1; j--) {
      if (ele < arr[j]) {
        arr[j + 1] = arr[j];
      } else {
        break;
      }
    }
    arr[j + 1] = ele;
  }
}

void test_simple_sort(int length, int method = 1) {
  vector<int> arr;
  for (auto i = 0; i < length; i++) {
    auto e = std::rand() % length;
    arr.emplace_back(e);
  }
  print_result(arr, 0, -1, arr.size());

  auto start = std::chrono::steady_clock().now();
  if (method == 1) {
    bubble_sort(arr);
  } else if (method == 2) {
    select_sort(arr);
  } else {
    insert_sort(arr);
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

  test_simple_sort(size);
  test_simple_sort(size, 2);
  test_simple_sort(size, 3);

  return 0;
}
