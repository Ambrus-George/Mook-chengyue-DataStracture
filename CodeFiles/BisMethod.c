/*
���ַ���ûɶ�Ѷȣ�һ�� while ������д�ԣ�����ע�⣬���м����λ�ò���Ŀ�ģ��ǵ� -1/+1 ����Ϊ����Ѿ��ж�����
*/

Position BinarySearch( List L, ElementType X )
{
    Position left = 1;
    Position right = L->Last;
    Position medium = (right - left)/2 + left;

    while (left <= right)
    {
        if (X == L->Data[medium])
        {
            return medium;
        }else if(X > L->Data[medium]){
            left = ++medium;
        }else{
            right = --medium;
        }
    }
    return NotFound; 
}