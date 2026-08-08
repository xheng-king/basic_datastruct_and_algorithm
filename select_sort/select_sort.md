### 大体实现
（与冒泡排序对比阅读）  
约定：数组有效数据位从0到length-1  

1.外层循环：i从0到length-2(i < length-1，不包含数组最后一个元素)  
2.设置min为i  
3.内层循环：j从i+1到length-1(j < length)，用于寻找i+1到length-1的最小元素下标赋给min  
4.交换min和i位置处的元素  