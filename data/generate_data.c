/*****************************************************************************
File name: generate_data.c
Description: 
    生成排序算法的测试数据，测试数据共有四组，一组随机数据，一组按顺序排列的数据，一组按照逆序排列的数据，一组含有重复数据的数据
    其中，后三组数据都是在第一组随机数据的基础上生成的。
    生成的数据文件为data_random, data_sorted, data_reversed, data_redudant
Author: 李梓豪
Version: 1.0
Last-Modified: 2019-01-31
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../basic_def.h"
#include "../insertion_sort.c"

// MAXLEN: how many elememts in test data
#define MAXLEN 1000
// RATIO: percentage of redundant data in data_redundant
#define RATIO 0.4


static void generate_random_data(DataType * arr, int len);
static void generate_sorted_data(DataType * arr, int len);
static void generate_reversed_data(DataType * arr, int len);
static void generate_redundant_data(DataType * arr, int len);

int main(void){
    int len = MAXLEN;
    int * arr  =(int *) malloc(len * sizeof(int));

    generate_random_data(arr, len);
    generate_sorted_data(arr, len);
    generate_reversed_data(arr, len);
    generate_redundant_data(arr, len);

    free(arr);
    return 0;
}

/*************************************************
Function: 
    generate_random_data
Description: 
    Generate random data, both saved in arr and file "data_random"
Calls:  rand, fopen, fprintf, fclose
Called By: main
Input: arr: pointer of empty array, len: length of array
Output: Random data saved in arr and text file "data_random"
Return: None.
*************************************************/
static void generate_random_data(DataType * arr, int len){
    int mod = 2 * len;
    for(int i = 0; i<len ; i += 1){
        arr[i] = rand() % mod;
    }
    FILE * ptr_f = fopen("data_random", "w");
    fprintf(ptr_f, "%d\n", len);
    for(int i = 0; i<len; i += 1)
        fprintf(ptr_f, "%d ", arr[i]);
    fclose(ptr_f);
}


/*************************************************
Function: 
    generate_sorted_data
Description: 
    Based on random data in arr, sort the data in-place and save them in file "data_sorted"
Calls:  fopen, fprintf, fclose
Called By: main
Pre-condition: data in arr is random data
Input: arr: pointer of random data array, len: length of array
Output: Random data saved in arr and text file "data_random"
Return: None.
*************************************************/
static void generate_sorted_data(DataType * arr, int len){
    insertion_sort(arr, len);
  
    FILE * ptr_f = fopen("data_sorted", "w");
    fprintf(ptr_f, "%d\n", len);
    for(int i = 0; i<len; i += 1)
        fprintf(ptr_f, "%d ", arr[i]);
    fclose(ptr_f);
}


/*************************************************
Function: 
    generate_reversed_data
Description: 
    Based on sorted data in arr, reverse the data in-place and save them in file "data_reversed"
Calls:  fopen, fprintf, fclose
Called By: main
Pre-condition: data in arr is sorted data
Input: arr: pointer of sorted array, len: length of array
Output: Random data saved in arr and text file "data_random"
Return: None.
*************************************************/
static void generate_reversed_data(DataType * arr, int len){
    int mid = (len - 1)/2;
    DataType tmp;
    for(int i = 0; i<= mid; i+=1){
        tmp = arr[i];
        arr[i] = arr[len-1-i];
        arr[len-1-i] = tmp;
    }

    FILE * ptr_f = fopen("data_reversed", "w");
    fprintf(ptr_f, "%d\n", len);
    for(int i = 0; i<len; i += 1)
        fprintf(ptr_f, "%d ", arr[i]);
    fclose(ptr_f);
}

/*************************************************
Function: 
    generate_redundant_data
Description: 
    Based on random data saved in text file "data_random", add some redundant data randomly and save them in file "data_sorted"
Calls:  rand, fopen, fprintf, fclose
Called By: main
Pre-condition: text file "data_random" exists, and data in it are random data
Input: arr: pointer of array, len: length of array
Output: Random data saved in arr and text file "data_random"
Return: None.
*************************************************/
static void generate_redundant_data(DataType * arr, int len){
    
    // load data in text file "data_random"
    FILE * ptr_f = fopen("data_random", "r");
    fscanf(ptr_f, "%d", &len);
    for(int i = 0; i<len; i +=1){
        fscanf(ptr_f, "%d", arr + i);
    }
    fclose(ptr_f);

    // randomly set some redundant data
    int idx = rand() % len, num = MAXLEN * RATIO;
    DataType key = arr[idx];
    for(int i=0; i<num; i+=1){
        idx = rand() % len;
        arr[idx] = key;
    }
    
    // save data in text file "data_redundant"
    ptr_f = fopen("data_redundant", "w");
    fprintf(ptr_f, "%d\n", len);
    for(int i = 0; i<len; i += 1)
        fprintf(ptr_f, "%d ", arr[i]);
    fclose(ptr_f);
}