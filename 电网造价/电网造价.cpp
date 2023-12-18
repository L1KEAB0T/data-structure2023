#include <iostream>

const int MAX = 26; // 最大小区数

// 定义边的结构体
template <typename T>
struct Edge {
    T start;
    T end;
    int cost;
};

// 定义并查集
template <typename T>
struct DisjointSet {
    T parent[MAX];
    int rank[MAX];
};

// 初始化并查集
template <typename T>
void makeSet(DisjointSet<T>& ds, int n) {
    for (int i = 0; i < n; i++) {
        ds.parent[i] = i;
        ds.rank[i] = 0;
    }
}

// 查找根节点
template <typename T>
T find(DisjointSet<T>& ds, T i) {
    if (i != ds.parent[i])
        ds.parent[i] = find(ds, ds.parent[i]);
    return ds.parent[i];
}

// 合并两个集合
template <typename T>
void Union(DisjointSet<T>& ds, T x, T y) {
    T rootX = find(ds, x);
    T rootY = find(ds, y);

    if (ds.rank[rootX] < ds.rank[rootY])
        ds.parent[rootX] = rootY;
    else if (ds.rank[rootX] > ds.rank[rootY])
        ds.parent[rootY] = rootX;
    else {
        ds.parent[rootY] = rootX;
        ds.rank[rootX]++;
    }
}

// 冒泡排序边
template <typename T>
void sortEdges(Edge<T> edges[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].cost > edges[j + 1].cost) {
                Edge<T> temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal算法构造最小生成树
template <typename T>
void kruskal(Edge<T> edges[], int n, int e) {
    DisjointSet<T> ds;
    makeSet(ds, n);

    const int resultSize = n - 1;
    Edge<T> result[MAX];
    int mstCost = 0;
    int i = 0;

    while (i < resultSize && e < n * (n - 1) / 2) {
        Edge<T> nextEdge = edges[e++];
        T x = find(ds, nextEdge.start);
        T y = find(ds, nextEdge.end);

        if (x != y) {
            result[i++] = nextEdge;
            Union(ds, x, y);
            mstCost += nextEdge.cost;
        }
    }

    std::cout << "最小生成树:" << std::endl;
    for (int j = 0; j < resultSize; j++) {
        std::cout << result[j].start << " - " << result[j].end << " : " << result[j].cost << std::endl;
    }
}

int main() {
    int n, e;
    std::cout << "请输入小区数（n）: ";
    std::cin >> n;

    e = 0;
    const int maxEdges = n * (n - 1) / 2;
    Edge<char> edges[MAX];

    std::cout << "请输入小区之间的电网边数: ";
    int edgeCount;
    std::cin >> edgeCount;

    std::cout << "请输入电网边的起点、终点和造价（用空格分隔）:" << std::endl;
    for (int i = 0; i < edgeCount; i++) {
        std::cin >> edges[i].start >> edges[i].end >> edges[i].cost;
    }

    sortEdges(edges, edgeCount);
    kruskal(edges, n, e);

    return 0;
}
