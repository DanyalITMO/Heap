//
// Created by danek on 23.04.18.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <array>
#include <vector>
#include <iostream>
#include <unistd.h>

template<typename T, template<typename> class CONT = std::vector>
class Heap {
   CONT<T> _container;

   void trickleDown(int index)
   {
      int largeChild;
      auto top = _container.at(index);

      while (index < _container.size() / 2) {
         int left_child = 2 * index + 1;
         int right_child = left_child + 1;

         if (right_child < _container.size() &&
             _container[left_child] < _container[right_child])
            largeChild = right_child;
         else
            largeChild = left_child;

         if (top >= _container[largeChild]) break;

         _container[index] = _container[largeChild];
         index = largeChild;

      }

      _container[index] = top;
   }

public:
   T remove()
   {
      if (!_container.empty()) {
         T ret = _container.front();
         _container.front() = _container.back();

         trickleDown(0);
         _container.pop_back();
         return ret;
      }
      else
         throw std::runtime_error("empty container");
   }

   void onlyInsert(T el)
   {
      _container.push_back(el);
   }


    void heapify(int index)
    {
        if (index > _container.size() / 2 - 1) return;
        if (index > 4) {
            heapify(index * 2 + 2);
            heapify(index * 2 + 1);
            }
        else {
#pragma omp parallel sections
            {
#pragma omp section
                heapify(index * 2 + 2);
#pragma omp section
                heapify(index * 2 + 1);
            }
            trickleDown(index);
        }
    }
};

#endif //HEAP_HEAP_H
