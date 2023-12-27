#include<iostream>
using namespace std;
class link {
public:
	int number;
	link* next;
	link* ahead;
};
void read(int& n, int& begin_pos,int &m,int &k) {
	cout << "��������Ϸ������(<10000��)";
	cin >> n;
	while (n > 10000 || n < 0) {
		cout << "�����������ƣ�����������";
		cin >> n;
	}
	cout << "��������Ϸ��ʼ��λ��";
	cin >> begin_pos;
	while (begin_pos > n||begin_pos<0) {
		cout << "�������������������Ϸ��ʼ��λ��";
		cin >> begin_pos;
	}
	cout << "��������������";
	cin >> m;
	while (m > n||m<0) {
		cout << "�������������������Ϸ��ʼ��λ��";
		cin >> m;
	}
	cout << "������ʣ�������������";
	cin >> k;
	while (k > n||k<0) {
		cout << "�������������������Ϸ��ʼ��λ��";
		cin >> k;
	}
}
void initialize(link Link[],int n) {
	Link[0].number = 1;
	Link[0].ahead = &Link[n - 1];
	Link[0].next = &Link[1];
	for (int i = 1; i < n - 1; i++) {
		Link[i].number = i + 1;
		Link[i].ahead = &Link[i - 1];
		Link[i].next = &Link[i + 1];
	}
	Link[n - 1].number = n;
	Link[n - 1].next = &Link[0];
	Link[n - 1].ahead = &Link[n - 2];
}
void dead(link Link[],int n,int k,int begin_pos,int m) {
	link* pos;
	pos = &Link[begin_pos - 1];
	int isk = n - k;
	while (isk--) {
		int ism = m;
		while (--ism) {
			pos = pos->next;
		}
		cout << "��" << n - isk - k << "�������߱��Ϊ" << pos->number << endl;
		pos->next->ahead = pos->ahead;
		pos->ahead->next = pos->next;
		pos = pos->next;
	}
}
void output_live(link Link[],int k) {
	cout << "���������Ϊ��" << endl;
	link* ipos;
	ipos = &Link[0];
	for (int i = 1; i <= k; i++) {
		cout << ipos->number << ' ';
		ipos = ipos->next;
	}
	cout << endl;
}
int main() {
	int n, begin_pos,m, k;
	read(n, begin_pos, m, k);
	link* Link;
	Link = new link[n];
	initialize(Link, n);
	dead(Link, n, k, begin_pos, m);
	output_live(Link, k);
	delete[]Link;
	return 0;
}