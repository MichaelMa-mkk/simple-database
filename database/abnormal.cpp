#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
����������
��������10��
ѭ��һ�²�����
��ѯһ������
ɾ����������
ɾ����������
����һ�����ݣ���ֵ����
��ѯ�ü�ֵ
ѭ������1���
*/

int generateRandomInt()
{
	random_device rd;
	uniform_int_distribution<int> dist(0, 99999);
	return dist(rd);
}

void test_correctness_bigdata()
{
	database db("test");
	db.open(CREATE);
	db.close();
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		db.store(i, to_string(i));
		/*if (!db.fetchtest(i, to_string(i)))
		{
		cout << i << endl;
		}*/
	}
	db.close();
}

void abnomalTest()
{
	database db("test");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 10000; ++i)
	{
		int m = generateRandomInt();
		if (!db.fetchtest(i, to_string(i)))
		{
			cout << i << "fetch wrong" << endl;
		}
		if (db.remove(i) != true)
		{
			cout << i << "remove wrong" << endl;
		}
		if (db.remove(i) != false)
		{
			cout << i << "remove s wrong" << endl;
		}
		db.store(i, to_string(i));
		if (!db.fetchtest(i, to_string(i)))
		{
			cout << i << "fetch s wrong" << endl;
		}
	}
}

int main()
{
	test_correctness_bigdata();
	abnomalTest();
	return 0;
}