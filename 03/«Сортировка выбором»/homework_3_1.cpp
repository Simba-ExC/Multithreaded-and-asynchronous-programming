// «Сортировка выбором»

#include <algorithm>
#include <iostream>
#include <list>
#include <iterator>
#include <future>
#include <thread>

int min(std::list<int> l) {
    return *std::min_element(l.begin(), l.end());
}

void sortList(std::list<int>& l, std::promise<std::string>_prom) {
    for (int j = 0; j < l.size(); j++) {
        auto begin = std::next(l.begin(), j);
        auto end = l.end();
        std::list<int> sub;
        sub.splice(sub.begin(), l, begin, end);

        std::future<int> result(std::async(
            std::launch::deferred, min, sub));
        int m = result.get();

        if (m != *sub.begin()) {
            sub.insert(std::find(sub.begin(), sub.end(), m), *sub.begin());
            sub.pop_front();
            sub.remove(m);
            sub.push_front(m);
        }
        l.splice(end, sub);
    }
    _prom.set_value("Sorting is complete");
}

void print(std::list<int>& l) {
    for (const auto& elem : l)
        std::cout << elem << " ";
    std::cout << std::endl;
}

int main(int argc, char** argv) {

    std::list<int> list = { 9, 6, 4, 3, 11, 2, 5, 7, 46 };
    std::promise<std::string> prom;
    std::future<std::string> fut = prom.get_future();

    std::cout << std::endl;
    print(list);

    std::thread t(sortList, std::ref(list), std::move(prom));
    fut.wait();
    std::cout << fut.get() << std::endl;
    print(list);
   
    t.join();
    return 0;
}


