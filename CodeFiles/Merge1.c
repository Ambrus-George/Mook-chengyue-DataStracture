/*
�Ƚϼ򵥣���Ҫϸ�����⣬��Ŀ���м���ϸ�ڣ�
1.��С��������
2.ʹ��L1��L2�Ľ��
3.L1��L2 ���Ǵ���ͷ����**************************���̫��Ҫ��
4.���������б�Ҳ��Ҫ����ͷ���********************���̫��Ҫ��

����ע�⣺��������ڵı�����������µı�����ȡ������Ӱ�캯���������
 */
List Merge( List L1, List L2 ){
    /*����ͷ��㣬�ύ�����Ҫ����ͷ���*/
    PtrToNode front;
    PtrToNode rear;
    List l1, l2;
    front = (List)malloc(sizeof(PtrToNode));
    rear = front;
    front->Next = NULL;

    l1 = L1->Next;
    l2 = L2->Next;

    /**/
    while (l1 && l2)
    {
        /*L1�Ľ��ָ����*/
        if (l1->Data < l2->Data)
        {
            rear->Next = l1;
            rear = rear->Next;
            l1 = l1->Next;
        }
        
        /*L2�Ľ��ָ���ͻ����������һ��*/
        else{
            rear->Next = l2;
            rear = rear->Next;
            l2 = l2->Next;
        }
    }

    /*ʣ�µĽ�㶼��L1��*/
    if (l1)
    {
        rear->Next = l1;
    }
    
    /*ʣ�µĽ�㶼��L2��*/
    if (l2)
    {
        rear->Next = l2;
    }

    L1->Next = NULL;
    L2->Next = NULL;

    return front;
}