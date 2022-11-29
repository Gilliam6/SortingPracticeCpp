#pragma once
#include "Sort.cpp"


template <class RandIt>
void  print(RandIt first, RandIt second);

template<class RandIt>
void  mergeSort(RandIt first, RandIt second);

template<class RandIt>
void  mergeSortO1(RandIt first, RandIt second);

template<class RandIt>
void  selectionSort(RandIt first, RandIt second);

template<class RandIt>
void  bubbleSort(RandIt first, RandIt second);

template<class RandIt>
void  insertSort(RandIt first, RandIt second);

template<class RandIt>
void  heapSort(RandIt first, RandIt second);

template<class RandIt>
void  quickSort(RandIt first, RandIt second);
