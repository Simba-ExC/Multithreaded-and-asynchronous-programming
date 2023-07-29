#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;
std::atomic<int> count;

//memory_order_seq_cst
void client1(int number) {
    while (count < number) {
        count.fetch_add (1, std::memory_order_seq_cst);
        std::this_thread::sleep_for(1s);
        std::cout << count << " clients in the queue. " << std::endl;
    }
}
void clerk1() {
    while (count > 0) {
        count.fetch_sub (1, std::memory_order_seq_cst);
        std::this_thread::sleep_for(2s);
        std::cout << "The clerk processed the order, " << count << " clients in the queue. " << std::endl;
    }
}

//memory_order_relaxed
void client2(int number) {
    while (count < number) {
        count.fetch_add(1, std::memory_order_relaxed);
        std::this_thread::sleep_for(1s);
        std::cout << count << " clients in the queue. " << std::endl;
    }
}
void clerk2() {
    while (count > 0) {
        count.fetch_sub(1, std::memory_order_relaxed);
        std::this_thread::sleep_for(2s);
        std::cout << "The clerk processed the order, " << count << " clients in the queue. " << std::endl;
    }
}

//_______________________________________________________________

int main(int argc, char** argv) {
    count = 2;
    std::thread t1(client1, 5);
    std::thread t2(clerk1);
    //std::thread t3(client2, 5);
    //std::thread t4(clerk2);
    t1.join();
    t2.join();
    //t3.join();
    //t4.join();
    return 0;
}