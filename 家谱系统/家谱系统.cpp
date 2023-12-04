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
	cout << "**              ����ϵͳ                **"<<endl;
	cout << "==========================================" << endl;
	cout << "**          ѡ��Ҫִ�еĲ���            **" << endl;
	cout << "**             A=���Ƽ���               **" << endl;
	cout << "**           B=��Ӽ�ͥ��Ա             **" << endl;
	cout << "**           C=��ɢ��ͥ��Ա             **" << endl;
	cout << "**          D=���ļ�ͥ��Ա����          **" << endl;
	cout << "**             E=�˳�����               **" << endl;
	cout << "==========================================" << endl;
}
void ancestor(family_tree* first) {
	string name;
	cout << "���Ƚ���һ�����ף�\n";
	cout << "������ü��׵�����\n";
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
	// ��������ӽڵ㣬��ݹ�����ӽڵ�
	if (GNote->getKids() != nullptr) {
		family_tree* result = findNote(str, GNote->getKids());
		// �ҵ�Ŀ��ڵ��ֱ�ӷ���
		if (result != nullptr)
			return result;
	}
	// ��������ֵܽڵ㣬��ݹ�����ֵܽڵ�
	else if (GNote->getNextSibing() != nullptr) {
		return findNote(str, GNote->getNextSibing());
	}
	// �������ӽڵ���ֵܽڵ㣬����nullptr
	return nullptr;
}
char choice() {
	cout << "��ѡ��Ҫִ�еĲ���" << endl;
	char ch;
	cin >> ch;
	while (ch < 'A' || ch>'E') {
		cout << "ch�������" << endl;
		cin >> ch;
	}
	return ch;
}
void findKids(family_tree* Note) {
	if (Note->getKids() == nullptr) {
		cout << Note->getName() << "����Ů" << endl;
	}
	else {
		family_tree* GNote = Note->getKids();
		cout << Note->getName() << "����ŮΪ";
		while (GNote != nullptr) {
			cout << GNote->getName() << ' ';
			GNote = GNote->getNextSibing();
		}
		cout << endl;
	}
}
void read_kids(string son_name[],int num) {
	cout << "��������Ů������"<<endl;
	//�������:ÿ���˻�һ����
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
	cout << "������Ҫ������ͥ�ĳ�Ա" << endl;
	cin >> str;
	family_tree* GNote;
	GNote = findNote(str, first);
	if (GNote == nullptr)
		cout << "��δ�ҵ�������Ա" << endl;
	else {
		cout << "������" << str << "��Ů�ĸ���";
		int num;
		cin >> num;
		while (num < 0 || num>9) {
			cout << "�����������������" << endl;
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
	cout << "������Ҫ������Ů�ĳ�Ա" << endl;
	cin >> str;
	family_tree* GNote;
	family_tree* Note;
	Note = findNote(str, first);
	GNote = Note;
	if (GNote == nullptr)
		cout << "��δ�ҵ�������Ա" << endl;
	else {
		cout << "������Ҫ��ӵĳ�Ա����" << endl;
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
	cout << "����������Ҫɾ���ļ�ͥ�ļҳ�" << endl;
	cin >> str;
	Note = findNote(str, first);
	if (Note == nullptr) {
		cout << "δ�ҵ��ó�Ա" << endl;
		return;
	}
	else {
		/*if (Note->getKids() != nullptr) {
			remove_kids(Note->getKids());
			if (Note->getKids()->getNextSibing() != nullptr)
				remove_siblings(Note->getKids()->getNextSibing());
		}*/
		removeFromParents(Note);
		cout << str << "�������������ѱ�ɾ��" << endl;
		findKids(Note->getParents());
	}
}
void changeName(family_tree* first) {
	string str;
	family_tree* Note;
	cout << "����������Ҫ�����ĳ�Ա" << endl;
	cin >> str;
	Note = findNote(str, first);
	if (Note == nullptr) {
		cout << "δ�ҵ��ó�Ա" << endl;
		return;
	}
	else {
		cout << "�������µ�����" << endl;
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