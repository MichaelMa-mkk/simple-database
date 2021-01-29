#ifndef DATABASE_H
#define DATABASE_H
#include"BPnode.h"
#include"cache.hpp"
#include"datafile.h"
#include"indexfile.h"

class database
{
private:
	indexfile index;
	datafile data;
	cacheRec cache;
	string indexpath;
	string datapath;
public:
	database(string path);// initialize with one string
	database(string indexpath, string datapath);// initialize with two strings
	void setPath(string path);// update file path
	void open(file f);
	void close();
	bool store(const int& key, string& value);// insert a pair
	bool remove(const int& key);// delete a pair
	bool modify(const int& key, string& value);// update a pair
	string fetch(const int& key);// query key
	bool fetchtest(const int& key, string& value);// test if query is cosistent with expected
	string fetchNoCache(const int& key);// query key without cache
	vector<string> fetchRange(const int& start, const int& end);
	bool recovery(const int& key);// rollback a delete operation
};

database::database(string path)
{
	this->indexpath = path + "index";
	this->datapath = path + "data";
}

inline database::database(string indexpath, string datapath)
{
	this->indexpath = indexpath;
	this->datapath = datapath;
}

void database::setPath(string path)
{
	this->indexpath = path + "index";
	this->datapath = path + "data";
}

void database::open(file f)
{
	index.openIndexfile(indexpath, f);
	data.openDatafile(datapath, f);
}

void database::close()
{
	index.closeIndexfile();
	data.closeDatafile();
}

bool database::store(const int& key, string &value)
{
	if (index.isEmpty())
	{
		int vpos = data.insert(value);
		int length = value.size() + 1;
		index.insert(key, vpos, length);
		cache.addRecord(key, value);
		return true;
	}
	if (cache.ifHasKey(key))
	{
		return false;
	}
	BPnode obj = index.searchInsert(key);
	if (index.key(key, obj))
	{
		index.pathClear();
		return false;
	}
	else
	{
		int vpos = data.insert(value);
		int length = value.size() + 1;
		index.insert(key, vpos, length, 0, obj);
		cache.addRecord(key, value);
		return true;
	}
}

bool database::remove(const int& key)
{
	if (index.isEmpty()) return false;
	BPnode obj = index.search(key);
	if (index.key(key, obj))
	{
		index.deleteIdx(key, obj);
		if (cache.ifHasKey(key))
		{
			cache.deleteRecord(key);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool database::modify(const int& key, string& value)
{
	if (index.isEmpty()) return false;
	BPnode tmp = index.search(key);
	if (index.key(key, tmp))
	{
		int i = tmp.searchKey(key);
		int vpos = tmp.value[i].pos;
		int length = tmp.value[i].length;
		int valuePos = data.modify(vpos, length, value);
		tmp.value[i] = dataToken(valuePos, value.size() + 1);
		index.writeBPnode(tmp);
		if (cache.ifHasKey(key))
		{
			cache.deleteRecord(key);
			cache.addRecord(key, value);
		}
		return true;
	}
	else
	{
		return false;
	}
}

string database::fetch(const int& key)
{
	if (index.isEmpty()) return "";
	if (cache.ifHasKey(key))
	{
		string result = cache.getValue(key);
		cache.deleteRecord(key);
		cache.addRecord(key, result);
		return result;
	}
	BPnode tmp = index.search(key);
	if (index.key(key, tmp))
	{
		int i = tmp.searchKey(key);
		int vpos = tmp.value[i].pos;
		int length = tmp.value[i].length;
		string result = data.valueData(vpos, length);
		cache.addRecord(key, result);
		return result;
	}
	else
	{
		return "";
	}
}

bool database::fetchtest(const int& key, string &value)
{
	return (value == fetch(key));
}

inline string database::fetchNoCache(const int & key)
{
	if (index.isEmpty()) return "";
	BPnode tmp = index.search(key);
	if (index.key(key, tmp))
	{
		int i = tmp.searchKey(key);
		int vpos = tmp.value[i].pos;
		int length = tmp.value[i].length;
		string result = data.valueData(vpos, length);
		cache.addRecord(key, result);
		return result;
	}
	else
	{
		return "";
	}
}

inline vector<string> database::fetchRange(const int & start, const int & end)
{
	vector<string> result;
	for (int i = start; i < end; i++) {
		string query = fetch(i);
		if (query != "") result.push_back(query);
	}
	return result;
}

bool database::recovery(const int& key)
{
	if (index.isEmpty())
	{
		return false;
	}
	BPnode tmp = index.search(key);
	if (index.key(key, tmp))
	{
		return false;
	}
	if (tmp.HasKey(key))
	{
		index.recovery(key, tmp);
		return true;
	}
	return false;
}
#endif