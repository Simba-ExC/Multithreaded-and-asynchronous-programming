// «for_each»

#include <algorithm>
#include <iostream>
#include <list>
#include <iterator>
#include <future>
#include <thread>


int func(int value) {
	return value+1;
}

template<typename It, typename Func>
void parallel_for_each(It first, It last, Func f) {
	unsigned int const length = std::distance(first, last);
	if (!length)
		return;
	unsigned int const min_per_thread = 25;
	if (length < (2 * min_per_thread)) {
		std::for_each(first, last, f); 
	}
	else {
		It const mid_point = first + length / 2;
		std::future<void> first_half = std::async(&parallel_for_each<It, Func>, first, mid_point, f);
		std::future<void> last_half = std::async(&parallel_for_each<It, Func>,mid_point, last, f);
		first_half.get(); 
		last_half.get();
	}
}
void print(std::vector<int>& l) {
	for (const auto& elem : l)
		std::cout << elem << " ";
	std::cout << std::endl;
}
int main(int argc, char** argv) {
	
	std::vector<int> v{ 1,5,9,8,3,2 };
	print(v);
	int i = 0;
	parallel_for_each(v.begin(), v.end(), [](int i) {std::cout << func(i) << " "; });
	
}








