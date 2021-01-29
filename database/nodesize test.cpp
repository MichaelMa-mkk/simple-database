#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include"windows.h"

/*
�ڵ����ʲ���
���Բ�ͬ�ڵ��ڲ�ͬ�����µĵ��β���ʱ��
*/

int generateRandomInt()
{
	random_device rd;
	uniform_int_distribution<int> dist(0,10000000);
	return dist(rd);
}


void test_correctness_bigdata()
{
	//createFile();
	//string test = "1";
	database db("test");
	db.open(CREATE);
	db.close();
	db.open(READ_AND_WRITE);
	for (int i = 0; i < 1000000; ++i)
	{
		int num = generateRandomInt();
		db.store(num, to_string(num));
		if (!db.fetchtest(num, to_string(num)))
		{
		cout << num << endl;
		}
	}
	db.close();
	cout << "ok" << endl;
	cin.get();
}

void test_time()
{
	string test = "1";
	database db("test");
	db.open(READ_AND_WRITE);

	double time;
	double storetime = 0;
	double modifytime = 0;
	double fetchtime = 0;
	double removetime = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);

	for (int i = 0; i < 1000; ++i)
	{
		int num = generateRandomInt();

		QueryPerformanceCounter(&nBeginTime);
		db.store(num, test);
		QueryPerformanceCounter(&nEndTime);// end timing
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;// second
		storetime += time;

		QueryPerformanceCounter(&nBeginTime);
		db.modify(num, to_string(num));
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		modifytime += time;

		QueryPerformanceCounter(&nBeginTime);
		if (db.fetchNoCache(num)[0] == 'f') cout << num << endl;
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		fetchtime += time;

		QueryPerformanceCounter(&nBeginTime);
		db.remove(num);
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		removetime += time;
	}
	cout << "�洢ִ��ʱ�䣺" << storetime * 1000 << "us" << endl;// transform to us, one operation time
	cout << "�޸�ִ��ʱ�䣺" << modifytime * 1000 << "us" << endl;
	cout << "��ȡִ��ʱ�䣺" << fetchtime * 1000 << "us" << endl;
	cout << "ɾ��ִ��ʱ�䣺" << removetime * 1000 << "us" << endl;
	cin.get();
}

int main()
{
	//test_correctness_bigdata();
	test_time();
	return 0;
}