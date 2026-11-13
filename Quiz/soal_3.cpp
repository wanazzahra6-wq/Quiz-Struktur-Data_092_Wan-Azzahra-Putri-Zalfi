#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

const int V = 6; // Jumlah vertex (A, B, C, D, E, F)
char vertexChar[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Fungsi untuk mengubah karakter (A-F) menjadi indeks angka (0-5)
int getIndex(char c) {
    return c - 'A';
}

// 1. BFS (Breadth-First Search) - Penelusuran Melebar
void bfs(int adjMatrix[V][V], int startVertex) {
    bool visited[V] = {false};
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    cout << "Traversal BFS: ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << vertexChar[curr] << " ";

        for (int i = 0; i < V; i++) {
            // Jika ada jalur (bobot > 0) dan belum dikunjungi
            if (adjMatrix[curr][i] > 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << "\n";
}

// 2. DFS (Depth-First Search) - Penelusuran Mendalam
void dfsUtil(int adjMatrix[V][V], int curr, bool visited[]) {
    visited[curr] = true;
    cout << vertexChar[curr] << " ";

    for (int i = 0; i < V; i++) {
        if (adjMatrix[curr][i] > 0 && !visited[i]) {
            dfsUtil(adjMatrix, i, visited);
        }
    }
}

void dfs(int adjMatrix[V][V], int startVertex) {
    bool visited[V] = {false};
    cout << "Traversal DFS: ";
    dfsUtil(adjMatrix, startVertex, visited);
    cout << "\n";
}

// 3. DIJKSTRA (Mencari Jarak & Rute Terpendek)
void dijkstra(int adjMatrix[V][V], int src, int dest) {
    int dist[V];
    bool sptSet[V];
    int parent[V];

    // Inisialisasi jarak tak terhingga dan parent
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        // Cari vertex dengan jarak minimum yang belum diproses
        int min = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v], u = v;
            }
        }

        if (u == -1) break;
        sptSet[u] = true;

        // Perbarui jarak tetangga dari vertex u
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Tampilkan hasil jarak dan rute ke tujuan
    cout << "\n--- HASIL DIJKSTRA (" << vertexChar[src] << " ke " << vertexChar[dest] << ") ---\n";
    if (dist[dest] == INT_MAX) {
        cout << "Tidak ada rute menuju " << vertexChar[dest] << ".\n";
        return;
    }

    cout << "Total Jarak Terpendek: " << dist[dest] << "\n";
    cout << "Rute yang dilalui: ";
    
    // Rekonstruksi jalur dari parent
    stack<int> path;
    int curr = dest;
    while (curr != -1) {
        path.push(curr);
        curr = parent[curr];
    }

    while (!path.empty()) {
        cout << vertexChar[path.top()];
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << "\n";
}

// FUNGSI UTAMA (MAIN)
int main() {
    // Inisialisasi Adjacency Matrix ukuran 6x6 (A sampai F) dengan nilai 0 (tidak ada sisi)
    int adjMatrix[V][V] = {0};

    // Memasukkan bobot/jarak berdasarkan tabel soal
    // A(0), B(1), C(2), D(3), E(4), F(5)
    adjMatrix[getIndex('A')][getIndex('B')] = 4; adjMatrix[getIndex('B')][getIndex('A')] = 4;
    adjMatrix[getIndex('A')][getIndex('C')] = 2; adjMatrix[getIndex('C')][getIndex('A')] = 2;
    
    adjMatrix[getIndex('B')][getIndex('C')] = 1; adjMatrix[getIndex('C')][getIndex('B')] = 1;
    adjMatrix[getIndex('B')][getIndex('D')] = 5; adjMatrix[getIndex('D')][getIndex('B')] = 5;
    adjMatrix[getIndex('B')][getIndex('E')] = 3; adjMatrix[getIndex('E')][getIndex('B')] = 3;
    
    adjMatrix[getIndex('C')][getIndex('D')] = 8; adjMatrix[getIndex('D')][getIndex('C')] = 8;
    adjMatrix[getIndex('C')][getIndex('E')] = 6; adjMatrix[getIndex('E')][getIndex('C')] = 6;
    
    adjMatrix[getIndex('D')][getIndex('E')] = 2; adjMatrix[getIndex('E')][getIndex('D')] = 2;
    adjMatrix[getIndex('D')][getIndex('F')] = 4; adjMatrix[getIndex('F')][getIndex('D')] = 4;
    
    adjMatrix[getIndex('E')][getIndex('F')] = 3; adjMatrix[getIndex('F')][getIndex('E')] = 3;

    // 1. Jalankan Penelusuran Graf (BFS & DFS) mulai dari Vertex 'A'
    cout << "=== PENELUSURAN GRAF (Mulai dari A) ===\n";
    bfs(adjMatrix, getIndex('A'));
    dfs(adjMatrix, getIndex('A'));

    // 2. Simulasi Algoritma Dijkstra dengan pilihan pengguna
    char awal, tujuan;
    cout << "\n=== PENCARIAN RUTE TERPENDEK (DIJKSTRA) ===\n";
    cout << "Masukkan Vertex Awal (A-F): ";
    cin >> awal;
    cout << "Masukkan Vertex Tujuan (A-F): ";
    cin >> tujuan;

    dijkstra(adjMatrix, getIndex(awal), getIndex(tujuan));

    return 0;
}