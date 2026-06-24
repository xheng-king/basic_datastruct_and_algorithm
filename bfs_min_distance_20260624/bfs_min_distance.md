## 心得

bfs求单元最短路径，实际上就是求一个distance数组

经典广度优先搜索包括外壳函数bfs_traverse和内层函数bfs

内层函数bfs对一个结点处理包括：打印->标记已访问->入队

bfs_min_distance亦属于内层函数，但其不需要外层函数

bfs_min_distance对一个结点处理包括：设置distance->标记已访问->入队