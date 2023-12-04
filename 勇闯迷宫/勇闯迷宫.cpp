#include <iostream>
using namespace std;

class MazeSolver {
private:
    char maze[10][10];  // �Թ���ͼ
    int path[10][10];   // ·���������
    int m;              // �Թ���������

public:
    MazeSolver() {
        // ���캯������ʼ���Թ���ͼ��·���������
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                maze[i][j] = '#';
                path[i][j] = 0;
            }
        }
    }

    void readMaze() {
        // ��ȡ�Թ���ͼ�ĺ���ʵ��
        cout << "�������Թ��ߴ磨1-10����";
        cin >> m;

        if (m <= 0 || m > 10) {
            cout << "�Թ��ߴ粻����Ҫ�����������룡" << endl;
            return;
        }

        cout << "�밴�������Թ���ͼ��" << endl;
        cout << "ǽ����'#'��ʾ��ͨ����'0'��ʾ�����Ĭ�����Ͻǣ��յ�Ĭ�����½�" << endl;
        for (int i = 0; i < m; i++) {
            cout << "�������" << i + 1 << "�У�";
            for (int j = 0; j < m; j++) {
                cin >> maze[i][j];
                if (maze[i][j] != '#' && maze[i][j] != '0') {
                    cout << "�Թ���ͼ�����Ƿ��ַ������������룡" << endl;
                    return;
                }
                else if (i == 0 && j == 0) {
                    maze[i][j] = 'S';   // �����Ͻ�����Ϊ���
                }
                else if (i == m - 1 && j == m - 1) {
                    maze[i][j] = 'E';   // �����½�����Ϊ�յ�
                }
            }
        }
    }


    void outputMaze() {
        // ����Թ���ͼ�ĺ���ʵ��
        cout << "Maze Map:" << endl;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool solveMaze(int row, int col) {
        // �Թ����ĺ���ʵ�֣������㷨��
        if(row == m - 1 && col == m - 1) {
            path[row][col] = 1;
            return true;
        }
        if(row < 0 || row >= m || col < 0 || col >= m || maze[row][col] == '#' || path[row][col] == 1) {
            return false;
        }
        path[row][col] = 1;
        if(solveMaze(row - 1, col) || solveMaze(row + 1, col) || solveMaze(row, col - 1) || solveMaze(row, col + 1)) {
            return true;
        }
        path[row][col] = 0;
        return false;
    }

    void outputPath() {
        cout << "Maze Path:" << endl;
        int** pathPoints = new int* [100];  // ��̬���飬���ڴ洢·��������
        for (int i = 0; i < 100; i++) {
            pathPoints[i] = new int[2];
        }
        int k = 0;  // ��¼·��������
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (path[i][j] == 1) {
                    pathPoints[k][0] = i;  // �洢·�����������
                    pathPoints[k][1] = j;  // �洢·�����������
                    k++;  // ����·��������
                }
                cout << path[i][j] << " ";
            }
            cout << endl;
        }
        // ���·�����������е�
        cout << "Path points: ";
        for (int i = 0; i < k; i++) {
            if (i > 0) {
                cout << "->";
            }
            cout << "(" << pathPoints[i][0] << "," << pathPoints[i][1] << ")";
        }
        cout << endl;

        // �ͷŶ�̬�����ڴ�
        for (int i = 0; i < 100; i++) {
            delete[] pathPoints[i];
        }
        delete[] pathPoints;
    }

};

int main() {
    MazeSolver solver;
    solver.readMaze();
    if(solver.solveMaze(0, 0)) {
        solver.outputMaze();
        solver.outputPath();
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}