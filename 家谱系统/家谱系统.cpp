#include<iostream>
using namespace std;
class family_tree {
private:
	family_tree* parents=nullptr;
	family_tree* kids = nullptr;
	family_tree* nextSibling=nullptr;
	string name;
public:
	void assignname(string str) { this->name = str; }
	void assignparents(family_tree* par){ this->parents = par; }
	void assignkids(family_tree* kid) {	this->kids = kid;	}
	void assignnextSibling(family_tree* next) { nextSibling = next; }
	const string& getName() const { return name; }
	family_tree* getKids() { return kids; }
	family_tree* getParents() { return parents; }
	family_tree* getNextSibing() { return nextSibling; }
	~family_tree() {
		family_tree* currentKid = kids;
		while (currentKid != nullptr) {
			family_tree* nextKid = currentKid->getNextSibing();
			delete currentKid;
			currentKid = nextKid;
		}
	}
};
void initialize() {
	cout << "**              家谱系统                **"<<endl;
	cout << "==========================================" << endl;
	cout << "**          选择要执行的操作            **" << endl;
	cout << "**             A=完善家谱               **" << endl;
	cout << "**           B=添加家庭成员             **" << endl;
	cout << "**           C=解散家庭成员             **" << endl;
	cout << "**          D=更改家庭成员姓名          **" << endl;
	cout << "**             E=退出程序               **" << endl;
	cout << "==========================================" << endl;
}
void ancestor(family_tree* first) {
	string name;
	cout << "首先建立一个家谱！\n";
	cout << "请输入该家谱的祖先\n";
	cin >> name;
	family_tree* treenode;
	treenode = new family_tree;
	treenode->assignname(name);
	first->assignkids(treenode);
	treenode->assignparents(first);
}
family_tree* findNote(string str, family_tree* GNote) {
	if (GNote == nullptr)
		return nullptr;
	if (GNote->getName() == str)
		return GNote;
	// 如果存在子节点，则递归查找子节点
	if (GNote->getKids() != nullptr) {
		family_tree* result = findNote(str, GNote->getKids());
		// 找到目标节点就直接返回
		if (result != nullptr)
			return result;
	}
	// 如果存在兄弟节点，则递归查找兄弟节点
	else if (GNote->getNextSibing() != nullptr) {
		return findNote(str, GNote->getNextSibing());
	}
	// 不存在子节点和兄弟节点，返回nullptr
	return nullptr;
}
char choice() {
	cout << "请选择要执行的操作" << endl;
	char ch;
	cin >> ch;
	while (ch < 'A' || ch>'E') {
		cout << "ch输入错误" << endl;
		cin >> ch;
	}
	return ch;
}
void findKids(family_tree* Note) {
	if (Note->getKids() == nullptr) {
		cout << Note->getName() << "无子女" << endl;
	}
	else {
		family_tree* GNote = Note->getKids();
		cout << Note->getName() << "的子女为";
		while (GNote != nullptr) {
			cout << GNote->getName() << ' ';
			GNote = GNote->getNextSibing();
		}
		cout << endl;
	}
}
void read_kids(string son_name[],int num) {
	cout << "请输入子女的名字"<<endl;
	//输入规则:每个人换一次行
	for (int i = 0; i < num; i++) {
		int j = 0;
		char c = cin.get();
		while (c != '\n') {
			son_name[i] += c;
			c = cin.get();
		}
	}
}
void insert(family_tree* first) {
	string str;
	cout << "请输入要建立家庭的成员" << endl;
	cin >> str;
	family_tree* GNote;
	GNote = findNote(str, first);
	if (GNote == nullptr)
		cout << "并未找到该名成员" << endl;
	else {
		cout << "请输入" << str << "子女的个数";
		int num;
		cin >> num;
		while (num < 0 || num>9) {
			cout << "输入错误，请重新输入" << endl;
			cin >> num;
		}
		cin.clear();
		cin.ignore();
		family_tree* insert_tree;
		insert_tree = new family_tree[num];
		string* son_name;
		son_name = new string[num];
		read_kids(son_name, num);
		for (int i = 0; i < num; i++) {
			insert_tree[i].assignparents(GNote);
			if (i != 0) {
				insert_tree[i - 1].assignnextSibling(&insert_tree[i]);
			}
			insert_tree[i].assignname(son_name[i]);
		}
		GNote->assignkids(&insert_tree[0]);
		findKids(GNote);
		delete[] son_name;
	}
}
void insertKids(family_tree* first) {
	string str;
	cout << "请输入要增加子女的成员" << endl;
	cin >> str;
	family_tree* GNote;
	family_tree* Note;
	Note = findNote(str, first);
	GNote = Note;
	if (GNote == nullptr)
		cout << "并未找到该名成员" << endl;
	else {
		cout << "请输入要添加的成员姓名" << endl;
		string son_name;
		cin >> son_name;
		family_tree* newtree;
		newtree = new family_tree;
		newtree->assignname(son_name);
		newtree->assignparents(GNote);
		if (GNote->getKids() == nullptr) 
			GNote->assignkids(newtree);
		else {
			GNote = GNote->getKids();
			while (GNote->getNextSibing() != nullptr) {
				GNote = GNote->getNextSibing();
			}
			GNote->assignnextSibling(newtree);
		}
		findKids(Note);
	}
}
/*void remove_kids(family_tree* kids) {
	if (kids->getKids() != nullptr)
		remove_kids(kids->getKids());
	if (kids->getNextSibing() != nullptr)
		remove_siblings(kids->getNextSibing());
	delete[] kids;
}
void remove_siblings(family_tree* sibling) {
	if (sibling->getNextSibing() != nullptr)
		remove_siblings(sibling->getNextSibing());
	if (sibling->getKids() != nullptr)
		remove_kids(sibling->getKids());
	delete[] sibling;
}*/
void removeFromParents(family_tree* node) {
	family_tree* parent = node->getParents();
	if (parent != nullptr) {
		family_tree* kids = parent->getKids();
		if (kids == node) {
			parent->assignkids(node->getNextSibing());
		}
		else {
			family_tree* sibling = kids;
			while (sibling != nullptr && sibling->getNextSibing() != node) {
				sibling = sibling->getNextSibing();
			}
			if (sibling != nullptr) {
				sibling->assignnextSibling(node->getNextSibing());
			}
		}
	}
	//delete node;
}
void deletefam(family_tree* first) {
	string str;
	family_tree* Note;
	cout << "请输入你想要删除的家庭的家长" << endl;
	cin >> str;
	Note = findNote(str, first);
	if (Note == nullptr) {
		cout << "未找到该成员" << endl;
		return;
	}
	else {
		/*if (Note->getKids() != nullptr) {
			remove_kids(Note->getKids());
			if (Note->getKids()->getNextSibing() != nullptr)
				remove_siblings(Note->getKids()->getNextSibing());
		}*/
		removeFromParents(Note);
		cout << str << "及其所有子孙已被删除" << endl;
		findKids(Note->getParents());
	}
}
void changeName(family_tree* first) {
	string str;
	family_tree* Note;
	cout << "请输入你想要改名的成员" << endl;
	cin >> str;
	Note = findNote(str, first);
	if (Note == nullptr) {
		cout << "未找到该成员" << endl;
		return;
	}
	else {
		cout << "请输入新的名字" << endl;
		cin >> str;
		Note->assignname(str);
	}
}
int main() {
	family_tree first;
	initialize();
	ancestor(&first);
	while (1) {
		switch (choice()) {
			case 'A': {
				insert(&first);
				cout << endl;
				break;
			}
			case 'B': {
				insertKids(&first);
				cout << endl;
				break;
			}
			case 'C': {
				deletefam(&first);
				cout << endl;
				break;
			}
			case 'D': {
				changeName(&first);
				cout << endl;
				break;
			}
			case 'E': {
				return 0; 
			}
		}
	}
}