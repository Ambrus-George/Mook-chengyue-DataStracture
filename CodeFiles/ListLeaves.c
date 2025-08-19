#include <stdio.h>

#define Null -1
#define MAXSIZE 10
typedef int Tree;

int N = 0;

struct Node
{
    int position;
    Tree left;
    Tree right;
}T[MAXSIZE];

//Quence
struct Quence
{
    int quence[MAXSIZE];
    int head;
    int tail;
}Q;

Tree BuildTree(struct Node T[]);
void Output(Tree r);
void Push(int p);
int Pop();

int main()
{
    //build the tree
    Tree root = 0;
    root = BuildTree(T);

    //adjust
    Output(root);
    
    return 0;
}

Tree BuildTree(struct Node T[])
{
    scanf("%d\n", &N);

    if (N)
    {   
        int check[N];
        for (int i = 0; i < N; i++)
        {
            /* �ж��ǲ��Ǹ������ж����� */
            check[i] = 1;
            T[i].position = i;
        }
        
        for (int i = 0; i < N; i++)
        {
            char c2, c3;
            scanf("%c %c\n", &c2, &c3);

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

void Output(Tree r)
{
    //��Ҫ���������������Ҷ��㣬Ȼ�����
    //ʹ��������ʵ��һ������
    Q.head = Null;
    Q.tail = Null;

    int printflag = 0;

    Push(r);

    while (Q.head != N-1) //���пյ�ʱ�� head == N-1
    {
        int popNum = Pop(Q);

        if ((T[popNum].left == Null) && (T[popNum].right == Null))
        {
            if (printflag)
            {
                printf(" ");
            }
            /* pop �����������Ҷ��㣬��� */
            printf("%d", T[popNum].position);
            printflag = 1;
        }
        
        //pop ���������������� push
        if (T[popNum].left != Null)
        {
            Push(T[popNum].left);
        }
        
        //pop ������������ҽ��� push
        if (T[popNum].right != Null)
        {
            Push(T[popNum].right);
        }
    }

}

void Push(int p)
{
    //������Ŀ�����˽�������������Ͳ��� ���������� ���ж���
    Q.quence[Q.tail++] = p;
}

int Pop()
{
    //����������������Ͳ��� �����пա� ���ж���
    int result = Q.quence[Q.head++];
    return result;
}