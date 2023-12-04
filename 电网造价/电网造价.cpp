#include <iostream>

const int MAX = 26; // ���С����

// ����ߵĽṹ��
struct Edge {
    char start;
    char end;
    int cost;
};

// ���岢�鼯
struct DisjointSet {
    int parent[MAX];
    int rank[MAX];
};

// ��ʼ�����鼯
void makeSet(DisjointSet& ds, int n) {
    for (int i = 0; i < n; i++) {
        ds.parent[i] = i;
        ds.rank[i] = 0;
    }
}

// ���Ҹ��ڵ�
int find(DisjointSet& ds, int i) {
    if (i != ds.parent[i])
        ds.parent[i] = find(ds, ds.parent[i]);
    return ds.parent[i];
}

// �ϲ���������
void Union(DisjointSet& ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);

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
void sortEdges(Edge edges[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].cost > edges[j + 1].cost) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal�㷨������С������
void kruskal(Edge edges[], int n, int e) {
    DisjointSet ds;
    makeSet(ds, n);

    const int resultSize = n - 1;
    Edge result[MAX];
    int mstCost = 0;
    int i = 0;

    while (i < resultSize && e < n * (n - 1) / 2) {
        Edge nextEdge = edges[e++];
        int x = find(ds, nextEdge.start - 'a');
        int y = find(ds, nextEdge.end - 'a');

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
    Edge edges[MAX];

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