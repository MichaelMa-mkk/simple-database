#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
非正常测试
数据量：10万
循环一下操作：
查询一条数据
删除本条数据
删除本条数据
插入一条数据，键值不变
查询该键值
循环操作1万次
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