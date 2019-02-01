## 项目介绍
此项目中探索了快速排序和归并排序的优化方法。


先实现了插入排序、归并排序、快速排序，作为Baseline, 然后在他们的基础上进行了算法的优化。

做的优化如下: 
1. 归并排序
    - 采用非递归的方式实现归并排序, 本质上是对递归树的自底向上的层次遍历（后序遍历也可以完成，但是层次遍历的方法更加易于实现）
    - 对于短数组，采用插入排序
2. 快速排序
    - 在完成划分后, 将和pivot相等的元素移动至pivot后面, 从而避免重复数据过多时划分结果差的情况
    - 对于短数组，采用插入排序
    - (可优化但没有实现的) 采用非递归方式实现快速排序，对递归树进行**先序遍历**。

## 执行方式
1. 设定data/generate_data.c中测试数据的参数, 编译执行, 生成4组测试数据。
2. 编译test_sort.c
3. 参考如下方式，对算法进行测试:

    cat data/data_random | ./a.out 


## 测试结果

算法的测试结果如下，以下数据为循环50次求平均值后的时间

- 数据个数：200个, 当长度不大于8时, 采用插入排序

|Algorithm |Random Data|Sorted Data|Reversed Data|Redundant Data(40%)|
|----------|-----------|-----------|-------------|-------------------|
|Insertion Sort|16|1|28|15|
|Merge Sort|74|59|71|80|
|Merge Sort(Optimized)|19|13|16|20|
|Quicksort|12|9|9|13|
|Quicksort(Optimized)|10||7|8|7|



- 数据个数：200个,当长度不大于16时, 采用插入排序

|Algorithm |Random Data|Sorted Data|Reversed Data|Redundant Data(40%)|
|----------|-----------|-----------|-------------|-------------------|
|Insertion Sort|13|1|28|12|
|Merge Sort|47|66|66|68|
|Merge Sort(Optimized)|9|10|13|12|
|Quicksort|11|13|10|15|
|Quicksort(Optimized)|8|6|7|7|
 
- 数据个数：500个, 当长度不大于16时，采用插入排序

|Algorithm |Random Data|Sorted Data|Reversed Data|Redundant Data(40%)|
|----------|-----------|-----------|-------------|-------------------|
|Insertion Sort|93|1|161|60|
|Merge Sort|121|111|92|155|
|Merge Sort(Optimized)|22|17|26|24|
|Quicksort|30|20|26|41|
|Quicksort(Optimized)|24|12|16|17|

- 数据个数：1000个, 当长度不大于16时，采用插入排序


|Algorithm |Random Data|Sorted Data|Reversed Data|Redundant Data(40%)|
|----------|-----------|-----------|-------------|-------------------|
|Insertion Sort|228|2|591|243|
|Merge Sort|188|200|198|207|
|Merge Sort(Optimized)|47|33|40|71|
|Quicksort|65|41|41|124|
|Quicksort(Optimized)|49|26|28|44|
