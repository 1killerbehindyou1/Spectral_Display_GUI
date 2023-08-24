#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

void print_something(std::size_t count)
{
    while (count-- > 0)
    {
        std::cout << "[Thread " << std::this_thread::get_id()
                  << "] Retries left : " << count << std::endl;
        std::this_thread::sleep_for(100ms);
    };
}

int main()
{
    print_something(10);
    return 0;
}
