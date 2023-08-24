#include <chrono>
#include <functional>
#include <future>
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

std::chrono::milliseconds print_something_with_result(std::size_t count)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (count-- > 0)
    {
        {
            std::unique_lock<std::shared_mutex> _{cout_mx};
            std::cout << "[Thread " << std::this_thread::get_id()
                      << "] Retries left : " << count << std::endl;
        }

        std::this_thread::sleep_for(100ms);
    };
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start);
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

    auto f = std::async(print_something_with_result, 10);

    std::promise<std::chrono::milliseconds> result;
    auto f_result = result.get_future();
    // std::async BEGIN
    std::thread t_like_async{
        [result = std::move(result)](std::size_t count) mutable
        { result.set_value(print_something_with_result(count)); },
        10};
    // std::async AND

    t.join();
    t2.join();
    t_like_async.join();
    std::cout << "Computation time: " << f.get().count() << "ms" << std::endl;
    std::cout << "Second computation time: " << f_result.get().count() << "ms"
              << std::endl;
    return 0;
}
