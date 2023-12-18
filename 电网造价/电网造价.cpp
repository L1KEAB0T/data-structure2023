#include <iostream>

const int MAX = 26; // ���С����

// ����ߵĽṹ��
template <typename T>
struct Edge {
    T start;
    T end;
    int cost;
};

// ���岢�鼯
template <typename T>
struct DisjointSet {
    T parent[MAX];
    int rank[MAX];
};

// ��ʼ�����鼯
template <typename T>
void makeSet(DisjointSet<T>& ds, int n) {
    for (int i = 0; i < n; i++) {
        ds.parent[i] = i;
        ds.rank[i] = 0;
    }
}

// ���Ҹ��ڵ�
template <typename T>
T find(DisjointSet<T>& ds, T i) {
    if (i != ds.parent[i])
        ds.parent[i] = find(ds, ds.parent[i]);
    return ds.parent[i];
}

// �ϲ���������
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

// ð�������
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

// Kruskal�㷨������С������
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

    std::cout << "��С������:" << std::endl;
    for (int j = 0; j < resultSize; j++) {
        std::cout << result[j].start << " - " << result[j].end << " : " << result[j].cost << std::endl;
    }
}

int main() {
    int n, e;
    std::cout << "������С������n��: ";
    std::cin >> n;

    e = 0;
    const int maxEdges = n * (n - 1) / 2;
    Edge<char> edges[MAX];

    std::cout << "������С��֮��ĵ�������: ";
    int edgeCount;
    std::cin >> edgeCount;

    std::cout << "����������ߵ���㡢�յ����ۣ��ÿո�ָ���:" << std::endl;
    for (int i = 0; i < edgeCount; i++) {
        std::cin >> edges[i].start >> edges[i].end >> edges[i].cost;
    }

    sortEdges(edges, edgeCount);
    kruskal(edges, n, e);

    return 0;
}
