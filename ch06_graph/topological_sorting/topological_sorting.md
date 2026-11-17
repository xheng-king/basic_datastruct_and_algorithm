## 反思

拓朴排序很像广度优先搜索

广搜：**源结点入队+访问+visit置1** -> 循环到队空，每次出队一个，并将其邻接**入队+访问+visit置1**

拓扑：0入度结点入栈+访问 -> 循环到栈空，每次出栈一个，后将其邻接**入度减一，此时入度为0的邻接入栈+访问**

两者的访问都可以在入队（栈）或出队（栈）中二选一

但拓扑排序因为用于无环图，从已经访问的结点出发是不会回到自己的，故不需要visit数组

## 错误
```C
while(!my_stack.empty()){
        int current = my_stack.top();
        my_stack.pop();
        for(int i = 0; i < VERTEX_NUM; i++){
            if(g->arc[current][i]){
                g->indegree[i]--;
            }
            if(g->indegree[i] == 0){
                my_stack.push(i);
                printf("%d ", i);
            }
        }
    }
```

并非对所有入度为零的结点都入栈，而是current的出边指向的结点中，入度为零才入栈。这和dijkstra算法完全相反，dijkstra是所有final为0的结点选最小的dist作为current，而非仅仅邻接。