## 大体实现

细节较多，现场推演很慢，记忆**代码逻辑+如何绘制排序树**即可  

### partion:
1.设置主元pivot  
2.进入while循环  
2.1.high处元素若大于等于pivot则一直左移  
2.2.high处元素放于low  
2.3.low处元素若小于等于pivot则一直右移  
2.4.low处元素放于high  
3.low处放pivot  
4.返回low  

注意，2、2.1、2.3这三个while循环，都有low<high的判别  

### quick_sort
如果low<high，就调用partition得到划分位置，对[low,划分位置-1]与[划分位置+1~high]两个区间调用自身