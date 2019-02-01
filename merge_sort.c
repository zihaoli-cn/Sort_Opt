/*****************************************************************************
File name: merge_sort.c
Description: 
    1. 实现归并排序(Merge Sort)
    特性：
        空间复杂度theta(n), 空间开销较大
        时间复杂度theta(nlgn), 稳定，与特定的序列无关
        从递归树来看，此种实现是对递归树的后序遍历(Post-order Traversal)，即，先执行左右子树的操作，再执行根结点的操作。
    用途：用于做benchmark。

    2. 实现归并排序(Merge Sort)的优化版本
    优化：
        1. 当数组较短时，改用插入排序（Insertion Sort）
        2. 非递归方式实现， 减少了递归时压栈的时间和空间。 从递归树来看，只有一个节点对应的两颗子树的所有操作都完成了，才能进行父节点的操作。
        递归版本的归并排序，类似从根节点的深度优先遍历。在此以非递归方式实现的归并排序，等同于从树的最底层节点开始的层次遍历。

Author: 李梓豪
Version: 1.0
Last-Modified: 2019-01-31
History: 
    2019-01-29， finish the code, remain to be tested
    2019-01-30， all tested
*****************************************************************************/

#ifndef _BASIC_DEF_H_
#include "basic_def.h"
#endif

#ifndef _INSERTION_SORT_C_
#include "insertion_sort.c"
#endif

#include <stdlib.h>

void merge_sort(DataType *arr, int len);
void merge_sort_opt(DataType *arr, int len);

static void merge(DataType *arr, int left, int mid, int right);
static void merge_sort_iter(DataType *arr, int left, int right);

/*************************************************
Function: 
    merge
Description: 
    Merge two sorted arrays——arr[left]:arr[mid], arr[mid+1]:arr[right]
Calls:  malloc, free
Called By: merge_sort_iter
Precondition: arr[left]:arr[mid], arr[mid+1]:arr[right] are both sorted
Input: arr: pointer of array, left: low bound of idx, mid: middle idx, right: upper bound of idx
Output: Sorted array: array[left]:arr[right]
Return: None.
*************************************************/
static void merge(DataType *arr, int left, int mid, int right){
    if(left < right){
        int len1, len2;
        len1 = mid - left + 1;
        len2 = right - mid;

        DataType * arr1 = (DataType * ) malloc(len1 * sizeof(DataType));
        DataType * arr2 = (DataType * ) malloc(len2 * sizeof(DataType));
        
        //init
        int i, j;
        for(i = 0; i < len1; i += 1)
            arr1[i] = arr[left + i];
        for(j = 0; j < len2; j += 1)
            arr2[j] = arr[mid + 1 + j];

        int k = left;
        for(i = 0, j = 0; i<len1 && j<len2; k+=1)
            arr[k] = (arr1[i] OP arr2[j]) ? arr1[i++] : arr2[j++];

        // test : arr1 is EMPTY?
        int test = i==len1; 
        DataType * ptr = test ? arr2 : arr1;
        i = test ? j : i;
        len1 = test ? len2 : len1;

        // move the residual elements
        while(i<len1)
            arr[k++] = ptr[i++];

        free(arr1);
        free(arr2);
    }
}

/*************************************************
Function: 
    merge_sort_iter
Description: 
    Sort arr[left]:arr[right] using Merge Sort recursively.
Calls:  merge, merge_sort_iter
Called By: merge_sort
Input: arr: pointer of array, left: low bound of idx, right: upper bound of idx
Output:  Sorted array.
Return: None.
*************************************************/
static void merge_sort_iter(DataType *arr, int left, int right){
    if(left < right){
        if(left + 1 == right){
            DataType data_l = arr[left], data_r = arr[right];
            int judge = data_l OP data_r;

            arr[left] = judge ? data_l : data_r;
            arr[right] = judge ? data_r : data_l;
        }
        else
        {
            int mid = (right + left)/2;
            merge_sort_iter(arr, left, mid);
            merge_sort_iter(arr, mid+1, right);
            merge(arr, left, mid, right);
        }
    }
}


/*************************************************
Function: 
    merge_sort
Description: 
    Sort arr using Merge Sort without further optimizaion.
Calls:  merge_sort_iter
Called By: main
Input: arr: pointer of array, len: length of the array
Output:  Sorted array.
Return: None.
*************************************************/
void merge_sort(DataType *arr, int len){
    merge_sort_iter(arr, 0, len - 1);
}



/*************************************************
Function: 
    merge_sort_opt
Description: 
    Merge Sort's non-recursive implementation
Calls:  insertion_sort_iter, merge
Called By: main
Input: arr: pointer of array, len: the length of the arrays
Output: Sorted array
Return: None.
*************************************************/
void merge_sort_opt(DataType *arr, int len){
    int sep = MIN_LEN;
    int idx_l, idx_r;

    // sort
    for(idx_l = 0; idx_l < len; idx_l += sep){
        // for all idx_r, idx_r <= len - 1
        idx_r = (idx_l+sep <= len )? idx_l+sep-1: len-1 ;
        insertion_sort_iter(arr, idx_l, idx_r);
    }
    //merge
    do{
        sep *= 2;
        for(idx_l = 0; idx_l < len; idx_l += sep){
            // for all idx_r, idx_r <= len - 1
            idx_r = (idx_l + sep <= len )? idx_l + sep - 1: len - 1 ;

            // handle the last separation
            if(idx_r - idx_l + 1 > sep/2)
                merge(arr, idx_l, idx_l + sep/2 - 1, idx_r);
        }
    }while(sep <= len);
}

