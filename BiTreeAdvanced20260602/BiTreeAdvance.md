# 算法错误日志

### 1.遍历
有线索用线索，没线索闯右子树最左（顺序）或左字数最右（逆序）
但是闯的时候循环条件是`p->ltag == 0`，代表有左孩子，而不是
`p->lchild != NULL`，因为此时二叉树已被线索化，不能根据指针是否为空判断左孩子是否存在。

# Tips:
对某个源文件，要定架构，编程路线更清楚：
1.头文件+函数声明+宏定义

(2.main函数，调用函数声明中的函数)

3.函数实现

2026.6.4 错误日志
asux@AsuxWin10:~/programs/BasicDataStructAndAlgorithm/BiTreeAdvanced20260602$ ./BiTreeAdvanced.out 
Input structure: operation (index) (pindex)
example:
add node 2 to node 1: a 2 1
delete node 2: d 2
show bitree: s
thread the bitree: t
quit: q
a 2 1
a 3 1
a 4 2
a 5 2
t
s
In-order sequence: 2 1 3 
In-order sequence(reversed): 3 1 2 
q
Segmentation fault (core dumped)