## 错误一

让limits.h中定义的INT_MAX，在涉及边（弧）的**权重矩阵**的图算法中不可行。

权重矩阵以INT_MAX(0x7fffffff)，若某算法需要将两条边的权值相加，  
如，此folyd算法将distance[i][round]与distance[round][j]相加  
其中若有INT_MAX权值的边，则会导致相加后为一负数

## 错误二

在delete_edge函数的实现中，一定要在删除链表后置各个顶点的first_edge指针为空指针。

## 反思

floyd无法求解含有**负权环**的图，会导致死循环