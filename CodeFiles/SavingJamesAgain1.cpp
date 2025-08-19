#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stack>

typedef struct Node *PtrToNode;
struct Node {
	int x;					// ��������
	int y;
	bool canJump;			// �Ƿ񿿽����ĵ�
	bool isSafe;			// �Ƿ񿿽�����
	Node(int x, int y, bool c, bool s) : x(x), y(y), canJump(c), isSafe(s) {}
};

class SavingJamesAgain
{
public:
	SavingJamesAgain(int N, int M) : NumOfCorcodiles(N), StepLength(M), diameter(15.0)
	{
		Corcodiles.resize(N, nullptr);
		Pre.resize(N, -1);
		Dist.resize(N, std::numeric_limits<int>::max());
		Connection.resize(N, std::vector<bool>(N, false));
		Visited.resize(N, false);
	}
	~SavingJamesAgain()
	{
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			delete(Corcodiles.at(i));
		}
	}

	bool canJump(int x, int y)																	
	{
		double distance = std::sqrt(std::pow((double)x, 2) + std::pow((double)y, 2));
		return ((diameter / 2 + StepLength) > distance);
	}

	bool isSafe(int x, int y)
	{
		return (((StepLength + std::abs(x)) >= 50) || ((StepLength + std::abs(y)) >= 50));
	}

	bool isConnected(int x, int y, int m, int n)
	{
		double distace = std::pow((double)x - (double)m, 2) + std::pow((double)y - (double)n, 2);
		return distace <= std::pow(StepLength, 2);
	}

	void initData()
	{
		// ��������
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			int x = 0, y = 0;
			std::cin >> x >> y;
			bool c = canJump(x, y);
			bool s = isSafe(x, y);

			Corcodiles.at(i) = new Node(x, y, c, s);
		}

		// ��������֮���������ȥ
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			for (size_t j = 0; j < NumOfCorcodiles; j++)
			{
				Connection.at(i).at(j) = isConnected(Corcodiles.at(i)->x, Corcodiles.at(i)->y, Corcodiles.at(j)->x, Corcodiles.at(j)->y);
			}
		}

	}

	void Dijkstra(int item)
	{
		Dist.at(item) = 0;

		while (true)
		{
			int nextItem = -1;
			int min = std::numeric_limits<int>::max();

			for (size_t i = 0; i < NumOfCorcodiles; i++)
			{
				if (!Visited.at(i) && (Dist.at(i) < min))
				{
					nextItem = i;
					min = Dist.at(i);
				}
			}

			if (nextItem == -1)	return;
			Visited.at(nextItem) = true;

			for (size_t i = 0; i < NumOfCorcodiles; i++)
			{
				if (!Visited.at(i) && Connection.at(nextItem).at(i) && ((Dist.at(nextItem) + 1) < Dist.at(i)))
				{
					Dist.at(i) = Dist.at(nextItem) + 1;
					Pre.at(i) = nextItem;
				}
			}
		}
	}

	bool comp(int a, int b)    // ���� a ��� b ����������ĵ�
	{
		double dis_a = std::pow(Corcodiles.at(a)->x, 2) + std::pow(Corcodiles.at(a)->y, 2);
		double dis_b = std::pow(Corcodiles.at(b)->x, 2) + std::pow(Corcodiles.at(b)->y, 2);

		return dis_a < dis_b;
	}

	void printPath(int starIndex, int endIndex, std::vector<int>& path)
	{
		std::stack<int> S;

		while (endIndex != starIndex)
		{
			S.push(endIndex);
			endIndex = path.at(endIndex);
		}

		S.push(starIndex);

		while (!S.empty())
		{
			int item = S.top();
			std::cout << Corcodiles.at(item)->x << " " << Corcodiles.at(item)->y << std::endl;
			S.pop();
		}
	}

	void saving007()
	{
		// ���Դ����ĵ�ֱ���ϰ�
		if (((diameter / 2) + StepLength) >= 50.0)
		{
			std::cout << "1";
			return;
		}

		int starAdd = -1;								// ���·����ֵ  // ���
		int endAdd = -1;												 // �յ�
		int minDist = std::numeric_limits<int>::max();					 // ��С����
		std::vector<int> Path(NumOfCorcodiles, -1);						 // ·��

		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			if (Corcodiles.at(i)->canJump)														// �����·�������
			{
				std::fill(Pre.begin(), Pre.end(), -1);
				std::fill(Dist.begin(), Dist.end(), std::numeric_limits<int>::max());
				std::fill(Visited.begin(), Visited.end(), false);

				Dijkstra(i);

				for (size_t j = 0; j < NumOfCorcodiles; j++)
				{
					if (Corcodiles.at(j)->isSafe && minDist > Dist.at(j))						// �Ҷ�Ӧ�����յ�
					{
						starAdd = i;
						endAdd = j;
						minDist = Dist.at(j);
						Path = Pre;
					}
					else if (Corcodiles.at(j)->isSafe && Dist.at(j) !=std::numeric_limits<int>::max() && minDist == Dist.at(j) && comp(i, starAdd))
					{
						starAdd = i;
						endAdd = j;
						minDist = Dist.at(j);
						Path = Pre;
					}
				}
			}
		}


		if (minDist == std::numeric_limits<int>::max())
		{
			std::cout << "0";
		}
		else {
			std::cout << minDist + 2 << std::endl;
			printPath(starAdd, endAdd, Path);
		}
	}


private:
	double diameter;
	int NumOfCorcodiles;						// ��������
	int StepLength;								// Bond������Զ
	std::vector<PtrToNode> Corcodiles;			// ������������
	std::vector<std::vector<bool>> Connection;	// ����֮���Ƿ�������ȥ

	std::vector<int> Pre;						// �ϰ�·��
	std::vector<int> Dist;						// ÿ������������Ծ����
	std::vector<bool>Visited;					// ������û�б����ʹ�
};

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	SavingJamesAgain Bond(N, M);

	Bond.initData();

	Bond.saving007();

	return 0;
}