#include <iostream>
#include <vector>
#include <limits>

typedef struct Node* PtrToNode;
struct Node
{
	int edgeWeight;
	int vertex_1;
	int vertex_2;
	Node(int weight, int v1, int v2) : edgeWeight(weight), vertex_1(v1), vertex_2(v2) {}
};

class MinHeap
{
public:
	MinHeap() {}
	~MinHeap()
	{
		for (int i = 0; i <= size; ++i)
		{
			delete heap.at(i);
		}
	}

	void init(int capacity)
	{
		size = 0;
		heap.resize(capacity + 1, nullptr);	// ʵ������С�Ѵ�1��ʼ�洢
		heap.at(0) = new Node(0, -1, -1);	// 0��λ��һ������С��ֵ
	}

	void insert(PtrToNode newptr)
	{
		insertHelper(newptr);
	}

	PtrToNode top()
	{
		return heap.at(1);
	}

	void deleteMin()
	{
		deleteHelper();
	}

	bool isEmpty()
	{
		return (size == 0);
	}

private:
	int size;
	std::vector<PtrToNode> heap;

	void insertHelper(PtrToNode newptr)
	{
		size++;
		size_t index = size;

		for (; newptr->edgeWeight < heap.at(index/2)->edgeWeight; 
				index /= 2)
		{
			heap.at(index) = heap.at(index / 2);
		}

		heap.at(index) = newptr;
	}

	void deleteHelper()		// ɾ����Сֵ���������Ǽ�װ����һ��ֵ�ڳ�ʼλ��Ȼ���������·���ϵ�ֵ
	{
		if (isEmpty())
		{
			return;
		}

		delete heap.at(1);
		heap.at(1) = nullptr;

		size_t parent = 1;
		size_t child = 0;
		for (; parent*2 <= size; parent = child)
		{
			
			child = parent * 2;

			// ѡ�������ӽڵ�Ȩ�ؽ�С���Ǹ�
			if (child + 1 <= size &&
				heap.at(child + 1)->edgeWeight < heap.at(child)->edgeWeight)
			{
				child++;
			}

			// �ҵ����ʵ�λ�ã��˳�ѭ��
			if (heap.at(size)->edgeWeight < heap.at(child)->edgeWeight)
			{
				break;
			}

			heap.at(parent) = heap.at(child);
		}

		heap.at(parent) = heap.at(size);
		size--;
	}
};

class VillagesRoads
{
public:
	VillagesRoads(int villagenum, int roadnum);
	~VillagesRoads() {}
	void init();
	void printMinCost();
	int findRoot(int m);
	bool merge(int x, int y);

private:
	int villagesNum;
	int roadsNum;
	MinHeap heap;
	std::vector<int> parent;
};

bool VillagesRoads::merge(int x, int y)
{
	int root_x = findRoot(x);
	int root_y = findRoot(y);

	if (root_x == root_y)
	{
		return false;
	}

	parent.at(root_x) = root_y;
	return true;
}

int VillagesRoads::findRoot(int m)
{
	if (parent.at(m) != m)
	{
		parent.at(m) = findRoot(parent.at(m));
	}

	return parent.at(m);
}

void VillagesRoads::printMinCost()
{
	if (roadsNum < villagesNum - 1)
	{
		std::cout << "-1";
		return;
	}

	int count = 0;			// ��¼����С�����׳��˶�������
	int workload = 0;		// �׳��ߵ�ʱ����¹�����

	while (count < (villagesNum - 1) && !heap.isEmpty())
	{
		auto item = heap.top();

		// �����һ�����������ɻ�·���ǾͲ�Ҫ��������
		int root1 = findRoot(item->vertex_1);
		int root2 = findRoot(item->vertex_2);
		if (root1 != root2)
		{
			count++;
			merge(root1, root2);
			workload += item->edgeWeight;
		}

		heap.deleteMin();
	}

	if (count < (villagesNum - 1))
	{
		std::cout << "-1";
	}
	else
	{
		std::cout << workload;
	}
}

void VillagesRoads::init()
{
	for (size_t i = 0; i < roadsNum; i++)
	{
		int weight = 0, v1 = 0, v2 = 0;
		std::cin >> v1 >> v2 >> weight;

		PtrToNode item = new Node(weight, v1, v2);
		heap.insert(item);
	}
}

VillagesRoads::VillagesRoads(int villagenum, int roadnum)
{
	villagesNum = villagenum;
	roadsNum = roadnum;
	parent.resize(villagenum + 1);
	for (size_t i = 0; i < parent.size(); i++)
	{
		parent.at(i) = (int)i;
	}
	heap.init(roadnum);
}

int main()
{
	int villagenum = 0;
	int roadsnum = 0;
	std::cin >> villagenum >> roadsnum;
	VillagesRoads CountrysidePlan(villagenum, roadsnum);

	// ��ʼ�����󣬶���ƻ��ĵ�·��Ϣ
	CountrysidePlan.init();

	CountrysidePlan.printMinCost();
}