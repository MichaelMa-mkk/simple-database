#ifndef DATAFILE_H
#define DATAFILE_H
#include<iostream>
#include<fstream>
#include<string>
#include "buffer.hpp"
#include "BPnode.h"
#include "space.h"

using namespace std;

class wrongDataFile{};
class datafile
{
private:
	fstream f;
	databin freeSpace;
public:
	datafile() {};
	void openDatafile(string path, file method);
	void closeDatafile();
	string valueData(int pos,int length);// get data from disk
	int insert(string value);// insert data to disk
	void deleteValue(int pos, int length);// remove data from disk
	int modify(int pos, int length, string value);// update data in disk
};

#endif
