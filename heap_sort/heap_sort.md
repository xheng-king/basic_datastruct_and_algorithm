### 大体实现
约定：同插入排序，arr[0]作为哨兵，len作为arr的有效数据长度，即有效数据范围是1~len。  

#### void heap_adjust(elemtype arr[], int k, int len)
1.设置哨兵arr[0]为根arr[k]；  
2.进入循环，初始置i为k的左孩子(2xk)：  
　　2.1若i有右兄弟(i<len)，且i的右兄弟比i大(arr[i]小于arr[i+1])则置i为i+1；  
　　2.2比较arr[0]与arr[i]，  
　　　a.若arr[0]大于arr[i]，表明可以将arr[0]放在k处，此时退出循环即可(break)；  
　　　b.否则，让arr[i]放在k处，同时置k为i。  
当某一轮循环让ix2指向k的左孩子发现ix2超过len，那么就直接退出循环，故循环的终止条件是i<=len，否则，i自乘2。  
3.出循环后，将arr[0]放在k处

#### void build_heap(elemtype arr[], int len)
设置一个循环，i从len/2递减到1，以i为根节点的堆，调用heap_adjust。  

#### void heap_sort(elemtype arr[], int len)
1.首先调用build_max_heap建大根堆  
2.设置循环，i从len递减到2（len-1趟排序）  
　　交换arr[i]与arr[1]，并对前i-1个元素调整(调用heap_adjust)

### 错误日志
1.
```c
void build_heap(elemtype arr[], int len){
    for(int i = 1; i < len/2; i--){
        heap_adjust(arr, i, len);
    }
}
```
i应该从len/2到1而非1到len/2  
2.
heap_sort在一开始忘记调用build_heap