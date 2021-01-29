#ifndef BUFFER_H
#define BUFFER_H
#include<iostream>
#include<queue>
#include<fstream>
using namespace std;

struct dataTokenBuffer// used to reserve modified message
{
	int pos;
	string value;
	dataTokenBuffer(int pos, string value = "")
	{
		this->pos = pos;
		this->value = value;
	}
};

#endif
