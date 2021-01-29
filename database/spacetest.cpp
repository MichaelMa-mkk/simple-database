#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
空间性能测试
测试databin对空间的优化效果
测试本删除机制对index大小的影响
随机插入n条数据，随机删除n/2条数据，再随机插入n/2条数据
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