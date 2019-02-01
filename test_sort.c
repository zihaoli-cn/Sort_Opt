#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.c"
#include "quicksort.c"

#ifndef _BASIC_DEF_H_
#include "basic_def.h"
#endif



#define ITER 50


extern void insertion_sort(DataType * arr, int len);
extern void merge_sort(DataType * arr, int len);    
extern void merge_sort_opt(DataType * arr, int len);
extern void quicksort(DataType * arr, int len);     
extern void quicksort_opt(DataType * arr, int len); 

int main(void){
    int len;
    scanf("%d",&len);  
    // target data
    DataType * arr = malloc(len * sizeof(DataType));
    for(int i = 0; i<len; i+=1)
        scanf("%d",arr + i);
    

    unsigned long duration;
    DataType * arr_tmp = malloc(len * sizeof(DataType));

    duration = 0;
    for(int i = 0; i < ITER ; i += 1){
        //copy data
        for(int i = 0; i<len; i++)
            arr_tmp[i] = arr[i];
        //sort
        clock_t start = clock();
        insertion_sort(arr_tmp, len);
        clock_t end = clock();

        duration += end - start;
    }
    printf("Insertion Sort: %lu\n",duration/ITER);
    

    duration = 0;
    for(int i = 0; i < ITER ; i += 1){
        //copy data
        for(int i = 0; i<len; i++)
            arr_tmp[i] = arr[i];

        //sort
        clock_t start = clock();
        merge_sort(arr_tmp, len);
        clock_t end = clock();

        duration += end - start;
    }
    printf("Merge Sort: %lu\n",duration/ITER);
    

    duration = 0;
    for(int i = 0; i < ITER ; i += 1){
        //copy data
        for(int i = 0; i<len; i++)
            arr_tmp[i] = arr[i];

        //sort
        clock_t start = clock();
        merge_sort_opt(arr_tmp, len);
        clock_t end = clock();

        duration += end - start;
    }
    printf("Merge Sort(Optimized): %lu\n",duration/ITER);
    

    duration = 0;
    for(int i = 0; i < ITER ; i += 1){
        //copy data
        for(int i = 0; i<len; i++)
            arr_tmp[i] = arr[i];

        //sort
        clock_t start = clock();
        quicksort(arr_tmp, len);
        clock_t end = clock();

        duration += end - start;
    }
    printf("Quicksort: %lu\n",duration/ITER);
    

    duration = 0;
    for(int i = 0; i < ITER ; i += 1){
        //copy data
        for(int i = 0; i<len; i++)
            arr_tmp[i] = arr[i];

        //sort
        clock_t start = clock();
        quicksort_opt(arr_tmp, len);
        clock_t end = clock();

        duration += end - start;
    }
    printf("Quicksort(Optimized): %lu\n",duration/ITER);



    free(arr);
    free(arr_tmp);
    return 0;
}


