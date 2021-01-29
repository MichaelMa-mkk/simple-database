#ifndef BPNODE_H
#define BPNODE_H

#include<iostream>
#include<vector>
#include<fstream>
#include<set>
#include"space.h"

#define NODE_MIN  9
#define NODE_MAX  16 // node size
#define INDEX_MAX ( NODE_MAX * 4 + 3) * 4 + 1 + NODE_MAX

#define EXIST 1
#define DELETE 2

/*B+ tree node*/

enum file { READ_ONLY, CREATE, READ_AND_WRITE };  // open file methods
enum state { INNER_NODE, LEAF };  // the state of a node
using namespace std;


class BPnode
{
protected:
	int posInFile = -1;
	int num = 0;
	int isLeaf = 1;
public:
	vector<int> keys;            // key sets
	vector<dataToken> value;     // value sets
	vector<int> children;        // pos of children
	vector<char> deleted = vector<char>(NODE_MAX, 'y');  // delete tag
	BPnode() {};
	int getPosInFile();         // get offset in file
	void setPosInFile(int pos); // set offset of file
	bool HasKey(int key);       // exist key£¨whether deleted£©
	bool isOverFlow();
	int searchKey(int key);
	void insert(int key, int vpos, int length, int cpos = 0);  // insert a pair
	void remove(int key);       // delete a pair
	int getState();             // leaf or not?
	void setState(int s);
	void setNum(int n);         // set key num
	int getNum();               // get key num
	void deleteKey(int key);    // delete a pair
	void cancelDelete(int key, int vpos, int length);   // rollback a delete operation
};
#endif

