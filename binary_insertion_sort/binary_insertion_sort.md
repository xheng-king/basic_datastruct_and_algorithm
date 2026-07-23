## 大体实现

数组约定同直接插入排序，使用arr[0]作为哨兵。  

外层循环同直接插入排序，i从2到length。  

外层循环内部，首先判断是否需要插入，即arr[i]是否大于arr[i-1]，若是，则该轮循环什么都不做。若不是，则进入二分查找并插入过程。  

二分查找并插入过程：首先将哨兵arr[0]置为arr[i]，然后初始化low和high为二分查找区间1~i-1，二分查找是个while循环，循环条件是low<=high，首先计算m=(low+high)/2，若哨兵小于arr[m]，则high置为m-1，否则low置为m+1(**让low = m + 1更容易被执行**)。最后high+1即为哨兵待插入位置，再用一个循环，让j从i-1到high+1，将arr[j+1]赋值为arr[j]。最后将哨兵放到arr[high+1]即可

## 低级错误

### 1
```C
while(low <= high){
    int m = (low + high) / 2;
    if(arr[0] < arr[m])
        high = low - 1;
    else
        low = high + 1;
}
```

high应该置为m-1，low应该置为m+1