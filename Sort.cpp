#include <random>
#include <algorithm>
#include <iostream>
#include <queue>  

template <class RandIt>
void  print(RandIt first, RandIt second) {
   std::cout << "Print: ";
   while (first != second) {
      std::cout << *first << " ";
      first++;
   }
   std::cout << "\n";
}

template <class T>
void  print(const T& v) {
   if (!v.size())
      return;
   for (const auto& p: v) {
      std::cout << p << " ";
   }
   std::cout << "\n";
}

template <class RandIt>
void  quickSort(RandIt first, RandIt second) {
   int size = second - first;
   
   if (size < 2)
      return;

   auto pivot = *(first + size/2);
   std::swap(*(first + size/2), *(second - 1));
   auto it1 = first, it2 = second - 2;
   
   while (it2 != it1) {
      while (it2 != it1 && *it1 < pivot)
         it1++;
      while (it2 != it1 && *it2 > pivot)
         it2--;
      if (it2 == it1) break;
      std::swap(*it1, *it2);
      it1++;
      if (it2 == it1) break;
      it2--;
   }
   if (pivot > *it1) {
      std::swap(*(it1 + 1), *(second-1));
      quickSort(first, it1 + 1);
      quickSort(it1+2, second);
   }
   else {
      std::swap(*it1, *(second-1));
      quickSort(first, it1);
      quickSort(it1+1, second);
   }
}

template <class RandIt>
void heapSort(RandIt first, RandIt second) {
   std::priority_queue<typename std::remove_reference<decltype(*first)>::type> heap;
   RandIt begin = first;

   while (begin != second) {
      heap.push(*begin++);
   }
   while (first != begin) {
      *--begin = heap.top();
      heap.pop();
   }
}

template <class RandIt, typename D>
void partitions(RandIt first, RandIt second, int size, D) {
   if (size <= 1)
      return;
   std::vector<D> v;
   RandIt begin1 = first;
   RandIt begin2 = first + size/2;
   RandIt end1 = first + size/2;
   RandIt end2 = second;
   
   while (static_cast<int>(v.size()) != size) {
      if (begin1 == end1 || begin2 == end2)
         break;
      if (*begin1 < *begin2) {
         v.push_back(*begin1);
         begin1 += 1;
      }
      else {
         v.push_back(*begin2);
         begin2 += 1;
      }
   }
   while (begin1 != end1)
      v.push_back(*begin1++);
   while (begin2 != end2)
      v.push_back(*begin2++);

   auto vecIt = v.begin();
   for (auto p = first; p != second; p++) {
      *p = *vecIt++;
   }
}

template <class RandIt>
void mergeSort(RandIt first, RandIt second) {
   int size = second - first;
   if (size > 2) {
      mergeSort(first, first + size/2);
      mergeSort(first + size/2, second);
   }
   partitions(first, second, size, *first);
}


template <class RandIt>
void selectionSort(RandIt first, RandIt second) {
   auto min = first;
   for (auto p = first; p != second; ++p) {
      min = p;
      for (auto v = p; v != second; ++v) {
         if (*min > *v) {
            min = v;
         }
      }
      std::swap(*min, *p);
   }
}


template <class RandIt>
void bubbleSort(RandIt first, RandIt second) {
   for (auto p = second - 1; p != first + 1; --p) {
      for (auto v = first; v != p; v++) {
         if (*v > *(v + 1))
            std::swap(*v, *(v + 1));
      }
   }
}


template <class RandIt>
void insertSort(RandIt first, RandIt second) {
   for (auto p = first + 1; p != second; ++p) {
      for (auto v = p - 1;*v > *(v + 1); v--) {
         std::swap(*v, *(v + 1));
         if (v == first)
            break;
      }
   }
}
