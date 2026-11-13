#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. Struct untuk Node Single Linked List (menyimpan NIM, Nama, Nilai)
struct Mahasiswa {
    string nim;
    string nama;
    float nilai;
    Mahasiswa* next; // Pointer ke node mahasiswa berikutnya
};

// Fungsi untuk menambah data mahasiswa ke akhir Single Linked List
void tambahMahasiswa(Mahasiswa*& head, string nim, string nama, float nilai) {
    Mahasiswa* newNode = new Mahasiswa();
    newNode->nim = nim;
    newNode->nama = nama;
    newNode->nilai = nilai;
    newNode->next = nullptr;

    // Jika linked list masih kosong, node baru jadi head (elemen pertama)
    if (head == nullptr) {
        head = newNode;
    } else {
        // Jika tidak kosong, telusuri sampai node terakhir
        Mahasiswa* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; // Sambungkan node baru di akhir
    }
}

// Fungsi untuk menampilkan seluruh data mahasiswa dari Single Linked List
void tampilkanMahasiswa(Mahasiswa* head) {
    if (head == nullptr) {
        cout << "Data mahasiswa kosong!\n";
        return;
    }
    
    cout << "\n--- DAFTAR DATA MAHASISWA ---\n";
    Mahasiswa* temp = head;
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". NIM   : " << temp->nim << "\n";
        cout << "   Nama  : " << temp->nama << "\n";
        cout << "   Nilai : " << temp->nilai << "\n";
        cout << "-----------------------------\n";
        temp = temp->next;
    }
}

// Fungsi untuk mengambil semua nilai dari Linked List dan memasukkannya ke Dynamic Array (vector)
vector<float> ambilNilaiKeArray(Mahasiswa* head) {
    vector<float> arrNilai;
    Mahasiswa* temp = head;
    while (temp != nullptr) {
        arrNilai.push_back(temp->nilai); // Masukkan nilai ke vector (Dynamic Array)
        temp = temp->next;
    }
    return arrNilai;
}

// Fungsi untuk mengurutkan nilai menggunakan Insertion Sort (Terkecil ke Terbesar)
void insertionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        
        // Pindahkan elemen yang lebih besar dari key ke posisi sebelah kanannya
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Fungsi Linear Search untuk mencari data mahasiswa berdasarkan NIM pada Single Linked List
void linearSearchNIM(Mahasiswa* head, string cariNIM) {
    Mahasiswa* temp = head;
    bool ketemu = false;
    
    cout << "\n--- HASIL LINEAR SEARCH (Cari NIM: " << cariNIM << ") ---\n";
    while (temp != nullptr) {
        if (temp->nim == cariNIM) {
            cout << "Data Ditemukan!\n";
            cout << "NIM   : " << temp->nim << "\n";
            cout << "Nama  : " << temp->nama << "\n";
            cout << "Nilai : " << temp->nilai << "\n";
            ketemu = true;
            break;
        }
        temp = temp->next;
    }
    
    if (!ketemu) {
        cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
    }
}

// Fungsi Binary Search untuk mencari nilai tertentu pada Dynamic Array yang sudah terurut
void binarySearchNilai(const vector<float>& arr, float cariNilai) { //untuk membagi area pencarian menjadi dua secara berulang.
    int kiri = 0;
    int kanan = arr.size() - 1;
    bool ketemu = false;
    
    cout << "\n--- HASIL BINARY SEARCH (Cari Nilai: " << cariNilai << ") ---\n";
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        
        if (arr[tengah] == cariNilai) {
            cout << "Nilai " << cariNilai << " ditemukan pada indeks array ke-" << tengah << "\n";
            ketemu = true;
            break;
        }
        
        if (arr[tengah] < cariNilai) {
            kiri = tengah + 1; // Cari di sisi kanan
        } else {
            kanan = tengah - 1; // Cari di sisi kiri
        }
    }
    
    if (!ketemu) {
        cout << "Nilai " << cariNilai << " tidak ditemukan dalam daftar.\n";
    }
}

int main() {
    Mahasiswa* head = nullptr; // Inisialisasi awal Linked List kosong

    // 1. Memasukkan contoh data mahasiswa
    tambahMahasiswa(head, "251401001", "Ani", 78.5);
    tambahMahasiswa(head, "251401092", "Rara", 95.0);
    tambahMahasiswa(head, "251401045", "Budi", 60.0);
    tambahMahasiswa(head, "251401012", "Citra", 85.5);
    tambahMahasiswa(head, "251401077", "Dodi", 70.0);

    // 2. Tampilkan data awal mahasiswa
    tampilkanMahasiswa(head);

    // 3. Konversi nilai ke Dynamic Array (vector) lalu urutkan dengan Insertion Sort
    vector<float> daftarNilai = ambilNilaiKeArray(head);
    insertionSort(daftarNilai);

    // Tampilkan hasil pengurutan nilai
    cout << "\n--- HASIL INSERTION SORT (Nilai Terkecil ke Terbesar) ---\n";
    for (size_t i = 0; i < daftarNilai.size(); i++) {
        cout << daftarNilai[i] << " ";
    }
    cout << "\n";

    // 4. Fitur Pencarian (Linear Search untuk NIM & Binary Search untuk Nilai)
    linearSearchNIM(head, "251401092"); // Contoh cari NIM Rara
    binarySearchNilai(daftarNilai, 85.5);   // Contoh cari nilai tertentu

    return 0;
}