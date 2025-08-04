#include <iostream>
#include <limits>
#include <vector>


typedef struct Node* PtrToNode;
struct Node
{
	int length;
	int charge;
	Node(int len, int ch) : length(len), charge(ch) {}
};


class TravelMenu
{
public:
	TravelMenu(int numcities);
	~TravelMenu();

	void readEdges(int num);
	void checkPath(int scity, int ecity);

private:
	int NumCities;										// ��������
	std::vector<std::vector<PtrToNode>> Data;			// ���й�·�����ٷ�
	/*std::vector<int> Path;*/							// ��Ŀ����Ҫ��ӡ���·��
	std::vector<int> Dist;								// 
	std::vector<int> Payment;							// 
	std::vector<bool> Visited;							// �Ƿ���ʹ��ı�־λ

	void insertEdgeHelper(int c1, int c2, int len, int pay);
	void Dijkstra(int startCity);
};

TravelMenu::TravelMenu(int numcities) : NumCities(numcities)
{
	Data.resize(numcities, std::vector<PtrToNode>(numcities, nullptr));
	Dist.resize(numcities, std::numeric_limits<int>::max());
	Payment.resize(numcities, std::numeric_limits<int>::max());
	Visited.resize(numcities, false);
}

TravelMenu::~TravelMenu()
{
	for (size_t i = 0; i < NumCities; i++)
	{
		for (size_t j = 0; j < NumCities; j++)
		{
			PtrToNode item = Data.at(i).at(j);
			if (item)
			{
				delete(item);
				Data.at(i).at(j) = nullptr;
				Data.at(j).at(i) = nullptr;
			}
		}
	}
}

void TravelMenu::Dijkstra(int startCity)
{
	Dist.at(startCity) = 0;
	Payment.at(startCity) = 0;

	while (true)
	{
		int nextItem = -1;
		int min = std::numeric_limits<int>::max();
		int minP = std::numeric_limits<int>::max();

		for (size_t i = 0; i < NumCities; i++)
		{
			// �ҵ�һ��û�з��ʹ��ģ�Dist ��С�ĵ�
			if (!Visited.at(i) && Dist.at(i) < min)
			{
				nextItem = i;
				min = Dist.at(i);
				minP = Payment.at(i);
			}
		}

		if (-1 == nextItem)		return;

		Visited.at(nextItem) = true;

		for (size_t i = 0; i < NumCities; i++)
		{
			// ��ͨ������ӵ�ǰ�㵽Ŀ�����죨�ȵ�Ŀ��������·�ߣ�
			if (!Visited.at(i) && Data.at(nextItem).at(i) 
				&& ((Dist.at(nextItem) + Data.at(nextItem).at(i)->length) < Dist.at(i)))
			{
				Dist.at(i) = Dist.at(nextItem) + Data.at(nextItem).at(i)->length;
				Payment.at(i) = Payment.at(nextItem) + Data.at(nextItem).at(i)->charge;
			}
			// �������������¼��һ���죬�ȸ��ٷ��ĸ���
			else if (!Visited.at(i) && Data.at(nextItem).at(i)
				&& ((Dist.at(nextItem) + Data.at(nextItem).at(i)->length) == Dist.at(i)))
			{
				if (Payment.at(nextItem) + Data.at(nextItem).at(i)->charge < Payment.at(i))
				{
					Payment.at(i) = Payment.at(nextItem) + Data.at(nextItem).at(i)->charge;
				}
			}
		}
	}
}

void TravelMenu::checkPath(int scity, int ecity)
{
	// ����Dijkstra�㷨�����㵥Դ��Ȩ·��ͼ
	Dijkstra(scity);

	// ��Ŀ˵��֤�˽�Ĵ��ڣ��Ǿ�ֱ���ҵ�ֵ���������
	std::cout << Dist.at(ecity) << " " << Payment.at(ecity);
}

void TravelMenu::insertEdgeHelper(int c1, int c2, int len, int pay)
{
	PtrToNode itemPtr = new Node(len, pay);

	Data.at(c1).at(c2) = itemPtr;
	Data.at(c2).at(c1) = itemPtr;
}

void TravelMenu::readEdges(int num)
{
	for (size_t i = 0; i < num; i++)
	{
		int city1 = 0, city2 = 0, length = 0, payment = 0;
		std::cin >> city1 >> city2 >> length >> payment;

		insertEdgeHelper(city1, city2, length, payment);
	}
}

int main()
{
	int numOfCities = 0;
	int numOfRoads = 0;
	int startCity = -1;
	int endCity = -1;

	std::cin >> numOfCities >> numOfRoads >> startCity >> endCity;

	TravelMenu menu(numOfCities);							// �����������ʻ�
		
	menu.readEdges(numOfRoads);								// �����������

	menu.checkPath(startCity, endCity);						// �ҵ���̵�·��

	return 0;
}