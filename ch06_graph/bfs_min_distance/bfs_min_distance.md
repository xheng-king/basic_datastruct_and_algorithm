## 心得

bfs求单元最短路径，实际上就是求一个distance数组  

经典广度优先搜索包括外壳函数bfs_traverse和内层函数bfs  

内层函数bfs对一个结点的处理包括：打印->标记已访问->入队  

外层函数主要是防止非连通图和进行一些数据结构的初始化操作  

bfs_min_distance亦属于内层函数，但其不需要访问非连通图的外层函数  

bfs_min_distance对一个结点处理包括：设置distance、path->标记已访问->入队  

bfs、dfs、bfs_min_distance、dijkstra四者都需要一个visit数组(final数组)  
此外，bfs_min_distance、dijkstra需要distance和path数组保存结果  

## 注意

bfs求最短路径仅适用于无权图，但有环图也可以
唯一不能用于有环图的是拓扑排序