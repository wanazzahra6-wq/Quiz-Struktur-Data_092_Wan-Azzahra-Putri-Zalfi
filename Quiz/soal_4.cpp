#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int TABLE_SIZE = 20;

// Struktur untuk menyimpan data mahasiswa di Hash Table
struct Mahasiswa {
    long long nim; 
    string nama;
    bool isOccupied; 
    bool isDeleted;  
    Mahasiswa() {
        nim = -1;
        nama = "";
        isOccupied = false;
        isDeleted = false;
    }
};

class HashDoubleHashing {
private:
    Mahasiswa table[TABLE_SIZE];
    int totalData;

    // Hash Function 1: key % 20
    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    // Hash Function 2: 19 - (key % 19)
    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    HashDoubleHashing() {
        totalData = 0;
    }

    // Fungsi Insert dengan Double Hashing
    void insert(long long nim, string nama) {
        if (totalData >= TABLE_SIZE) {
            cout << "Hash Table penuh! Tidak dapat memasukkan NIM " << nim << "\n";
            return;
        }

        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;

        // Cari slot kosong menggunakan rumus double hashing
        while (table[index].isOccupied && table[index].nim != nim) {
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (i >= TABLE_SIZE) {
                cout << "Collision resolution gagal atau tabel penuh.\n";
                return;
            }
        }

        // Masukkan data ke slot yang ditemukan
        table[index].nim = nim;
        table[index].nama = nama;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        totalData++;
        
        if (i > 0) {
            cout << "Insert NIM " << nim << " (" << nama << ") berhasil pada indeks " << index << " (Terjadi Collision, i=" << i << ")\n";
        } else {
            cout << "Insert NIM " << nim << " (" << nama << ") berhasil pada indeks " << index << "\n";
        }
    }

    // Fungsi Search (Pencarian Data berdasarkan NIM)
    void search(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;

        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].nim == nim) {
                cout << "[DITEMUKAN] NIM: " << table[index].nim << " | Nama: " << table[index].nama << " pada Indeks ke-" << index << "\n";
                return;
            }
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (i >= TABLE_SIZE) break;
        }

        cout << "[TIDAK DITEMUKAN] Mahasiswa dengan NIM " << nim << " tidak ada dalam Hash Table.\n";
    }

    // Fungsi Remove (Penghapusan Data berdasarkan NIM)
    void remove(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;

        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].nim == nim) {
                table[index].isOccupied = false;
                table[index].isDeleted = true; // Tandai sebagai deleted agar probing tidak terputus
                table[index].nim = -1;
                table[index].nama = "";
                totalData--;
                cout << "[BERHASIL DIHAPUS] Data dengan NIM " << nim << " dari indeks " << index << "\n";
                return;
            }
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (i >= TABLE_SIZE) break;
        }

        cout << "[GAGAL HAPUS] NIM " << nim << " tidak ditemukan untuk dihapus.\n";
    }

    // Fungsi Display (Menampilkan seluruh isi Hash Table)
    void display() {
        cout << "\n=========================================\n";
        cout << "            ISI HASH TABLE               \n";
        cout << "=========================================\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Indeks " << (i < 10 ? " " : "") << i << " : ";
            if (table[i].isOccupied) {
                cout << "[NIM: " << table[i].nim << " | Nama: " << table[i].nama << "]\n";
            } else {
                cout << "[KOSONG]\n";
            }
        }
        cout << "=========================================\n\n";
    }
};

int main() {
    HashDoubleHashing ht;

    cout << "=== 1. PROSES INSERT 15+ DATA MAHASISWA & UJI COLLISION ===\n";
    // Memasukkan 16 data mahasiswa untuk menguji ukuran 20 dan kondisi collision
    ht.insert(251401001, "Ani");
    ht.insert(251401021, "Budi"); // Akan mengalami collision dengan Ani di indeks yang sama (251401021 % 20 == 251401001 % 20)
    ht.insert(251401041, "Citra"); // Uji collision lanjutan
    ht.insert(251401092, "Rara");
    ht.insert(251401012, "Dodi");
    ht.insert(251401045, "Eka");
    ht.insert(251401077, "Fajar");
    ht.insert(251401003, "Gita");
    ht.insert(251401015, "Hadi");
    ht.insert(251401025, "Intan");
    ht.insert(251401033, "Joko");
    ht.insert(251401050, "Kiki");
    ht.insert(251401065, "Lala");
    ht.insert(251401080, "Maya");
    ht.insert(251401088, "Niko");
    ht.insert(251401099, "Omar");

    // Tampilkan tabel setelah insert
    ht.display();

    // 2. Uji Fitur Search (Pencarian)
    cout << "=== 2. UJI FITUR SEARCH ===\n";
    ht.search(251401092); // Cari Rara
    ht.search(251401050); // Cari Kiki
    ht.search(251401999); // Cari NIM yang tidak ada

    // 3. Uji Fitur Remove (Penghapusan & Uji Collision setelah hapus)
    cout << "\n=== 3. UJI FITUR REMOVE ===\n";
    ht.remove(251401021); // Hapus Budi
    ht.search(251401021); // Cek apakah sudah hilang

    // Tampilkan tabel akhir
    ht.display();

    return 0;
}