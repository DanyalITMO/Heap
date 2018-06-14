#include <iostream>
#include "Heap.h"
#include <random>
#include <chrono>

template<typename T, template <typename ELEM, typename...>  class CONT>
void fillRandomly(CONT<T>& data, const int size, const T min, const T max)
{
    std::random_device rd;
    std::uniform_int_distribution<T> uid(min, max);
    for (size_t i = 0; i < size; i++)
    {
        data.push_back(uid(rd));
    }
}




int main() {
    Heap<int> heap;
    std::vector<int> vec;//{1,2,3,4,5,6,7,8};
    fillRandomly(vec, 1000'000, 0, 200);
    auto start = std::chrono::system_clock::now();

    for(auto it : vec)
        heap.insert(it);
    for(int i =0; i < vec.size(); i++) {
        auto var = heap.remove();
      ///  std::cout<<var<<std::endl;
    }

    for(auto it : vec)
        heap.onlyInsert(it);
    heap.heapify(0);
    for(int i =0; i < vec.size(); i++) {
        auto var = heap.remove();
//        std::cout<<var<<std::endl;
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;

    std::cout << "Time to sort a vector of "
              << vec.size()<< " ints : " << diff.count() << " s\n";

    return 0;
}