#include "datafile.h"

void datafile::openDatafile(string path, file method)
{
	switch (method)
	{
	case READ_ONLY:
		f.open(path, ios::binary | ios::in);
		if (!f) throw wrongDataFile();
		break;
	case CREATE:
		f.open(path, ios::binary | ios::out);
		break;
	case READ_AND_WRITE:
		f.open(path, ios::binary | ios::out | ios::in);
		if (!f.is_open())
		{
			throw wrongDataFile();
		}
		break;
	}
}

void datafile::closeDatafile()
{
	f.close();
}

int datafile::insert(string value)
{
	value += '\0';
	int length = value.size();
	int vpos = freeSpace.getPos(length);
	if (vpos != -1)// reuse the free space
	{
		f.seekp(vpos);
		f.write(value.c_str(), length);
		return vpos;
	}
	else
	{
		f.seekp(0,ios::end);
		vpos = f.tellp();
		f.write(value.c_str(), length);
		return vpos;
	}
}

void datafile::deleteValue(int pos, int length)// add space to freeSpace
{
	freeSpace.insert(pos, length);
}

int datafile::modify(int pos, int length, string value)// not determinable length value update
{
	deleteValue(pos, length);
	return insert(value);
}

string datafile::valueData(int pos, int length)
{
	f.seekg(pos);
	char *content = new char[length];
	f.read(content, length);
	string tmp(content);
	delete content;
	return tmp;
}
