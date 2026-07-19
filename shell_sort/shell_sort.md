## 大体过程

即分组直接插入排序。**推荐和分组插入的markdown文档对比观看**

步长数组dt[]，数组长度t

名称：shell_sort(外层)、shell_insert(内层)

数组约定：0号位作为哨兵，数组长度length是指数组实际物理长度为length+1，即1~length为有效数据位，dt从0开始  

shell_insert:主体为一个i从dk+1到数组长度length的for循环
每个array[i]，对比其与前一个array[i-dk]的大小：若不小于，这轮循环什么都不做，若小于，则表明需要将其插入到前面的位置。
插入到前面的位置具体过程：置哨兵为该array[i]，开启内层循环。  

内层循环的j从i-dk开始，以当前array[j]大于哨兵作为循环条件（for的第一个分号和第二个分号之间的内容），每次j减一向前移动，循环内部将array[j+dk]赋值为array[j]。  

出循环后j当前的位置是不大于哨兵的下标，或者j为小于0的数(越界)。将哨兵放在j后一个位置，即，将array[j+dk]赋值为array[0]。

shell_sort:用一个循环，遍历dt数组，对每个步长，调用shell_insert函数