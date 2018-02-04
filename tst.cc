#include <iostream>

#include <sys/time.h>

using namespace std;

int main()
{
    struct timeval now;
    gettimeofday(&now, nullptr);

    std::cout << now.tv_sec << " " << now.tv_usec << std::endl;
    std::cout << now.tv_sec << " " << now.tv_usec + 1000 << std::endl;

    return 0;
}
