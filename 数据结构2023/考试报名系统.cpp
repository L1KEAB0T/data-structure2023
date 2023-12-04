#include<iostream>
#include<iomanip>
using namespace std;
static int n;
class TestSystem {
public:
	int age;
	int num;
	string name;
	string sex;
	string type;
	TestSystem* next;
};
class list {
public:
	int size;
	TestSystem* head;
	static void outputall(list List);
	static void outputone(TestSystem* npos);
	static TestSystem* find(list List, int pnum);
	static void insert(list& List, TestSystem student[]);
	static void del(list& List, TestSystem student[]);
	static void change(list& List, TestSystem student[]);
};
void list::outputall(list List) {
	TestSystem* npos;
	int i;
	npos = List.head;
	cout << "考号    姓名    性别    年龄    报考类型" << endl;
	for (i = 0; i < List.size; i++) {
		cout << setiosflags(ios::left);
		cout << setw(8) << npos->num;
		cout << setw(8) << npos->name;
		cout << setw(8) << npos->sex;
		cout << setw(8) << npos->age;
		cout << npos->type << endl;
		npos = npos->next;
	}
}
void list::outputone(TestSystem* npos) {
	cout << setiosflags(ios::left);
	cout << setw(8) << npos->next->num;
	cout << setw(8) << npos->next->name;
	cout << setw(8) << npos->next->sex;
	cout << setw(8) << npos->next->age;
	cout << setw(8) << npos->next->type << endl;
}
TestSystem* list::find(list List,int pnum) {
	TestSystem* npos;
	int i;
	npos = List.head;
	i = 0;
	while (npos->next->num != pnum && i++ <= List.size)
		npos = npos->next;
	if (npos->next->num != pnum) {
		cout << "输入的考号不存在" << endl;
		return 0;
	}
	return npos;
}
void list::insert(list& List,TestSystem student[]) {
	int pos, i;
	TestSystem* npos;
	cout << "请输入你要插入考生的位置";
	cin >> pos;
	while (pos > List.size + 1) {
		cout << "位置越界，请重新输入" << endl;
		cin >> pos;
	}
	List.size++;
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别!" << endl;
	cin >> student[n].num;
	cin >> student[n].name;
	cin >> student[n].sex;
	cin >> student[n].age;
	cin >> student[n].type;
	npos = List.head;
	if (pos == 1) {
		student[n].next = List.head;
		List.head = &student[n];
	}
	else {
		for (i = 1; i < pos - 1; i++)
			npos = npos->next;
		student[n].next = npos->next;
		npos->next = &student[n];
	}
	n++;
	list::outputall(List);
}
void list::del(list& List, TestSystem student[]) {
	TestSystem* npos;
	int pnum;
	List.size--;
	cout << "请输入你要删除考生的考号";
	cin >> pnum;
	if (pnum == List.head->num) {
		cout << "你删除的考生信息是：";
		cout << setiosflags(ios::left);
		cout << setw(8) << List.head->num;
		cout << setw(8) << List.head->name;
		cout << setw(8) << List.head->sex;
		cout << setw(8) << List.head->age;
		cout << setw(8) << List.head->type << endl;
		List.head = List.head->next;
		list::outputall(List);
	}
	else {
		npos = list::find(List, pnum);
		if (npos != 0) {
			cout << "你删除的考生信息是：";
			list::outputone(npos);
			npos->next = npos->next->next;
			npos = npos->next;
			delete npos;
			list::outputall(List);
		}
	}
}
void list::change(list& List, TestSystem student[]) {
	TestSystem* npos;
	int pnum;
	cout << "请输入你要查找考生的考号";
	cin >> pnum;
	npos = list::find(List, pnum);
	if (npos != 0) {
		cout << "请输入修改后的考生信息：";
		cin >> npos->next->num;
		cin >> npos->next->name;
		cin >> npos->next->sex;
		cin >> npos->next->age;
		cin >> npos->next->type;
		cout << "修改后的考生信息为：" << endl;
		list::outputone(npos);
	}
}
int main() {
	int i;
	int choice,pos=0,pnum=0;
	TestSystem* npos;
	TestSystem student[10000];
	list List{};
	cout << "首先请建立考生信息系统"<<endl;
	cout << "请输入考试人数：";
	cin >> n;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
	for (i = 1; i <= n; i++) {
		cin >> student[i - 1].num;
		cin >> student[i - 1].name;
		cin >> student[i - 1].sex;
		cin >> student[i - 1].age;
		cin >> student[i - 1].type;
		student[i - 1].next = &student[i];
	}
	List.size = n;
	List.head = &student[0];
	list::outputall(List);
	cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
	cout << "请选择您要进行的操作";
	cin >> choice;
	while (choice != 0) {
		switch (choice) {
			case(1): {
				list::insert(List, student);
				break;
			}
			case(2): {
				list::del(List, student);
				break;
			}
			case(3): {
				cout << "请输入你要查找考生的考号";
				cin >> pnum;
				npos=list::find(List, pnum);
				if (npos != 0) {
					cout << "你查找的考生信息是：";
					list::outputone(npos);
				}
				break;
			}
			case(4): {
				list::change(List, student);
				break;
			}
			case(5): {
				cout << "当前系统中所有的考生信息为：" << endl;
				list::outputall(List);
				break;
			}
			default:
				break;
		}
		cout << "请选择您要进行的操作";
		cin >> choice;
	}
	return 0;
}