#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

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

// Fungsi untuk menampilkan katalog
void tampilkanKatalog(const vector<Destinasi>& katalog) {
    cout << "\n=== Katalog Destinasi Wisata ===\n";
    for (size_t i = 0; i < katalog.size(); i++) {
        cout << i + 1 << ". " << katalog[i].nama << " - " << katalog[i].negara << " - " << katalog[i].provinsi
        << " - " << " (Rp " << katalog[i].harga << " - stok :" << katalog[i].stok_tiket << ")\n";
    }
    cout << endl;
}

int main() {
    // Katalog wisata (menggunakan vector)
    vector<Destinasi> katalog = {
        {"Pantai Parangtritis", "Yogyakarta", 75000},
        {"Candi Borobudur", "Magelang", 100000},
        {"Gunung Bromo", "Jawa Timur", 125000},
        {"Taman Mini", "Jakarta", 50000},
        {"Danau Toba", "Sumatera Utara", 120000}
    };

    // Queue untuk antrian pesanan
    queue<Pesanan> antrian;

    char lanjut;
    do {
        tampilkanKatalog(katalog);

        Pesanan pesanan;
        int pilihan;

        cout << "Nama Pemesan: ";
        getline(cin >> ws, pesanan.nama_pemesan);

        cout << "Pilih destinasi (1-" << katalog.size() << "): ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > katalog.size()) {
            cout << "Pilihan tidak valid.\n";
        } else {
            pesanan.destinasi_dipesan = katalog[pilihan - 1];
            antrian.push(pesanan);
            cout << "Pesanan berhasil ditambahkan!\n";
        }

        cout << "Tambah pesanan lagi? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');

    // Proses antrian pesanan
    cout << "\n=== Memproses Antrian Pesanan ===\n";
    while (!antrian.empty()) {
        Pesanan p = antrian.front();
        cout << p.nama_pemesan << " memesan ke "
             << p.destinasi_dipesan.nama << " (" << p.destinasi_dipesan.lokasi
             << "), Harga: Rp " << p.destinasi_dipesan.harga << endl;
        antrian.pop();
    }

    return 0;
}
