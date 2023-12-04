#include <iostream>
using namespace std;

class MazeSolver {
private:
    char maze[10][10];  // 迷宫地图
    int path[10][10];   // 路径标记数组
    int m;              // 迷宫的行列数

public:
    MazeSolver() {
        // 构造函数，初始化迷宫地图和路径标记数组
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                maze[i][j] = '#';
                path[i][j] = 0;
            }
        }
    }

    void readMaze() {
        // 读取迷宫地图的函数实现
        cout << "请输入迷宫尺寸（1-10）：";
        cin >> m;

        if (m <= 0 || m > 10) {
            cout << "迷宫尺寸不符合要求，请重新输入！" << endl;
            return;
        }

        cout << "请按行输入迷宫地图：" << endl;
        cout << "墙壁用'#'表示，通道用'0'表示，起点默认左上角，终点默认右下角" << endl;
        for (int i = 0; i < m; i++) {
            cout << "请输入第" << i + 1 << "行：";
            for (int j = 0; j < m; j++) {
                cin >> maze[i][j];
                if (maze[i][j] != '#' && maze[i][j] != '0') {
                    cout << "迷宫地图包含非法字符，请重新输入！" << endl;
                    return;
                }
                else if (i == 0 && j == 0) {
                    maze[i][j] = 'S';   // 将左上角设置为起点
                }
                else if (i == m - 1 && j == m - 1) {
                    maze[i][j] = 'E';   // 将右下角设置为终点
                }
            }
        }
    }


    void outputMaze() {
        // 输出迷宫地图的函数实现
        cout << "Maze Map:" << endl;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool solveMaze(int row, int col) {
        // 迷宫求解的函数实现（回溯算法）
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
        int** pathPoints = new int* [100];  // 动态数组，用于存储路径点坐标
        for (int i = 0; i < 100; i++) {
            pathPoints[i] = new int[2];
        }
        int k = 0;  // 记录路径点数量
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (path[i][j] == 1) {
                    pathPoints[k][0] = i;  // 存储路径点的行坐标
                    pathPoints[k][1] = j;  // 存储路径点的列坐标
                    k++;  // 增加路径点数量
                }
                cout << path[i][j] << " ";
            }
            cout << endl;
        }
        // 输出路径经过的所有点
        cout << "Path points: ";
        for (int i = 0; i < k; i++) {
            if (i > 0) {
                cout << "->";
            }
            cout << "(" << pathPoints[i][0] << "," << pathPoints[i][1] << ")";
        }
        cout << endl;

        // 释放动态数组内存
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