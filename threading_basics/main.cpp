#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

std::shared_mutex cout_mx;

void print_something(std::size_t count)
{
    while (count-- > 0)
    {
        {
            std::unique_lock<std::shared_mutex> _{cout_mx};
            std::cout << "[Thread " << std::this_thread::get_id()
                      << "] Retries left : " << count << std::endl;
        }

        std::this_thread::sleep_for(100ms);
    };
}

struct S
{
    void print_something(std::size_t count) { ::print_something(count); }
};

int main()
{
    std::thread t{print_something, 10};

    S s;
    std::thread t2{&S::print_something, &s, 10};

    print_something(10);

    t.join();
    t2.join();
    return 0;
}
