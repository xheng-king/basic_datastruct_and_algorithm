### 大体实现
约定：同冒泡排序、选择排序，无哨兵，len作为arr的有效数据长度，即有效数据范围是0~len-1。  
细节较多，现场推演很慢，记忆**代码逻辑+如何绘制排序树**即可  

#### partition:
1.设置主元pivot为low处元素  
2.进入while循环  
　　2.1.high处元素若大于等于pivot则一直左移  
　　2.2.high处元素放于low  
　　2.3.low处元素若小于等于pivot则一直右移  
　　2.4.low处元素放于high  
3.low处放pivot（或high处放pivot，无所谓，最后high必等于low）  
4.返回low  

注意，2、2.1、2.3这三个while循环，都有low<high的判别  

#### quick_sort
如果low<high，就调用partition得到划分位置，对[low,划分位置-1]与[划分位置+1~high]两个区间调用自身

### 错误日志
1.partition设置主元为arr[0]而非arr[low];