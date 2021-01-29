#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
�ռ����ܲ���
����databin�Կռ���Ż�Ч��
���Ա�ɾ�����ƶ�index��С��Ӱ��
�������n�����ݣ����ɾ��n/2�����ݣ����������n/2������
*/

int generateRandomInt()
{
	random_device rd;
	uniform_int_distribution<int> dist(0, 1500000);
	return dist(rd);
}

void spaceTest()
{
	string v = "1";
	database db("test");
	db.open(CREATE);
	db.close();
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 1000000; ++i)
	{
		int m = generateRandomInt();
		db.store(m, v);
	}
	cout << "store ok" << endl;
	for (int i = 0; i < 500000; ++i)
	{
		int m = generateRandomInt();
		db.remove(m);
	}
	for (int i = 0; i < 500000; ++i)
	{
		int m = generateRandomInt();
		db.store(m, v);
	}
	cout << "test ok" << endl;
	cin.get();
}

int main()
{
	spaceTest();
	return 0;
}