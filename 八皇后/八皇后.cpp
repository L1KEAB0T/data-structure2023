#include <iostream>
using namespace std;

class EightQueens {
private:
    int n;  // �ʺ����
    int res;  // �˻ʺ�Ϸ�������
    int* col;  // ��ռ��������
    int* dg;  // �Խ��ߣ�Ʋ��ռ��������
    int* udg;  // �Խ��ߣ��ࣩռ��������
    int* path; // ���ڼ�¼���̰ڷ����

public:
    EightQueens(int num) : n(num), res(0) {
        col = new int[n];
        dg = new int[2 * n];
        udg = new int[2 * n];
        path = new int[n];
        memset(col, 0, sizeof(int) * n);
        memset(dg, 0, sizeof(int) * 2 * n);
        memset(udg, 0, sizeof(int) * 2 * n);
    }

    ~EightQueens() {
        delete[] col;
        delete[] dg;
        delete[] udg;
        delete[] path;
    }

    void solve() {
        dfs(0);
    }

    void printResult() {
        cout << "Total: " << res << endl;
    }

private:
    void dfs(int u) {
        if (u == n) {
            res++;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (path[i] == j) cout << "Q";
                    else cout << ".";
                }
                cout << endl;
            }
            cout << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!col[i] && !dg[u - i + n] && !udg[u + i]) {
                col[i] = dg[u - i + n] = udg[u + i] = 1;  // ���ռ��
                path[u] = i;
                dfs(u + 1);
                col[i] = dg[u - i + n] = udg[u + i] = 0;  // ȡ�����
            }
        }
    }
};

int main() {
    int n;
    cout << "������ʺ��������";
    cin >> n;

    EightQueens eq(n);
    eq.solve();
    eq.printResult();

    return 0;
}