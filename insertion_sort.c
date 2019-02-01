/*****************************************************************************
File name: insertion_sort.c
Description: 插入排序(Insertion Sort)
    由于在处理短数组、部分有序的数据时较为高效。
    故在此用于被优化版本的归并排序、快速排序调用，当数组长度较小时，用插入排序进行处理。

Author: 李梓豪
Version: 1.0
Last-Modified: 2019-01-30
History: 
    2019-01-29， finish the code, remain to be tested
    2019-01-30， all tested
*****************************************************************************/

#define _INSERTION_SORT_C_

#ifndef _BASIC_DEF_H_
#include "basic_def.h"
#endif
void insertion_sort(DataType * arr, int len);
void insertion_sort_iter(DataType * arr, int left, int right);


/*************************************************
Function: 
    insertion_sort_iter
Description: 
    Sort arr[left]:arr[right] using insertion_sort
Calls:  None
Called By: main, merge_sort_opt_iter, quicksort_opt_iter
Input: arr: pointer of array, left: the lower bound of the idx, right: the upper bound of the idx
Output: Sorted arr[left]:arr[right]
Return: None.
*************************************************/
void insertion_sort_iter(DataType * arr, int left, int right){
    int i, j, k;
    DataType key;
    for(j = left + 1, i = left; j <= right; j++){
        if(arr[j] OP arr[j-1]){
            key = arr[j];
            i = j-1;
            // move forward
            do{
                arr[i + 1] = arr[i];
                i--;
            }while(i>=left && key OP arr[i]);
            arr[++i] = key;
        }
    }
}


/*************************************************
Function: 
    insertion_sort
Description: 
    Sort the array using insertion sort
Calls:  insertion_sort_iter
Called By: main
Input: arr: pointer of array, len: the length of the arrays
Output: Sorted array
Return: None.
*************************************************/
void insertion_sort(DataType * arr, int len){
    insertion_sort_iter(arr, 0, len-1);
}