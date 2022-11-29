#include <iostream>
#include "Benchmark.hpp"
#include "Sort.hpp"
#include <matplot/matplot.h>
int main() {
   Benchmark bench;

//   bench.plot(selectionSort<std::vector<int>::iterator>);
//   matplot::show();

   bench.plotAll();
   return (0);
}
