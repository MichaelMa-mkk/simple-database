#include"datafile.h"
#include "database.h"
#include"indexfile.h"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include"windows.h"

/*正确性测试
插入100万条<i,to_string(i)>数据
查询这100万条数据
修改1万条数据
查询修改的1万条数据
删除1万条数据
查询删除的1万条数据
插入1万条数据，其键值为前述所删除的1万条数据键值
查询再次插入的1万条数据
*/

int generateRandomInt()
{
	random_device rd;
	uniform_int_distribution<int> dist(0, 10000000);
	return dist(rd);
}

void test_modify()
{
	database db("test");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		db.modify(i, to_string(i + 1));
	}
	cout << "test modify finish" << endl;
	db.close();
}

void modify_correctness()
{
	database db("test");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		if (!db.fetchtest(i, to_string(i + 1)))
		{
			cout << i << endl;
		}
	}
	cout << "modify correctness finish" << endl;
}

void test_correctness_bigdata()
{
	string test = "1";
	database db("test");
	db.open(CREATE);
	db.close();
	db.open(READ_AND_WRITE);
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	double time = 0;
	double storetime = 0;
	for (int i = 0; i < 10000; ++i)
	{
		int num = generateRandomInt();
		QueryPerformanceCounter(&nBeginTime);
		db.store(num, to_string(num));
		QueryPerformanceCounter(&nEndTime);
		

		storetime += time;
	}
	cout << "存储执行时间：" << storetime << "s" << endl;
	cin.get();
	db.close();
}

void test_remove()
{
	database db("test");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		db.remove(i);
	}
	cout << "test remove finish" << endl;
}

void remove_correctness()
{
	database db("test");
	string result = "false";
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		if (!db.fetchtest(i, to_string(i)))
		{
			cout << i << endl;
		}
	}
	cout << "remove correctness finish" << endl;
}

void insertAfterRemove_correctness()
{
	database db("test");
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 100000; ++i)
	{
		db.store(i, to_string(i));
	}
	cout << "inserAfterRemove finish" << endl;
}

int main()
{
	test_correctness_bigdata();
	test_remove();
	//remove_correctness();
	insertAfterRemove_correctness();
	remove_correctness();
	test_modify();
	modify_correctness();

	cout << "ok";
	cin.get();
	return 0;
}