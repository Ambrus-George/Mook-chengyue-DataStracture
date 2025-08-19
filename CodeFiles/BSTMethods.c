/* ��Ĵ��뽫��Ƕ������ */
/* ����Insert��X�������������BST�����ؽ�����ĸ����ָ�� */
BinTree Insert( BinTree BST, ElementType X ){
    if (!BST)
    {
        Position node = (Position)malloc(sizeof(struct TNode));
        node->Data = X;
        node->Left = NULL;
        node->Right = NULL;

        return node;
    }else{
        if (X >= BST->Data)
        {
            BST->Right = Insert(BST->Right, X);
        }else{
            BST->Left = Insert(BST->Left, X);
        }  
    }
    return BST;
}

/* ����Delete��X�Ӷ���������BST��ɾ���������ؽ�����ĸ����ָ�룻
���X�������У����ӡһ��Not Found������ԭ���ĸ����ָ�� */
BinTree Delete( BinTree BST, ElementType X ){

    if (!BST)
    {
        printf("Not Found\n");
    }else{
        if (X == BST->Data)
        {
            /* found */
            if ((BST->Left) && (BST->Right))
            {
                Position Pitem = FindMin(BST->Right);
                BST->Data = Pitem->Data;
                BST->Right = Delete(BST->Right, Pitem->Data);
            }else{
                Position Pitem = BST;
                if (BST->Left)      BST = BST->Left;
                else                BST = BST->Right;
                free(Pitem);
            }
            
        }

        else if (X > BST->Data)     BST->Right = Delete(BST->Right, X);
        else                        BST->Left = Delete(BST->Left, X);
        
        
    }
    return BST;
}

/* ����Find�ڶ���������BST���ҵ�X�����ظý���ָ�룻����Ҳ����򷵻ؿ�ָ�� */
Position Find( BinTree BST, ElementType X ){
    Position Pitem = NULL;

    if (!BST)  return NULL;
    else{
        if (X == BST->Data)     Pitem = BST;
        else if (X > BST->Data) Pitem = Find(BST->Right, X);
        else                    Pitem = Find(BST->Left, X);
    }
    return Pitem;
}

/* ����FindMin���ض���������BST����СԪ����ָ�� */
Position FindMin( BinTree BST ){

    if (BST){
        while (BST->Left)       BST = BST->Left;
    }
    return BST;
}

/* ����FindMax���ض���������BST�����Ԫ����ָ�� */
Position FindMax( BinTree BST ){
    if (BST){
        while (BST->Right)      BST = BST->Right;
    }
    return BST;
}