#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Struct
struct Destinasi {
    string nama;
    string negara;
    string provinsi;
    string alamat_lengkap;
    int stok_tiket;
    int harga;
};

struct Pesanan {
    string nama_pemesan;
    Destinasi destinasi_dipesan;
};

// Stack untuk Undo
stack<Pesanan> undoStack;

// Queue dengan Array
const int MAX_ANTRIAN = 100;

struct QueuePesanan {
    Pesanan data[MAX_ANTRIAN];
    int front = 0;
    int rear = -1;
    int count = 0;

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX_ANTRIAN;
    }

    void enqueue(Pesanan p) {
        if (isFull()) {
            cout << "❌ Antrian penuh!\n";
            return;
        }
        rear = (rear + 1) % MAX_ANTRIAN;
        data[rear] = p;
        count++;
    }

    Pesanan dequeue() {
        if (isEmpty()) {
            cout << "❌ Antrian kosong!\n";
            return {};
        }
        Pesanan p = data[front];
        front = (front + 1) % MAX_ANTRIAN;
        count--;
        return p;
    }

    void tampilkan() {
        if (isEmpty()) {
            cout << "📭 Tidak ada pesanan dalam antrian.\n";
            return;
        }
        cout << "\n📋 Daftar Pesanan:\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAX_ANTRIAN;
            cout << i + 1 << ". " << data[idx].nama_pemesan
                 << " memesan ke " << data[idx].destinasi_dipesan.nama
                 << " - Rp " << data[idx].destinasi_dipesan.harga << "\n";
        }
    }

    bool hapusPesanan(const Pesanan& target) {
        if (isEmpty()) return false;
        bool ditemukan = false;
        Pesanan temp[MAX_ANTRIAN];
        int tempCount = 0;

        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAX_ANTRIAN;
            if (!ditemukan && data[idx].nama_pemesan == target.nama_pemesan &&
                data[idx].destinasi_dipesan.nama == target.destinasi_dipesan.nama) {
                ditemukan = true;
                continue;
            }
            temp[tempCount++] = data[idx];
        }

        front = 0;
        rear = -1;
        count = 0;
        for (int i = 0; i < tempCount; i++) {
            enqueue(temp[i]);
        }
        return ditemukan;
    }
};

// Algoritma Bubble Sort untuk mengurutkan berdasarkan nama (A-Z)
void bubbleSortByName(vector<Destinasi>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) {
                // Tukar posisi
                Destinasi temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Algoritma Selection Sort untuk mengurutkan berdasarkan harga (termurah-termahal)
void selectionSortByPrice(vector<Destinasi>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // Cari harga minimum di array yang belum terurut
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[min_idx].harga) {
                min_idx = j;
            }
        }
        
        // Tukar elemen minimum dengan elemen pertama
        if (min_idx != i) {
            Destinasi temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void pauseLanjut() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void tampilkanKatalog(const vector<Destinasi>& katalog) {
    cout << "\n📌 KATALOG DESTINASI WISATA 📌\n";
    cout << "====================================================================================================\n";
    cout << left << setw(4) << "No"
         << setw(25) << "Nama Destinasi"
         << setw(20) << "Negara"
         << setw(20) << "Provinsi"
         << setw(15) << "Harga"
         << setw(10) << "Stok" << endl;
    cout << "----------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < katalog.size(); i++) {
        cout << left << setw(4) << i + 1
             << setw(25) << katalog[i].nama
             << setw(20) << katalog[i].negara
             << setw(20) << katalog[i].provinsi
             << "Rp " << setw(11) << katalog[i].harga
             << setw(10) << katalog[i].stok_tiket << endl;
    }

    cout << "====================================================================================================\n";
}

void tampilkanDashboard() {
    cout << "\n=============================================\n";
    cout << "      🌍 Manejemen Destinasi Wisata 🌍        \n";
    cout << "=============================================\n";
    cout << "1. Lihat Katalog Destinasi\n";
    cout << "2. Tambah Pesanan\n";
    cout << "3. Undo Pesanan Terakhir\n";
    cout << "4. Proses Semua Pesanan\n";
    cout << "5. Keluar\n";
    cout << "---------------------------------------------\n";
    cout << "Pilih menu (1-5): ";
}

int main() {
    vector<Destinasi> katalog = {
        {"Eiffel Tower", "Prancis", "Ile-de-France", "Champ de Mars, Paris", 150, 350000},
        {"Mount Fuji", "Jepang", "Yamanashi", "Fujinomiya", 120, 300000},
        {"Statue of Liberty", "Amerika Serikat", "New York", "Liberty Island, NYC", 90, 400000},
        {"Colosseum", "Italia", "Lazio", "Piazza del Colosseo, Roma", 110, 375000},
        {"Great Wall", "Tiongkok", "Beijing", "Huairou District", 130, 280000},
        {"Santorini", "Yunani", "Aegean", "Thira, Cyclades", 100, 330000},
        {"Burj Khalifa", "Uni Emirat Arab", "Dubai", "1 Sheikh Mohammed bin Rashid", 200, 450000},
        {"Sydney Opera House", "Australia", "New South Wales", "Bennelong Point, Sydney", 80, 320000},
        {"Big Ben", "Inggris", "London", "Westminster, London", 140, 310000},
        {"Christ the Redeemer", "Brasil", "Rio de Janeiro", "Corcovado Mountain", 100, 290000}
    };

    QueuePesanan antrian;
    int pilihan;

    do {
        tampilkanDashboard();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                vector<Destinasi> katalog_terurut = katalog;
                int opsi_sort;
                cout << "\n🔽 Pilih jenis pengurutan:\n";
                cout << "1. Berdasarkan Nama (A-Z)\n";
                cout << "2. Berdasarkan Harga (Termurah-Termahal)\n";
                cout << "Pilihan: ";
                cin >> opsi_sort;

                if (opsi_sort == 1) {
                    // Menggunakan Bubble Sort untuk mengurutkan berdasarkan nama
                    bubbleSortByName(katalog_terurut);
                    cout << "\n✅ Katalog diurutkan berdasarkan nama\n";
                } else if (opsi_sort == 2) {
                    // Menggunakan Selection Sort untuk mengurutkan berdasarkan harga
                    selectionSortByPrice(katalog_terurut);
                    cout << "\n✅ Katalog diurutkan berdasarkan harga\n";
                } else {
                    cout << "⚠️  Pilihan tidak valid. Menampilkan data asli.\n";
                }

                tampilkanKatalog(katalog_terurut);
                pauseLanjut();
                break;
            }

            case 2: {
                tampilkanKatalog(katalog);
                Pesanan pesanan;
                int indeks;
                cout << "Nama Pemesan: ";
                getline(cin >> ws, pesanan.nama_pemesan);
                cout << "Pilih destinasi (1-" << katalog.size() << "): ";
                cin >> indeks;

                if (indeks < 1 || indeks > katalog.size()) {
                    cout << "❌ Pilihan tidak valid.\n";
                } else if (katalog[indeks - 1].stok_tiket == 0) {
                    cout << "❌ Stok tiket habis!\n";
                } else {
                    pesanan.destinasi_dipesan = katalog[indeks - 1];
                    katalog[indeks - 1].stok_tiket--;
                    antrian.enqueue(pesanan);
                    undoStack.push(pesanan);
                    cout << "✅ Pesanan berhasil ditambahkan!\n";
                }
                pauseLanjut();
                break;
            }

            case 3: {
                if (!undoStack.empty()) {
                    Pesanan terakhir = undoStack.top();
                    undoStack.pop();
                    bool dihapus = antrian.hapusPesanan(terakhir);
                    if (dihapus) {
                        for (auto& d : katalog) {
                            if (d.nama == terakhir.destinasi_dipesan.nama) {
                                d.stok_tiket++;
                                break;
                            }
                        }
                        cout << "↩️  Pesanan terakhir berhasil di-undo.\n";
                    }
                } else {
                    cout << "❌ Tidak ada pesanan yang bisa di-undo.\n";
                }
                pauseLanjut();
                break;
            }

            case 4: {
                cout << "\n🚚 Memproses Semua Antrian Pesanan...\n";
                if (antrian.isEmpty()) {
                    cout << "📭 Tidak ada pesanan dalam antrian.\n";
                } else {
                    while (!antrian.isEmpty()) {
                        Pesanan p = antrian.dequeue();
                        cout << "👤 " << p.nama_pemesan << " memesan ke "
                             << p.destinasi_dipesan.nama << " - Rp " << p.destinasi_dipesan.harga << endl;
                    }
                }
                pauseLanjut();
                break;
            }

            case 5:
                cout << "👋 Terima kasih telah menggunakan aplikasi!\n";
                break;

            default:
                cout << "⚠️  Pilihan tidak valid!\n";
                pauseLanjut();
        }

    } while (pilihan != 5);

    return 0;
}
