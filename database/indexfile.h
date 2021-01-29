#ifndef INDEXFILE_H
#define INDEXFILE_H
#include "BPnode.h"
#include "space.h"
#include <memory>

class wrongIndexFile {};
class keyExist {};
class keyDExist {};
class indexfile
{
private:
	fstream f;
	vector<BPnode> reserve;
	int rootPos = -1;
	bool empty = true;
	vector<BPnode> path;
public:
	indexfile() {};
	void openIndexfile(string path, file method);
	void closeIndexfile();
	void insert(int key, int vpos, int length, int cpos = 0, BPnode &obj = BPnode());
	void deleteIdx(int key, BPnode &obj);
	void overFlow(BPnode &obj);
	BPnode search(int key);        // get leaf node containing key£¨whether key is existed or not£©
	BPnode searchInsert(int key);  // add parent nodes to path while searching
	int writeBPnode(BPnode &obj);  // write BPnode to indexfile
	BPnode getBPMessage(int pos);  // get BPnode from indexfile
	void freshenIndexFile();
	void writeRootPos();           // write root BPnode to indexfile
	bool isEmpty();
	bool key(int key, BPnode &tmp);// query key existence
	void pathClear();              // clear path
	void recovery(int key, BPnode &obj);// rollback a delete key
};
#endif
