### 大体实现
约定：同冒泡排序、选择排序、快速排序，无哨兵，len作为arr的有效数据长度，即有效数据范围是0~len-1。  
细节较多，现场推演很慢，记忆**代码逻辑+如何绘制排序树**即可  
数据区：一个足够大（至少为待排序数组长度）的数组b  
#### void merge(elemtype arr[], int low, int mid, int high):
1.先将arr[]数组内low到high的元素复制到b  
2.进入for循环，i遍历b数组的low到mid，j遍历b数组的mid+1到high(以i小于等于mid和j小于等于high为循环条件)  
　　2.1.若b[i]<b[j]，则arr[k++]=arr[i++]  
　　2.2.否则arr[k++]=arr[j++]   
3.用两个while循环，分别以i小于等于mid和j小于等于high为循环条件，继续让arr[k++]=arr[i++]或arr[k++]=arr[j++]  

#### void merge_sort(elemtype arr[], int low, int high)————这个接口函数和快排很像:
如果low<high，先计算mid=(low+high)/2，然后对[low,mid]与[mid+1~high]两个区间调用自身，再调用merge归并两个有序段