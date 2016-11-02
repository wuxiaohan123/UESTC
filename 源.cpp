#include<iostream>
#include<cstring>
#define MAXSIZE 100						//最大hash地址
using namespace std;

class dictionary						//电话本类
{
private:
	typedef struct element				//电话本的数据元素
	{
		char name[18] = { 0 };
		char phone[12] = { 0 };
		char address[18] = { 0 };
		element* next = NULL;
	} element;
	typedef struct head					//头结点定义
	{
		int depth = 0;
		element *next = NULL;
	}head;
	head elem[MAXSIZE];					//头结点数组

public:
	char* name_reverse(char name[])		//将姓名字母倒过来排列（用于哈希算法）
	{
		static char temp[18];
		int i;
		int top = strnlen_s(name, 18);
		for (i = 0; top > 0; top--, i++)
			temp[i] = name[top - 1];
		temp[i] = '\0';
		return temp;
	}
	//name_reverse()已测试

	int hash_name(char name[])			//hash_name函数，寻址，输入名字输出插入位置。取值：0-100的正整数，异常值为-1
	{
		int n = 0;
		element* ptr = NULL;
		char temp_name[18] = { 0 };
		strcpy_s(temp_name, 18, name_reverse(name));//复制到临时存储空间temp_name里

		int size_of_name = strnlen_s(temp_name, 18);//求字符串长度

		for (int i = 0; i < size_of_name; i++)		//大写字母全部转化为小写字母
			temp_name[i] = (temp_name[i] >= 65 && temp_name[i] <= 90) ? temp_name[i] + 32 : temp_name[i];

		if (size_of_name >= 7)						//字母大于等于7个的哈希算法
			for (int i = 0; i < 7; i += 2)
				n += (int)(temp_name[i] - 'a');
		else if (size_of_name < 7 && size_of_name>3)//字母数大于3个少于7个
			for (int i = 0; i < 3; i += 2)
				n += 2 * (int)(temp_name[i] - 'a');
		else
		{
			cout << "名字太短了" << endl;			//字母最少4个以上
			n = 0;
		}
		return n;
	}

	element* is_name_exist(char name[])	//探测名字是否存在，存在则返回地址，不存在则返回空
	{
		int n = hash_name(name);
		element *ptr = elem[n].next;
		char temp_name[18] = { 0 };
		strcpy_s(temp_name, 18, name);	//复制到临时存储空间temp_name里
		while (ptr != NULL)				//若该头结点下有元素，则进入查找，否则查找下一个节点
		{
			if (!_stricmp(ptr->name, temp_name))
				return ptr;
			ptr = ptr->next;
		}
		return NULL;
	}

	void add_elem(char name[])			//在该头结点之后插入元素
	{
		int n = hash_name(name);		//找到插入的头结点
		element *ptr = elem[n].next;
		element *ptr1 = NULL;
		ptr1 = new element;				//新建元素
		elem[n].next = ptr1;
		ptr1->next = ptr;

		cout << "name:";
		cin >> ptr1->name;
		cout << "phone number:";
		cin >> ptr1->phone;
		cout << "address:";
		cin >> ptr1->address;
		elem[n].depth++;
		cout << "输入成功。按回车键继续……" << endl;
		cin.get();
	}

	void change_phone(char name[])		//修改电话号码
	{
		int n = hash_name(name);
		element *ptr = elem[n].next;
		cout << "输入新的电话号码：";
		cin >> ptr->phone;
		cout << "修改成功。" << endl;
	}

	void delete_elem(char name[])		//在该地址删除元素
	{
		if (is_name_exist(name))
		{
			element *ptr = is_name_exist(name);//指向该元素
			element *ptr1 = elem[hash_name(ptr->name)].next;//指向该哈希值的第一个元素

			if (ptr - ptr1 == 0)		//头节点下第一个元素就是所查的元素
			{
				ptr1 = NULL;
				delete ptr;
				ptr = NULL;
				elem[hash_name(name)].next = NULL;
			}
			else						//头结点之后非第一个元素是所查元素
			{
				while (_stricmp((ptr1->next)->name, name))
					ptr1 = ptr1->next;
				ptr1->next = ptr->next;
				delete ptr;
			}
			elem[hash_name(name)].depth--;
			cout << "删除成功。请按回车键继续" << endl;
		}
		else
			cout << "名字不存在，无法删除" << endl;
		cin.get();
	}

	bool search_phone(char phone[])		//搜索电话号码，不支持模糊搜索，搜索到则显示名字
	{
		element* ptr = NULL;
		char temp_phone[12] = { 0 };
		strcpy_s(temp_phone, 12, phone);

		int if_out = 0;
		for (int i = 0; i<11; i++)
			if (temp_phone[i] == '\0')	//不支持模糊搜索，必须输入11位电话号码
			{
				cout << "请输入11位电话号码" << endl;
				return false;
			}
		for (int i = 0; i < MAXSIZE; i++)//遍历全表，找相同的电话号码
		{
			ptr = elem[i].next;

			while (ptr != NULL)
			{
				if (!_stricmp(ptr->phone, phone))
				{
					cout << ptr->name << endl;
					if_out++;
				}
				ptr = ptr->next;
			}
		}
		if (if_out)
			cout << "\n共" << if_out << "个。";
		else
			cout << "\n未找到。";
		cout << "请按回车键继续……" << endl;
		cin.get();
		return true;
	}

	void show()								//遍历输出全表的所有信息
	{
		element* ptr = NULL;
		int number = 0;
		for (int i = 0; i < MAXSIZE; i++)
		{
			ptr = elem[i].next;
			if (elem[i].depth)
			{
				while (ptr != NULL)
				{

					cout << "name:\t\t" << ptr->name << endl;
					cout << "phone:\t\t" << ptr->phone << endl;
					cout << "address:\t" << ptr->address << endl;
					cout << endl;
					number++;

					ptr = ptr->next;
				}
			}
		}
		cout << "\n共" << number << "条记录。" << endl;
		cout << "请按回车键继续……" << endl;
	}
};


int main()
{
	dictionary dictionary0;
	int i = 0;
	char temp_name[18] = { 0 };
	char temp_phone[12] = { 0 };
	
	while (1)							
	{
		cout << "欢迎使用电话本" << endl;
		cout << "查找姓名请按1，查找电话请按2,输出电话本请按3，退出请按0：\t";
		cin >> i;

		switch (i)						//输入选项
		{
		case 1:
			cout << "\n请输入姓名：";
			cin >> temp_name;
			if (dictionary0.is_name_exist(temp_name))
			{
				cout << "name:\t\t" << dictionary0.is_name_exist(temp_name)->name << endl;
				cout << "phone:\t\t" << dictionary0.is_name_exist(temp_name)->phone << endl;
				cout << "address:\t" << dictionary0.is_name_exist(temp_name)->address << endl;
				cout << endl;

				char c_or_d = '\0';
				cout << "需要修改或删除记录吗？\n修改——c\t删除——d\t不修改——任意键继续：\t";
				cin >> c_or_d;

				switch (c_or_d)			//修改或删除选项
				{
				case 'c':
					dictionary0.change_phone(temp_name);
					cin.get();
					break;

				case 'd':
					dictionary0.delete_elem(temp_name);
					break;

				default:
					break;
				}
			}
			else
			{
				cout << "未找到该名字。\n" << endl;
				cout << "需要新建吗？y/n\t";
				char y_or_n = 'n';
				cin >> y_or_n;
				switch (y_or_n)
				{
				case 'y':
					dictionary0.add_elem(temp_name);
					break;

				case 'n':
					break;

				default:
					break;
				}
			}
			break;

		case 2:
			cout << "请输入电话号码：";
			cin >> temp_phone;
			dictionary0.search_phone(temp_phone); 
			cin.get();
			break;

		case 3:
			dictionary0.show();
			cin.get();
			break;

		default:
			return 0;
		}
		cin.get();
		system("cls");
	}
	cin.get();
	return 0;
}