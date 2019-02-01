/*****************************************************************************
File name: quicksort.c
Description: 
    1. 实现随机化快速排序(Randomrized Quicksort)
    特性：
        空间复杂度: 算法本身是in-place的，但是最坏情况对堆栈消耗较大
        不稳定，平均时间复杂度theta(nlogn)，最坏事件复杂度theta(n^2)，此种方法的最坏情况只取决于随机数的函数的结果，而不依赖于特定的序列。
        预计对重复元素较多的数据效果较差，因为partition过程没有将pivot的重复元素拣回附近，导致划分结果不太好。
        从递归树来看，这种实现是对递归树的先序遍历(Pre-order Traversal)，即，先执行根的操作，再执行两个子树的操作。
    用途：用于做benchmark。

    2. 实现随机化快速排序(Randomrized Quicksort)的优化版本
    优化：：
        1. 当数组较短时，改用插入排序（Insertion Sort），避免处理短数组时的需要的大量堆栈空间
        2. 在partition过程后，将与pivot相等的元素移动至pivot相邻的后面，优点是：对含有大量重复数据的序列，可以产生更优的划分
            缺点是：使得快速排序更加稳定，但增加了额外的操作，损失了”快“
    进一步优化方向：
        尾递归的优化，这里的递归是对递归树的先序遍历，可以据此进行实现非递归版本。

Author: 李梓豪
Version: 1.0
Last-Modified: 2019-01-28
History: 
    2019-01-28, finish the code, remain to be tested
    2019-01-30, all tested
*****************************************************************************/

#ifndef _BASIC_DEF_H_
#include "basic_def.h"
#endif

#ifndef _INSERTION_SORT_C_
#include "insertion_sort.c"
#endif

#include <stdlib.h>

void quicksort(DataType * arr, int len);
void quicksort_opt(DataType * arr, int len);

static int rand_idx(int min_idx, int max_idx);
static int partition(DataType * arr, int left, int right);
static void quicksort_iter(DataType * arr, int left, int right);
static int gather_to_front(DataType * arr, int left, int right, DataType key);
static void quicksort_opt_iter(DataType * arr, int left, int right);

/*************************************************
Function: 
    rand_idx
Description: 
    return a random integer between min_idx and max_int, which will be used for a array's index
Calls:  rand
Called By: partition
Precondition: 0 <= left <= right
Input: left: low bound of idx, right: upper bound of idx
Output:  random integer values in [left, right]
*************************************************/
int rand_idx(int min_idx, int max_idx){
    int mod = 1 + max_idx - min_idx;
    return min_idx + (rand() % mod);
}


/*************************************************
Function: 
    partition
Description: 
    randomly pick a pivot from arr[left] : arr[right], the partition the data into 2 parts: 
    1. smaller than pivot arr[left]~arr[i-1]
    2. no less than pivot arr[i+1]~arr[right]
Precondition: 
    left < right
Calls:  rand_idx
Called By: quicksort_iter
Input: arr: the array's pointer, left: low bound of idx, right: upper bound of idx
Output: array's partition
Return: integer i, where arr[i] = pivot
*************************************************/
static int partition(DataType * arr, int left, int right){
    int pivot_idx = rand_idx(left, right);
    DataType pivot = arr[pivot_idx];

    arr[pivot_idx] = arr[left];

    int i, j;
    for(i = left, j = left + 1; j <= right; j++){
        if(arr[j] OP pivot){
            arr[i] = arr[j];
            arr[j] = arr[++i];
        }
    }
    arr[i] = pivot;
    return i;
}


/*************************************************
Function: 
    partition
Description: 
    Sort the partial array: arr[left]:arr[right] in-place.
Calls:  partition, quicksort_iter
Called By: quicksort
Input: arr: the array's pointer, left: low bound of idx, right: upper bound of idx
Output:  Sorted arr[left]:arr[right]
Return: None.
*************************************************/
static void quicksort_iter(DataType * arr, int left, int right){
    if(left < right){
        int i = partition(arr, left, right);
        quicksort_iter(arr, left, i - 1);
        quicksort_iter(arr, i + 1, right);
    }
}



/*************************************************
Function: 
    quicksort
Description: 
    Rndomrized Quicksort, without further optimization, which serves as benchmark.  
Calls:  quicksort_iter
Called By: main
Input: arr: the array's pointer, len: the array's length
Output: Sorted wbole array.
Return: None.
*************************************************/
void quicksort(DataType * arr, int len){
    quicksort_iter(arr, 0, len - 1);
}



/*************************************************
Function: 
    gather_to_front
Description: 
    gather the elements that equals key to the front of the arrayCalls:  None.
Called By: partition
Input: arr: the array's pointer, left: low bound of idx, right: upper bound of idx, key:
Output: array.
Return: How many elements == key.
*************************************************/
static int gather_to_front(DataType *arr, int left, int right, DataType key){
    int low = left, high = right, count = 0;
    while(low<high){
        if(arr[high] == key){
            arr[high] = arr[low];
            arr[low] = key;
            low += 1;
            count += 1;
        }
        else
            high -= 1;
    }
    return count;
    /* recursive version
    if(left < right){
        if(arr[right] == key){
            arr[right] = arr[left];
            arr[left] = key;
            gather_same(arr, left+1, right, key);
        }
        else
            gather_same(arr, left, right-1, key);
    }
    */
}

/*************************************************
Function: 
    quicksort_opt_iter
Description: 
    sort arr[left]:arr[right] 
    if right - left + 1 > MIN_LEN, use optimized Randomrized Quicksort
    else,                          use Insertion Sort

Calls:  insertion_sort_iter, quicksort_opt_iter
Called By: quicksort_opt
Input: arr: the array's pointer, left: low bound of idx, right: upper bound of idx
Output: sorted array
Return: None.
*************************************************/
static void quicksort_opt_iter(DataType * arr, int left, int right){
    int len = right - left + 1;
    if(len <= MIN_LEN)
        insertion_sort_iter(arr, left, right);
    else{
        int i = partition(arr, left, right);
        int count = gather_to_front(arr, i+1, right, arr[i]);

        quicksort_opt_iter(arr, left, i-1);
        quicksort_opt_iter(arr, i+count+1, right);
    }
}

/*************************************************
Function: 
    quick_sort_opt
Description: 
    sort arr[left]:arr[right] 
    if right - left + 1 > MIN_LEN, use optimized Randomrized Quicksort
    else, use Insertion Sort

Calls:  insertion_sort, quicksort_opt_iter
Called By: quicksort_opt
Input: arr: the array's pointer, left: low bound of idx, right: upper bound of idx
Output: sorted array
Return: None.
*************************************************/
void quicksort_opt(DataType * arr, int len){
    quicksort_opt_iter(arr, 0, len - 1);
}

