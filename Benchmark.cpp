#include "Benchmark.hpp"

size_t Benchmark::timer() {
   static timespec	tv;

   timespec_get(&tv, TIME_UTC);
   return ((tv.tv_sec * (size_t)1000) + (tv.tv_nsec / (size_t)1000000));
};













