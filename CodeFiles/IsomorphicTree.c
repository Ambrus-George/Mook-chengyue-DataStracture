#include <stdio.h>

#define Null -1
#define MAXSIZE 10
typedef char ElementType;
typedef int Tree;

struct Node
{
    ElementType data;
    Tree left;
    Tree right;
}T1[MAXSIZE], T2[MAXSIZE];

Tree BuildTree(struct Node T[]);
int Isomorphic(Tree r1, Tree r2);

int main()
{
    //build the first tree
    Tree root1 = 0;
    root1 = BuildTree(T1);

    //build the second tree
    Tree root2 = 0;
    root2 = BuildTree(T2);

    //adjust
    if (Isomorphic(root1, root2)) { printf("Yes\n"); }
    else { printf("No\n"); }
    
    return 0;
}

Tree BuildTree(struct Node T[])
{
    int N = 0;
    scanf("%d\n", &N);

    if (N)
    {   
        int check[N];
        for (int i = 0; i < N; i++)
        {
            /* �ж��ǲ��Ǹ������ж����� */
            check[i] = 1;
        }
        
        for (int i = 0; i < N; i++)
        {
            char c2, c3;
            scanf("%c %c %c\n", &T[i].data, &c2, &c3);

            /*������ת��Ϊint���ж��ǲ��� ��-��*/
            if (c2 == '-')
            {
                T[i].left = -1;
            }else{
                T[i].left = c2 - '0';
                check[T[i].left] = 0;
            }
            
            if (c3 == '-')
            {
                T[i].right = -1;
            }else{
                T[i].right = c3 - '0';
                check[T[i].right] = 0;
            }
        }

        for (int i = 0; i < N; i++)
        {
            /* ���Ҹ���� */
            if (check[i])
            {
                return i;
            }
        }
        
    }

    //���û�������Խ���
    return Null;
}

int Isomorphic(Tree r1, Tree r2)
{
    //���ǿ���, ͬ��
    if (r1 == Null && r2 == Null)
    {
        return 1;
    }

    //һ����Ϊ�գ�һ������Ϊ��
    if ((r1 == Null && r2 != Null) || (r2 == Null && r1 != Null))
    {
        return 0;
    }
    
    
    //����㶼��һ������ͬ��
    if (T1[r1].data != T2[r2].data)
    {
        return 0;
    }

    //�������������ǿյģ���Ҫ�ж��������Ƿ�ͬ��
    if ((T1[r1].left == Null) && (T2[r2].left == Null))
    {
        return Isomorphic(T1[r1].right, T2[r2].right);
    }
    
    if ((T1[r1].left != Null) && (T2[r2].left != Null) &&
        (T1[T1[r1].left].data == T2[T2[r2].left].data))
    {
        /* �����������գ������������Ľ��һ�£�����Ҫ���� */
        return ( Isomorphic(T1[r1].left, T2[r2].left) &&
                 Isomorphic(T1[r1].right, T2[r2].right));
    }else{
        /* ��Ҫ���� */
        return ( Isomorphic(T1[r1].left, T2[r2].right) &&
                 Isomorphic(T1[r1].right, T2[r2].left));
    }
    
}