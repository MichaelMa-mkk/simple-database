#include "database.hpp"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include<regex>

bool isInteger(string &obj)//limit integer to [-100000000,1000000000]
{
	if (obj.size() == 0)
	{
		return false;
	}
	if (obj.size() == 1)
	{
		if (!isdigit(obj[0]))
		{
			return false;
		}
		return true;
	}
	if (obj.size() > 10)
	{
		return false;
	}

	if (!isdigit(obj[0]))
	{
		if (!(obj[0] == '-' || obj[0] == '+'))
		{
			return false;
		}
	}
	if (obj.size() == 10)
	{
		if (obj[0] > '1')
		{
			return false;
		}
	}
	for (int i = 1; i < obj.size(); ++i)
	{
		if (!isdigit(obj[i]))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int databaseChoice;
	int choice;
	database db("");
	while (true)
	{
		cout << "请选择：\n"\
			"1.创建一个数据库；\n"\
			"2.打开一个数据库；\n"\
			"3.退出；" << endl;
		string tmp;
		getline(cin, tmp);
		if (isInteger(tmp))
		{
			databaseChoice = stoi(tmp);
			if (databaseChoice >= 1 && databaseChoice <= 3)
			{
				break;
			}
			else
			{
				cout << "无此选项，请重新输入。" << endl;
			}
		}
		else
		{
			cout << "错误输入，请重新输入。" << endl;
		}
	}

	switch (databaseChoice)
	{
	case 1:
	{
		cout << "请输入新数据库路径或名称：" << endl;
		string name;
		getline(cin, name);
		db.setPath(name);
		db.open(CREATE);
		db.close();
		db.open(READ_AND_WRITE);
		break;
	}
	case 2:
	{
		while (true)
		{
			try
			{
				cout << "请输入数据库路径或名称：" << endl;
				string name;
				getline(cin, name);
				db.setPath(name);
				db.open(READ_AND_WRITE);
				break;
			}
			catch (wrongIndexFile)
			{
				cout << "数据库不存在。" << endl;
			}
			catch (wrongDataFile)
			{
				cout << "数据库不存在。" << endl;
			}
		}
		break;
	}
	case 3:
		exit(0);
		break;
	}
	while (true)
	{
		while (true)
		{
			cout << "请选择：\n"\
				"1.通过键值存储数据；\n"\
				"2.通过键值查询数据；\n"\
				"3.通过范围（左闭右开）查询数据；\n"\
				"4.通过键值修改数据；\n"\
				"5.通过键值删除数据；\n"\
				"6.通过键值恢复被删除数据；\n"\
				"7.退出；" << endl;
			string tmp;
			getline(cin, tmp);
			if (isInteger(tmp))
			{
				choice = stoi(tmp);
				if (databaseChoice >= 1 && databaseChoice <= 3)
				{
					break;
				}
				else
				{
					cout << "无此选项，请重新输入。" << endl;
				}
			}
			else
			{
				cout << "错误输入，请重新输入。" << endl;
			}
		}
		switch (choice)
		{
		case 1:
		{
			int key;
			string tmp;
			string value;
			while (true)
			{
				cout << "请输入键值：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
				}
			}
			cout << "请输入数据：";
			getline(cin, value);
			if (db.store(key, value))
			{
				cout << "存储成功！" << endl;
			}
			else
			{
				cout << "该键值已存在，存储失败。" << endl;
			}
			break;
		}
		case 2:
		{
			int key;
			string tmp;
			string result;
			while (true)
			{
				cout << "请输入键值：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
				}
			}
			result = db.fetch(key);
			if (result != "")
			{
				cout << "查询成功！数据为：" << result << endl;
			}
			else
			{
				cout << "该键值不存在，查询失败。" << endl;
			}
			break;
		}
		case 3:
		{
			int l, r;
			string tmp;
			vector<string> result;
			while (true)
			{
				cout << "请输入范围的左边界：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					l = stoi(tmp);
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
					continue;
				}
				cout << "请输入范围的右边界：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					r = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
				}
			}
			result = db.fetchRange(l, r);
			if (result.size() > 0)
			{
				cout << "查询成功！数据为：" << endl;
				for (string i : result) {
					cout << i << endl;
				}
			}
			else
			{
				cout << "该范围内不存在数据，查询失败。" << endl;
			}
			break;
		}
		case 4:
		{
			int key;
			string tmp;
			string value;
			while (true)
			{
				cout << "请输入键值：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入：" << endl;
				}
			}
			cout << "请输入数据：";
			getline(cin, value);
			if (db.modify(key, value))
			{
				cout << "修改成功！" << endl;
			}
			else
			{
				cout << "该键值不存在，修改失败。" << endl;
			}
			break;
		}
		case 5:
		{
			int key;
			string tmp;
			string result;
			while (true)
			{
				cout << "请输入键值：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
				}
			}
			if (db.remove(key))
			{
				cout << "删除成功！" << endl;
			}
			else
			{
				cout << "该键值不存在，删除失败。" << endl;
			}
			break;
		}
		case 6:
		{
			int key;
			string tmp;
			while (true)
			{
				cout << "请输入键值：";
				getline(cin, tmp);
				if (isInteger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "错误输入，请重新输入。" << endl;
				}
			}
			if (db.recovery(key))
			{
				cout << "恢复成功！" << endl;
			}
			else
			{
				cout << "恢复失败。" << endl;
			}
			break;
		}
		case 7:
			exit(0);
			break;
		}
	}
}