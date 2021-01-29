#include "database.h"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
综合测试
数据量：100万
循环一下操作：
查询一条数据
删除本条数据
删除本条数据
插入一条数据，键值不变
查询该键值
循环操作1万次
*/

set<int> writeIn;

int generateRandomInt()
{
	random_device rd;
	uniform_int_distribution<int> dist(0, 10000000);
	return dist(rd);
}

void createFile()
{
	fstream f;
	f.open("index", ios::binary | ios::out);
	f.close();
	f.open("data", ios::binary | ios::out);
	f.close();
}

void test_correctness_bigdata()
{
	string m = " ";
	createFile();
	database db("index", "data");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 1000000; ++i)
	{
		/*int num = generateRandomInt();
		db.store(num, m);
		if (writeIn.count(num) == 0)
		{
			writeIn.insert(num);
		}*/
		db.store(i, m);
		/*if (writeIn.count(i) == 0)
		{
			writeIn.insert(i);
		}
		/*if (!db.fetchtest(i, to_string(i)))
		{
		cout << i << endl;
		}*/
	}
	cout << "store ok" << endl;
	db.close();
}

void generalTest()
{
	string m = " ";
	database db("index", "data");
	db.open(READ_AND_WRITE);
	int i = 1;
	while (i++ < 5000000)
	{
		int num = generateRandomInt();
		db.fetch(num);
		if (i % 37 == 0)
		{
			int num = generateRandomInt();
			db.remove(num);
			if (writeIn.count(num) != 0)
			{
				writeIn.erase(num);
			}
		}
		if (i % 11 == 0)
		{
			int num = generateRandomInt();
			db.store(num, m);
			if (writeIn.count(num) == 0)
			{
				writeIn.insert(num);
			}
			db.fetch(num);
		}
		if (i % 17 == 0 && i % 34 != 0)
		{
			int num = generateRandomInt();
			db.modify(num, m);
		}
		if (i % 34 == 0)
		{
			int num = generateRandomInt();
			db.modify(num, m + m);
		}
	}
	cout << "test ok" << endl;
	for (int j : writeIn)
	{
		db.remove(j);
		for (int z = 0; i < 10; ++z)
		{
			int num = generateRandomInt();
			db.fetch(num);
		}
	}
	cout << "delete ok" << endl;
}

int main()
{
	test_correctness_bigdata();
	generalTest();
	cin.get();
	return 0;
}