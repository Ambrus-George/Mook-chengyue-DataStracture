#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

#define MAXSIZE 1000

typedef int ElementType;

bool hadprinted = false;

class CompleteBinaryTree
{
public:
	CompleteBinaryTree() : Data{ 0 }, CBTData{ 0 }, index(0) {}
	~CompleteBinaryTree() {}

	void readSortCBT(int N)
	{
		if (N)
		{
			readSortHelper(N);
		}
		
	}

	void levelOrderOutputCBT()
	{
		if (!index)
		{
			return;
		}

		for (int i = 0; i < index; i++)
		{
			if (!i) {
				std::cout << CBTData[i + 1];
			}
			else {
				std::cout << " " << CBTData[i + 1];
			}
		}

	}

	int findRootIndex(int startIndex, int endIndex)
	{
		if (startIndex == endIndex)
		{
			return startIndex;
		}

		if (startIndex > endIndex)
		{
			return 0;
		}

		// һ���� num ��ֵ
		int num = endIndex - startIndex + 1;
		// һ���� height ��
		int height = 0;

		for (; (int)(std::pow(2, height) - 1) <= num; height++)
		{

		}

		// �������һ��ȫ��
		if ((int)(std::pow(2, height -1) - 1) == num)
		{
			return (num/2 + startIndex);
		}
		// ���һ��δ����δ����
		else if (3 * (int)std::pow(2, height - 2) - 1 >= num)
		{
			int lastLevelNum = num - (int)std::pow(2, height - 1) + 1;
			int rootindex = (num - lastLevelNum) / 2 + startIndex + lastLevelNum;
			return rootindex;
		}
		// ���һ��δ���ҹ���
		else
		{
			int lastLevelNum = num - (int)std::pow(2, height - 1) + 1;
			int rootindex = (num - lastLevelNum) / 2 + startIndex + (int)std::pow(2, height - 2);
			return rootindex;
		}
	}

	void levelOrderCreate(int in, int left, int right)
	{
		levelOrderCreateHelper(1, 1, index);
	}
	
private:

	std::array<ElementType, MAXSIZE + 1> Data;
	std::array<ElementType, MAXSIZE + 1> CBTData;
	int index;

	void levelOrderCreateHelper(int in, int left, int right)
	{
		
		// һ���� num ��ֵ
		int num = right - left + 1;

		if (!num || num < 0)
		{
			return;
		}

		int rindex = findRootIndex(left, right);
		CBTData[in] = Data[rindex];

		levelOrderCreateHelper(in * 2, left, rindex - 1);
		levelOrderCreateHelper(in * 2 + 1, rindex + 1, right);
	}

	void readSortHelper(int N)
	{

		index = N;
		for (int i = 0; i < N; i++)
		{
			std::cin >> Data[i + 1];
		}
		std::sort(Data.begin() + 1, Data.begin() + index +1);

	}
};

int main()
{
	int N = 0;
	CompleteBinaryTree CBT;

	std::cin >> N;

	CBT.readSortCBT(N);
	CBT.levelOrderCreate(1, 1, N);
	CBT.levelOrderOutputCBT();

	

	return 0;
}