#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>

/*
时间性能 读缓存测试
数据量：10万
循环以下操作：
插入10条数据
读取一条数据
循环操作1000次
		10000次
		100000次
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