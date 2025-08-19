#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

class SavingJames
{
public:
	SavingJames(int N, int D) : JumpDistance(D), Num(0)
	{
		Position.at(0) = 0;
		Position.at(1) = 0;
		CrocodilesP.resize(N);
		Visited.resize(N, false);
	}
	~SavingJames() {}

	// �������������
	void ReadCrocodiles(int N)
	{
		for (int i = 0; i < N; i++)
		{
			int x = 0, y = 0;
			std::cin >> x >> y;
			writeHelper(x, y);
		}
	}

	// �ж��ǲ��ǵ�һ�����Ӱ�����
	bool IsFirstStep()
	{
		return ((Position.at(0) == 0) && (Position.at(1) == 0));
	}

	bool IsSafe()
	{
		int a = 50 - std::abs(Position.at(0));
		int b = 50 - std::abs(Position.at(1));

		return ((a <= JumpDistance) || (b <= JumpDistance));
	}

	bool DFS(int root)
	{
		int originalPosition0 = Position.at(0);
		int originalPosition1 = Position.at(1);

		bool result = false;

		// ·�����Ѿ����ʹ���ֱ�ӷ���false
		if (Visited.at(root))
		{
			return false;
		}

		// ���ܲ������ù���
		// �ǴӰ������ĵ�һ��
		if (IsFirstStep())
		{
			/*std::cout << "James Bond �Ӱ���׼������" << std::endl;*/

			long double distance = sqrt(pow(CrocodilesP.at(root).at(0), 2) + pow(CrocodilesP.at(root).at(1), 2));
			if (distance > (long double)JumpDistance + 7.5)
			{

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "��ֻ����������ȥ,����ԭ��  " << distance << std::endl;*/

				return false;
			}
			else {

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "����������ֻ����������,����ԭ��  " << distance << std::endl;*/

				Visited.at(root) = true;
				Position.at(0) = CrocodilesP.at(root).at(0);
				Position.at(1) = CrocodilesP.at(root).at(1);
			}
		}
		// ��һֻ����ͷ��������һ������ͷ��
		else {
			long double distance = sqrt(pow(CrocodilesP.at(root).at(0) - Position.at(0), 2) + pow(CrocodilesP.at(root).at(1) - Position.at(1), 2));
			if (distance > (long double)JumpDistance)
			{
				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "��ֻ����������ȥ������" << Position.at(0) 
					<< Position.at(1)  << "    " << distance << std::endl;*/

				return false;
			}
			else {

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "����������ֻ���������ˣ�����" << Position.at(0)
					<< Position.at(1) << "    " << distance << std::endl;*/

				Visited.at(root) = true;
				Position.at(0) = CrocodilesP.at(root).at(0);
				Position.at(1) = CrocodilesP.at(root).at(1);
			}
		}
		// ���ˣ�������������
		Visited.at(root) = true;
		// ���ӵ�ǰ�����ܲ���ֱ���ϰ�
		if (IsSafe())
		{
			/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "�����ϰ���" << std::endl;*/

			return true;
		}
		else {
			for (int i = 0; i < Num; i++)
			{
				// ��֪���ǲ����ڽӵ㣬���Ա���ȫ���ĵ�
				if (!Visited.at(i))
				{
					result = DFS(i);
					if (result)
					{
						break;
					}
				}
			}
		}

		// ���������ǰ���Ϻ���û�к��ʵ�·�ˣ��Ǿ�֤�������Ҳ����������ȥ�ոյ�λ�ã�Ȼ���������Ҫ���÷���״̬
		if (!result)
		{
			Position.at(0) = originalPosition0;
			Position.at(1) = originalPosition1;
			Visited.at(root) = false;
		}

		return result;
	}

	void EscapeCheck()
	{
		bool f = false;

		for (int i = 0; i < Num; i++)
		{
			f = DFS(i);

			if (f)
			{
				break;
			}
			
			std::fill(Visited.begin(), Visited.end(), false);
		}

		if (f)
		{
			std::cout << "Yes";
		}
		else {
			std::cout << "No";
		}
	}

private:
	std::array<int, 2> Position;
	int JumpDistance;
	int Num;
	std::vector<std::array<int, 2>> CrocodilesP;
	std::vector<bool> Visited;

	void writeHelper(int x, int y)
	{
		CrocodilesP.at(Num).at(0) = x;
		CrocodilesP.at(Num).at(1) = y;
		Num++;
	}
};

int main()
{
	int N = 0, D = 0;
	std::cin >> N >> D;
	SavingJames Bond(N, D);

	// �������������
	Bond.ReadCrocodiles(N);
	
	// �����ܲ����ϰ�
	Bond.EscapeCheck();

	return 0;
}