#include <iostream>
using namespace std;

class EightQueens {
private:
    int n;  // 皇后个数
    int res;  // 八皇后合法解数量
    int* col;  // 列占用情况标记
    int* dg;  // 对角线（撇）占用情况标记
    int* udg;  // 对角线（捺）占用情况标记
    int* path; // 用于记录棋盘摆放情况

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
                col[i] = dg[u - i + n] = udg[u + i] = 1;  // 标记占用
                path[u] = i;
                dfs(u + 1);
                col[i] = dg[u - i + n] = udg[u + i] = 0;  // 取消标记
            }
        }
    }
};

int main() {
    int n;
    cout << "请输入皇后的数量：";
    cin >> n;

    EightQueens eq(n);
    eq.solve();
    eq.printResult();

    return 0;
}