#include<iostream>
#include<cstring>
#define MAXSIZE 100						//���hash��ַ
using namespace std;

class dictionary						//�绰����
{
private:
	typedef struct element				//�绰��������Ԫ��
	{
		char name[18] = { 0 };
		char phone[12] = { 0 };
		char address[18] = { 0 };
		element* next = NULL;
	} element;
	typedef struct head					//ͷ��㶨��
	{
		int depth = 0;
		element *next = NULL;
	}head;
	head elem[MAXSIZE];					//ͷ�������

public:
	char* name_reverse(char name[])		//��������ĸ���������У����ڹ�ϣ�㷨��
	{
		static char temp[18];
		int i;
		int top = strnlen_s(name, 18);
		for (i = 0; top > 0; top--, i++)
			temp[i] = name[top - 1];
		temp[i] = '\0';
		return temp;
	}
	//name_reverse()�Ѳ���

	int hash_name(char name[])			//hash_name������Ѱַ�����������������λ�á�ȡֵ��0-100�����������쳣ֵΪ-1
	{
		int n = 0;
		element* ptr = NULL;
		char temp_name[18] = { 0 };
		strcpy_s(temp_name, 18, name_reverse(name));//���Ƶ���ʱ�洢�ռ�temp_name��

		int size_of_name = strnlen_s(temp_name, 18);//���ַ�������

		for (int i = 0; i < size_of_name; i++)		//��д��ĸȫ��ת��ΪСд��ĸ
			temp_name[i] = (temp_name[i] >= 65 && temp_name[i] <= 90) ? temp_name[i] + 32 : temp_name[i];

		if (size_of_name >= 7)						//��ĸ���ڵ���7���Ĺ�ϣ�㷨
			for (int i = 0; i < 7; i += 2)
				n += (int)(temp_name[i] - 'a');
		else if (size_of_name < 7 && size_of_name>3)//��ĸ������3������7��
			for (int i = 0; i < 3; i += 2)
				n += 2 * (int)(temp_name[i] - 'a');
		else
		{
			cout << "����̫����" << endl;			//��ĸ����4������
			n = 0;
		}
		return n;
	}

	element* is_name_exist(char name[])	//̽�������Ƿ���ڣ������򷵻ص�ַ���������򷵻ؿ�
	{
		int n = hash_name(name);
		element *ptr = elem[n].next;
		char temp_name[18] = { 0 };
		strcpy_s(temp_name, 18, name);	//���Ƶ���ʱ�洢�ռ�temp_name��
		while (ptr != NULL)				//����ͷ�������Ԫ�أ��������ң����������һ���ڵ�
		{
			if (!_stricmp(ptr->name, temp_name))
				return ptr;
			ptr = ptr->next;
		}
		return NULL;
	}

	void add_elem(char name[])			//�ڸ�ͷ���֮�����Ԫ��
	{
		int n = hash_name(name);		//�ҵ������ͷ���
		element *ptr = elem[n].next;
		element *ptr1 = NULL;
		ptr1 = new element;				//�½�Ԫ��
		elem[n].next = ptr1;
		ptr1->next = ptr;

		cout << "name:";
		cin >> ptr1->name;
		cout << "phone number:";
		cin >> ptr1->phone;
		cout << "address:";
		cin >> ptr1->address;
		elem[n].depth++;
		cout << "����ɹ������س�����������" << endl;
		cin.get();
	}

	void change_phone(char name[])		//�޸ĵ绰����
	{
		int n = hash_name(name);
		element *ptr = elem[n].next;
		cout << "�����µĵ绰���룺";
		cin >> ptr->phone;
		cout << "�޸ĳɹ���" << endl;
	}

	void delete_elem(char name[])		//�ڸõ�ַɾ��Ԫ��
	{
		if (is_name_exist(name))
		{
			element *ptr = is_name_exist(name);//ָ���Ԫ��
			element *ptr1 = elem[hash_name(ptr->name)].next;//ָ��ù�ϣֵ�ĵ�һ��Ԫ��

			if (ptr - ptr1 == 0)		//ͷ�ڵ��µ�һ��Ԫ�ؾ��������Ԫ��
			{
				ptr1 = NULL;
				delete ptr;
				ptr = NULL;
				elem[hash_name(name)].next = NULL;
			}
			else						//ͷ���֮��ǵ�һ��Ԫ��������Ԫ��
			{
				while (_stricmp((ptr1->next)->name, name))
					ptr1 = ptr1->next;
				ptr1->next = ptr->next;
				delete ptr;
			}
			elem[hash_name(name)].depth--;
			cout << "ɾ���ɹ����밴�س�������" << endl;
		}
		else
			cout << "���ֲ����ڣ��޷�ɾ��" << endl;
		cin.get();
	}

	bool search_phone(char phone[])		//�����绰���룬��֧��ģ������������������ʾ����
	{
		element* ptr = NULL;
		char temp_phone[12] = { 0 };
		strcpy_s(temp_phone, 12, phone);

		int if_out = 0;
		for (int i = 0; i<11; i++)
			if (temp_phone[i] == '\0')	//��֧��ģ����������������11λ�绰����
			{
				cout << "������11λ�绰����" << endl;
				return false;
			}
		for (int i = 0; i < MAXSIZE; i++)//����ȫ������ͬ�ĵ绰����
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
			cout << "\n��" << if_out << "����";
		else
			cout << "\nδ�ҵ���";
		cout << "�밴�س�����������" << endl;
		cin.get();
		return true;
	}

	void show()								//�������ȫ���������Ϣ
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
		cout << "\n��" << number << "����¼��" << endl;
		cout << "�밴�س�����������" << endl;
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
		cout << "��ӭʹ�õ绰��" << endl;
		cout << "���������밴1�����ҵ绰�밴2,����绰���밴3���˳��밴0��\t";
		cin >> i;

		switch (i)						//����ѡ��
		{
		case 1:
			cout << "\n������������";
			cin >> temp_name;
			if (dictionary0.is_name_exist(temp_name))
			{
				cout << "name:\t\t" << dictionary0.is_name_exist(temp_name)->name << endl;
				cout << "phone:\t\t" << dictionary0.is_name_exist(temp_name)->phone << endl;
				cout << "address:\t" << dictionary0.is_name_exist(temp_name)->address << endl;
				cout << endl;

				char c_or_d = '\0';
				cout << "��Ҫ�޸Ļ�ɾ����¼��\n�޸ġ���c\tɾ������d\t���޸ġ��������������\t";
				cin >> c_or_d;

				switch (c_or_d)			//�޸Ļ�ɾ��ѡ��
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
				cout << "δ�ҵ������֡�\n" << endl;
				cout << "��Ҫ�½���y/n\t";
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
			cout << "������绰���룺";
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