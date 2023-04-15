# Mook-陈越，何钦明-数据结构-2023春季
Mook浙江大学-陈越，何钦明两位老师开设的数据结构课程，这个仓库整理下自己在该课程PTA习题集上提交的程序，加油，希望自己坚持做完！
## 第一周
1. [最大子列和问题](MSSum.c)
2. [Maximum Subsequence Sum](MSSumPlus.c)
3. [二分查找](BisMethod.c)

## 第二周
1. [两个有序链表序列的合并](Merge1.c)
    > malloc(sizeof(PtrToNode)) 和 malloc(sizeof(struct Node))的效果一样，申请到的都是这个结构空间，不太理解，`sizeof` 这个函数的操作数如果是结构体和结构体指针，结果一样？这也太奇怪了，需要查下
2. [一元多项式的乘法与加法运算](AddMultiList.c) + [insert改良版](AddMultiList1.c)
    > 这个题的思路很简单；最主要的一个函数就是 `void insertNode()` 这个函数负责传入的列表和需要新建的结点数据，来将新节点加入到这个列表中的合适位置
    
    ```diff
    + 对于加法来说，只需要不断地比较两个列表，挑选出指数大的结点添加上去就行了
    - 对于乘法来说，同样简单，列表1中的每个结点和整个列表2相乘，结果一个个加到新列表中
    ```

    > 需要注意的是，加法中会有0系数项合并，乘法中也会有，虽然相乘不会出现0系数同类项，但是四个结点是会有这种情况发生的，如此这般，就要求 `insertList` 函数更强壮

    ```diff
    - 可是，insert函数强壮了，那很多判别的事情交给它就可以了，乘法，加法的函数反而简单了，因此，就要对整体函数进行改良了；其实说是改良，也就是把加法函数中的判定条件直接删了，计算加法结果，就傻傻地一个个结点添加就行了，至于结点放在哪儿，结点合并，结点删除，全交给 insert 函数就好了
    ```
3. [Reversing Linked List](ReversingList.c)
    > 虽然通过了全部测试点，但并不强壮，自测的时候发现 如果K 的取值为 0 ，会发生段错误，但显然陈越老师的测试点没有提及这一点；另外，由于自己写程序的时候，根本没有想到还有多余的结点，对应测试点6，所以，我当时还纳闷，这个尾地址根本没用呀，只要最后一个结点，我直接输出尾巴是 -1就好了，自作聪明了，早知道这样，程序就不这样写了，但我懒得改了，就这样吧，由于以上两个原因，程序可以完善，但我不
4. [Pop Sequence](PopSequence.c)
    > 好复杂，我使用的方法不太一样，别人都是模拟入栈出栈，我完全是找规律，要想判断，需要有两条得满足：
    ```diff
    + 1.想要输出这个样子的队列，堆栈的容量是否满足，也就是超没有超
    - 输出的顺序要正确，比如说不能有“7 5 6”这样的顺序，像个山谷一样
    ```
    > 本来还有点心情，试一下模拟的方法，但使用这个的时候，遇到了一个很讨厌的段错误，程序中我存储数据的二维数组本来是这样写的 `num[MAXSIZE][MAXSIZE]` 这里的 `MAXSIZE` 定1000（根据题目）但结果就是还没有进入主函数，就遇到 `segmentation fault`，但是这样提交也没有问题，但在我的电脑上无法运行，只有使用变量来定义才行 `num[K][N]` ，原因可能是，main函数调用的栈空间太大了，这个真的麻烦，很想知道如果避免

## 第三周
1. [树的同构](IsomorphicTree.c)
    > 这道题感觉好难，没有老师的小白专场，感觉自己几天都做不出来，真是菜；感觉难点在于：1.理解题意，题中的输入本身就是按照数组给的，输入的左子树，右子树，就是数组顺序，知道了这一点，就可以下手；2.判断两个树是否是同构，用的迭代方法，经过老师之前的授课，感觉迭代最好不用，这道题需要使用，另外就是思维逻辑，能够将所有的情况想清楚，这个需要训练啊

    > 另外，又遇到了自己电脑上运行有问题，提交上去运行没问题的情况，估计是gcc版本不同导致的吧，自己电脑上输入不对，真是垃圾，用c++或者java写可能就不会有这样的问题了
2. [List Leaves](ListLeaves.c)
    > 做完了 `树的同构` 这道题，这个题的思想方法一致，多了一个层序遍历的问题，按照何老师的授课，可以通过队列来实现层序遍历，我使用数组的方法实现队列（该队列较为简单，只对这道题有用），由于不熟悉队列，花了不少时间，真笨
3. [Tree Traversals Again](TTraAgain.c)
    > 需要讨巧，Push 进去的队列就是 `PreOrder` ；Pop 出来的队列就是 `InOrder` ；已经知道两个顺序，就可以推出 `PostOrder`。

## 第四周
1. [是否同一棵二叉搜索树](IsSameTree.c)
    ```diff
    - 我用的最愚蠢的办法，分别建立两棵树，然后判定是不是同结构的树
    + 第二种方法是不用建立树，找到根，比他小的一堆在左，大的在右，递归查看左右
    + 第三种方法是何老师教的，建立一棵树，利用flag位，查看结点的路径上没有遇到新的结点，那么就是一样的树
    ```
2. [Root of AVL Tree](RootAVLTree.c)
    > 难点在于如何能够判断出什么时候该进行四种旋转，递归函数实现，从树的底部到顶部的结点的左右高度判定，判定成立，就进行旋转
3. [Complete Binary Search Tree](CBSTree.c)
    > 需要熟悉完全二叉树的排序方式，使用数组来表示该完全二叉树
4. [二叉搜索树的操作集]()
