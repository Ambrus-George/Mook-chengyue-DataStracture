#include <stdio.h>

#define S_SIZE 5
#define MAX_SIZE 30

void OutputResult(int *preO, int *inO, int N);
void PrintPost(int* preO, int* inO, int N);

int printFlag = 0;
//Push ��˳�������������Ľ��
int preOrder[MAX_SIZE];
//Pop ��˳�������������Ľ��
int inOrder[MAX_SIZE];

int main()
{
    int N = 0;
    scanf("%d\n", &N);

    if (N)
    {
        OutputResult(preOrder, inOrder, N);
    }
    

    return 0;
}

void OutputResult(int *preO, int *inO, int N)
{
    int stack[N];//ģ���ջ
    int p_stack = -1;

    int pushNum = 0;
    int popNum = 0;

    for (int i = 0; i < (N + N); i++)
    {
        char s[S_SIZE] = {0};//��š�Push", "Pop"
        scanf("%s", s);
        
        if ('u' == s[1])
        {
            int item = 0;
            scanf(" %d\n", &item);
            *(preO + pushNum) = item; //�����������
            pushNum++;
            stack[++p_stack] = item;//��ջ���
        }else{
            *(inO + popNum) = stack[p_stack--];
            popNum++;
        }
        
    }
    PrintPost(preO, inO, N);
}

/*��ӡ����������*/
void PrintPost(int* preO, int* inO, int N)
{
    int n = N;

    if (1 == n)
    {
        
        if (printFlag)
        {
            printf(" ");
        }
        
        printf("%d", *preO);
        printFlag = 1;

        return;
    }

    
    int root = *preO;
    int nLeft = 0;

    for (int i = 0; i < n; i++)
    {
        /* ��������������Ҹ���� */
        if (root == *(inO + i))
        {
            nLeft = i;
            break;
        }
        
    }
    
    /* ����������� */
    if (nLeft)
    {
        PrintPost((preO+1), inO, nLeft);
    }

    /* ����������� */
    if (N-1-nLeft)
    {
        PrintPost((preO+nLeft+1), (inO+nLeft+1), (N-1-nLeft));
    }

    /* ����������� */
    PrintPost(preO, inO+nLeft, 1);
}