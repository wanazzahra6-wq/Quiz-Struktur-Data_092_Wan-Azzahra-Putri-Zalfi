#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// 1. STRUKTUR & FUNGSI UNTUK BINARY SEARCH TREE (BST) - ID Buku
struct NodeBuku {
    int idBuku;
    NodeBuku* left;
    NodeBuku* right;

    NodeBuku(int id) {
        idBuku = id;
        left = right = nullptr;
    }
};

// Fungsi untuk memasukkan ID buku baru ke dalam BST
NodeBuku* insertBST(NodeBuku* root, int id) {
    if (root == nullptr) return new NodeBuku(id);
    if (id < root->idBuku)
        root->left = insertBST(root->left, id);
    else if (id > root->idBuku)
        root->right = insertBST(root->right, id);
    return root;
}

// Fungsi Pencarian ID Buku pada BST
NodeBuku* searchBST(NodeBuku* root, int key) {
    if (root == nullptr || root->idBuku == key)
        return root;
    if (root->idBuku < key)
        return searchBST(root->right, key);
    return searchBST(root->left, key);
}

// Traversal Pre-Order: Root -> Left -> Right
void preOrder(NodeBuku* root) {
    if (root != nullptr) {
        cout << root->idBuku << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Traversal In-Order: Left -> Root -> Right (Menghasilkan ID terurut)
void inOrder(NodeBuku* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->idBuku << " ";
        inOrder(root->right);
    }
}

// Traversal Post-Order: Left -> Right -> Root
void postOrder(NodeBuku* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->idBuku << " ";
    }
}

// 2. FUNGSI UTAMA (MAIN)
int main() {
    // IMPLEMENTASI QUEUE (Antrean Peminjaman Buku - FIFO)
    // Menggunakan library <queue> 
    queue<string> antreanPeminjaman;

    cout << "=== 1. PROSES ANTREAN PEMINJAMAN BUKU (QUEUE - FIFO) ===\n";
    // Mahasiswa mendaftar antrean peminjaman (enqueue)
    antreanPeminjaman.push("Ani (NIM: 251401001)");
    antreanPeminjaman.push("Rara (NIM: 251401092)");
    antreanPeminjaman.push("Budi (NIM: 251401045)");

    cout << "Mahasiswa pertama dalam antrean yang akan dilayani: " << antreanPeminjaman.front() << "\n";
    
    // Melayani mahasiswa (dequeue / keluar antrean)
    cout << "Melayani peminjaman untuk: " << antreanPeminjaman.front() << "\n";
    antreanPeminjaman.pop(); 
    
    cout << "Antrean berikutnya yang dilayani: " << antreanPeminjaman.front() << "\n\n";

    // IMPLEMENTASI STACK (Riwayat Pengembalian Buku - LIFO) ---
    // Menggunakan library <stack> bawaan C++
    stack<string> riwayatPengembalian;

    cout << "=== 2. PROSES RIWAYAT PENGEMBALIAN BUKU (STACK - LIFO) ===\n";
    // Buku dikembalikan dan ditumpuk paling atas (push)
    riwayatPengembalian.push("Buku Algoritma dan Pemrograman (ID: 101)");
    riwayatPengembalian.push("Buku Struktur Data (ID: 102)");
    riwayatPengembalian.push("Buku Basis Data (ID: 103)");

    cout << "Riwayat pengembalian terakhir (paling atas tumpukan): " << riwayatPengembalian.top() << "\n";

    // Mengambil buku dari tumpukan atas untuk dicek petugas (pop)
    cout << "Memproses buku dari tumpukan: " << riwayatPengembalian.top() << "\n";
    riwayatPengembalian.pop();

    cout << "Riwayat teratas sekarang menjadi: " << riwayatPengembalian.top() << "\n\n";


    // IMPLEMENTASI BINARY SEARCH TREE (BST) - ID Buku ---
    cout << "=== 3. PENGELOLAAN ID BUKU DENGAN BST ===\n";
    NodeBuku* rootBuku = nullptr;
    
    // Masukkan data ID buku ke BST
    int daftarID[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : daftarID) {
        rootBuku = insertBST(rootBuku, id);
    }
    cout << "Data ID Buku berhasil dimasukkan ke BST.\n\n";

    // Menampilkan Traversal BST
    cout << "Traversal Pre-Order  : ";
    preOrder(rootBuku);
    cout << "\n";

    cout << "Traversal In-Order   : ";
    inOrder(rootBuku);
    cout << "\n";

    cout << "Traversal Post-Order : ";
    postOrder(rootBuku);
    cout << "\n\n";

    // Fitur Pencarian ID Buku di BST
    int cariID = 60;
    NodeBuku* hasilCari = searchBST(rootBuku, cariID);
    cout << "--- PENCARIAN ID BUKU DI BST ---\n";
    if (hasilCari != nullptr) {
        cout << "ID Buku " << cariID << " DITEMUKAN di dalam BST.\n";
    } else {
        cout << "ID Buku " << cariID << " TIDAK DITEMUKAN.\n";
    }

    return 0;
}