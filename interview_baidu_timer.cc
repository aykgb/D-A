#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <utility>

#include <sys/epoll.h>
#include <sys/time.h>
#include <assert.h>

using namespace std;

using Func = std::function<void()>;
using Time = double;
Time get_time() {
#if defined(__linux__)
    struct timespec now;
    auto result = clock_gettime(CLOCK_REALTIME, &now);
    (void) result; // reference result in case assert is compiled out
    assert(0 == result);
    return now.tv_sec + (now.tv_nsec / 1.0e9);
#else
    struct timeval now;
    auto result = gettimeofday(&now, NULL);
    (void) result; // reference result in case assert is compiled out
    assert(0 == result);
    return now.tv_sec + (now.tv_usec / 1.0e6);
#endif
}

std::string format_time(const Time& time, uint modulo = 1000) {
    long subtract = long(time / modulo) * modulo;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << (time - subtract);
    return ss.str();
}

struct Task {
    Time timestamp;
    Func execute;

    Task(Time& t, Func& f): timestamp(t), execute(f) { }
};

struct Comparator {
    bool operator()(Task t1, Task t2) {
        if(t1.timestamp < t2.timestamp) {
            return false;
        }
        return true;
    }
};

using TaskQueue = std::priority_queue<Task, vector<Task>, Comparator>;

class Timer {
    std::mutex mtx;
    std::condition_variable cv;
    TaskQueue task_queue;
    std::vector<std::thread> thds;

    bool stop = false;;

    // int fd = -1;

    bool is_ontime(Time& time) {
        double now = get_time();
        if(time <= now) {
            return true;
        }
        return false;
    }

    void entry() {
        while(!stop) {
            std::unique_lock<std::mutex> lck(mtx);
            if(task_queue.empty()) {
                cv.wait(lck);
                if(task_queue.empty()) { continue; }
                if(stop) { break; }
            }

            Task task = task_queue.top();
            while(!is_ontime(task.timestamp));

            debug.emplace_back(task.timestamp, get_time());

            task.execute();
            task_queue.pop();
            lck.unlock();
            // 为任务的执行单独起一个线程
            // std::async(std::launch::async, task.execute);
        }
    }

public:
    std::vector<std::pair<Time, Time>> debug;

    Timer() {
        for(int i = 0; i < 2; i++) {
            thds.emplace_back(&Timer::entry, this);
        }
    }

    ~Timer() {
        for(auto &thd: thds) {
            thd.join();
        }
    }

    void Add(Task& t) {
        std::unique_lock<std::mutex> lck(mtx);
        bool q_empty = task_queue.empty();
        task_queue.push(t);
        lck.unlock();
        if(q_empty) {
            cv.notify_one();
        }
    }

    void Stop() {
        stop = true;
        cv.notify_all();
    }
};

int main()
{
    auto print_debug = [](std::vector<std::pair<Time, Time>>& debug) {
        for(size_t id = 0; id < debug.size(); id++) {
            std::cout << std::left
                      << "id:" << std::setw(6) << id << " "
                      << "expect:" << format_time(debug[id].first, 100000) << " "
                      << "actual:" << format_time(debug[id].second, 100000) << " "
                      // << std::endl;
                      << "\n";
        }
    };

    std::unique_ptr<Timer> timer(new Timer);

    // std::ofstream file("timer.txt", std::fstream::app);


#if 1
    std::function<void()> func = []() { for(int i = 0; i < 1000; i++); };
    for(int i = 0; i < 1000000; i++) {
        static Time expec= get_time();
        expec += 1.0 / 1000000;
        Task task(expec, func);
        timer->Add(task);
    }
#else
    Time now = get_time();
    std::cout << "now:" << format_time(now, 1000000) << std::endl;

    Time expec = now + 100.0/1000000; // 100us
    std::function<void()> func = std::bind(ff, 0, expec);
    Task task(expec, func);
    timer->Add(task);

#endif

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    print_debug(timer->debug);
    timer->Stop();
    // file.close();

    return 0;
}
