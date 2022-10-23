#include <vector>
#include <ctime>
#include <iostream>
#include <queue>
#include <matplot/matplot.h>
#define MAX_ARRAY 100000

uint64_t	get_time(void) {
	static timespec	tv;

	timespec_get(&tv, TIME_UTC);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_nsec / (uint64_t)1000000));
}

void swap(int &a, int&b)
{
   int c = a;
   a = b;
   b = c;
}

void selectionSort(int *arr, int size) {
   unsigned int a, b, c, min = 0;
   a = 0;
   c = 0;
   while (a < size) {
      b = a;
      while (b < size) {
         if (arr[b] < arr[min])
            min = b;
         b++;
      }
      swap(arr[a], arr[min]);
     // c = arr[a];
     // arr[a] = arr[min];
     // arr[min] = c;
      a++;
   }
  // for (int i = 0; i < size; i++)
    //  std::cout << arr[i] << "\n";
}

void insertionSort(int *arr, int size) {
   int a = 0, b = 1;
   while (b < size)
   {
      a = b - 1;
      while (a >= 0 && (arr[a] > arr[a + 1]))
      {
         swap(arr[a], arr[a + 1]);
         a--;
      }
      b++;
   }

   //for (int i = 0; i < size; i++)
     // std::cout << arr[i] << "\n";
}

void bubbleSort(int *arr, int size) {
   int a, b = 0;

   while (b < size)
   {
      a = 1;
      while (a < size - b)
      {
         if (arr[a] < arr[a - 1])
            swap(arr[a], arr[a-1]);
         a++;
      }
      b++;
   }
   //for (int i = 0; i < size; i++)
     // std::cout << arr[i] << "\n";
}

void merge(int *a, int left, int mid, int right) 
{
   int it1 = 0;
   int it2 = 0;
   int result[right - left];

   while ((left + it1 < mid) &&  (mid + it2 < right))
        if (a[left + it1] < a[mid + it2])
        {
           result[it1 + it2] = a[left + it1];
           it1 += 1;
        }
        else
        {
           result[it1 + it2] = a[mid + it2];
           it2 += 1;
        }

    while (left + it1 < mid)
    {
       result[it1 + it2] = a[left + it1];
       it1 += 1;
    }

    while (mid + it2 < right)
    {
       result[it1 + it2] = a[mid + it2];
       it2 += 1;
    }

    for (int i = 0; i < it1 + it2; i++)
        a[left + i] = result[i];

}

void mergeSort(int *arr, int size)
{
   for (int i = 1; i < size; i *= 2)
      for (int j = 0; j < size - i; j += 2 * i)
         merge(arr, j, j + i, std::min(j + 2 * i, size));
  // for (int f = 0; f < size; f++)
    //  std::cout << arr[f] << "\n";
}

void heapSort(int *arr, int size)
{
   std::priority_queue<int, std::vector<int>, std::greater<int> > heap;

   for (int i = 0; i < size; i++) {
      heap.push(arr[i]);
   }
   for (int i = 0; i < size; i++) {
      arr[i] = heap.top();
      heap.pop();
   }
}

void heapSort2(int *arr, int size)
{
   std::priority_queue<int, std::deque<int>, std::greater<int> > heap;

   for (int i = 0; i < size; i++) {
      heap.push(arr[i]);
   }
   for (int i = 0; i < size; i++) {
      arr[i] = heap.top();
      heap.pop();
   }
}

int partition(int *arr, int l, int r) {
   int dot = arr[(r + l) / 2];
   int i = l;
   int j = r;

   while (i <= j) {
      while (arr[i] < dot)
         i++;
      while (arr[j] > dot)
         j--;
      if (i >= j)
         break;
      swap(arr[i++], arr[j--]);
   }
   return j;
}

void quick(int *arr, int l, int r)
{
   if (l < r) {
      int q = partition(arr, l, r);
      quick(arr, l, q);
      quick(arr, q+1, r);
   }
}

void quickSort(int *arr, int size)
{
 //  std::cout << "QUICK SORT START\n";
   quick(arr, 0, size - 1);
 //  std::cout << "QUICK SORT END\n";
   
  // for (int i = 0; i < size; i++) {
  //    std::cout << arr[i] << "\n";
  // }
}

void  doSort(int *arr, std::vector<int> &x, std::vector<int> &y, void (*fun)(int*, int))
{
   int i = 1000;
   uint64_t t1, tDelta;
   std::srand(std::time(0));

   while (i <= MAX_ARRAY)
   {
      for (int b = 0; b < i; b++) {
         arr[b] = std::rand();
      }

      t1 = get_time();
      fun(arr, i);
      tDelta = get_time() - t1;
      x.push_back(tDelta);
      y.push_back(i);
      std::cout << tDelta << "ms for sorting array of size "<< i <<"\n";
      i += 1000;
   }

}
int main() {
   std::vector<int> x, y, x1, x2, x3, x4, x5, x6;

   int *arr;

   arr = new int[MAX_ARRAY];

  // doSort(arr, x, y, bubbleSort);
  //doSort(arr, x1, y, insertionSort);
  //doSort(arr, x2, y, selectionSort);
   doSort(arr, x3, y, mergeSort); 
   doSort(arr, x4, y, heapSort); 
   doSort(arr, x6, y, heapSort2); 
   doSort(arr, x5, y, quickSort); 

   
   matplot::hold(matplot::on);

  // matplot::plot(y, x, "-o");
  // matplot::plot(y, x1, "-o");
  // matplot::plot(y, x2, "-o");
   matplot::plot(y, x3, "-o");
   matplot::plot(y, x4, "-o");
   matplot::plot(y, x5, "-o");
   matplot::plot(y, x6, "-o");
   matplot::title("Log Sort");
   matplot::ylabel("Time ms");
   matplot::xlabel("Array size");

   matplot::hold(matplot::off);
   matplot::legend({"Merge sort", "Heap sort on vector", "Selection sort", "Heap sort on deque"});
   matplot::save("img/Log_Sort_With_Extra Heap.svg");
   matplot::show();



   delete []arr;
   return (0);
}
