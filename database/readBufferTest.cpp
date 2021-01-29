#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
ʱ������ ���������
��������10��
ѭ�����²�����
����10������
��ȡһ������
ѭ������1000��
		10000��
		100000��
*/

int generateRandomInt()
{
	return 1000 * rand() / (RAND_MAX + 1);
}


void readBufferTest()
{
	database db("test");
	db.open(CREATE);
	db.close();
	db.open(READ_AND_WRITE);
	clock_t start, end;
	start = clock();
	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			db.store(10 * i + j, to_string(10 * i + j));
		}
		db.fetch(10 * i + 5);
	}
	end = clock();
	cout << (end - start) * 1000000 / CLOCKS_PER_SEC << "us";
	cout << "test ok" << endl;
	cin.get();
}

int main()
{
	readBufferTest();
	return 0;
}