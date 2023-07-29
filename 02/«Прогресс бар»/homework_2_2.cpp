//«Прогресс бар»

#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;
auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
std::mutex m;


void setCursor(int x, int y) {
    SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
}

void stream(int threadNumber, int length) {
    auto start = std::chrono::high_resolution_clock::now();

    int count{};

    while (true) {

        m.lock();
        setCursor(count + 18, threadNumber + 1);
        if (!count) std::cout << "\r поток " << threadNumber << " #id " << std::this_thread::get_id() << " ";
        else std::cout << "|";
        m.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100 * (threadNumber + 1)));
        if (++count > length) break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration <double> time = end - start;
    setCursor(length + 20, threadNumber + 1);
    std::cout << " " << time.count() << std::endl;
}

//_______________________________________________________________

int main() {
    setlocale(LC_ALL, "rus");
    
    int numberOfThreads = 4;
    int length = 20;
    std::vector<std::thread> threads(numberOfThreads);

    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i] = std::thread(stream, i, length);
    }
    for (auto& entry : threads) {
        entry.join();
    }
    return 0;
}
   




  
        
