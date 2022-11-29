//#include <matplot/matplot.h>
#ifndef BENCHMARK_HPP
# define BENCHMARK_HPP
# include <ctime>
# include <cstdlib>
# include <vector>
# include <iostream>
# include <matplot/matplot.h>
# include "Sort.hpp"

# define MAX_QUAD 10000
# define MAX_LOG  500000
class Benchmark {
   public:
      void  progressBar(float progress) {
         int barWidth = 70;

         std::cout << "[";
         int pos = barWidth * progress;
         for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
         }
         std::cout << "] " << int(progress * 100.0) << " %\r";
         std::cout.flush();

       //  std::cout << std::endl;
      };

      template <class RandIt>
      size_t    run(void (*func)(RandIt, RandIt), size_t size) {
         size_t t1, t2;
         std::vector<int> v(size);
         shuffleMachine(v.begin(), v.end());

         t1 = timer();
         func(v.begin(), v.end());
         t2 = timer();

         if (isSorted(v.begin(), v.end()) == false) {
            std::cerr << "WARNING CURRENT ARRAY IS NOT SORTED!!!\n";
            std::cout << "type \"print\" to check array and exit\n";
            std::string yes;
            std::cin >> yes;
            if (yes == "print") {
               for (const auto& i:v)
                  std::cout << i << " ";
               std::cout << std::endl;
               std::exit(1);
            }
         }
         return t2 - t1;
      }

      template <class RandIt>
         void        plot(void (*func)(RandIt, RandIt), int max) {
            std::vector<int> y, x;
            
            for (int i = max / 20; i <= max; i += max / 20) {
               y.push_back(i);
               x.push_back(run(func, i));
               progressBar(static_cast<float>(i) / max);
            }
            std::cout << std::endl;
            matplot::plot(y, x, "-o");
         }

      void        plotAll() {
         typedef typename std::vector<int>::iterator it;
         void(*func[])(it, it) = { selectionSort<it>, bubbleSort<it>, insertSort<it>, heapSort<it>, quickSort<it>, mergeSort<it> };
         std::vector<std::string> s = { "Selection Sort", "Bubble Sort", "Insert Sort", "Heap Sort", "Qick Sort", "Merge Sort" };
         matplot::hold(matplot::on);
         matplot::title("Sorting");
         matplot::ylabel("Time ms");
         matplot::xlabel("Array size");
         matplot::legend({ "Selection Sort", "Bubble Sort", "Insert Sort", "Heap Sort", "Merge Sort" });
         
         for (int i = 0; i < 3; i++) {
            std::cout << s[i] << " processing\n";
            plot(func[i], MAX_QUAD);
         }
         for (int i = 3; i < 6; i++) {
            std::cout << s[i] << " processing\n";
            plot(func[i], MAX_LOG);
         }
         matplot::hold(matplot::off);
         matplot::show();
      }


      template <class RandIt>
         void  shuffleMachine(RandIt first, RandIt second) {
            int size = second - first;
            std::srand(std::time(nullptr));
            while (first != second) {
               *first++ = std::rand() % size;
            }
         };

      template <class RandIt>
      bool           isSorted(RandIt first, RandIt second) {
         for (auto p = first; p != second - 1; p++) {
            if (*p > *(p + 1))
               return false;
         }
         return true;
      };

   private:
      
      size_t       timer();
      
};
#endif
