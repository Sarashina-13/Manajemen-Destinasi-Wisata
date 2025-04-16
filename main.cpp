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
    cout << "+-------------------------+-------------------+------------------+-------------------------------+------------+-----------------------+\n";
    cout << "| " << setw(23) << left << "Nama"
         << "| " << setw(17) << "Negara"
         << "| " << setw(16) << "Provinsi"
         << "| " << setw(29) << "Alamat Lengkap"
         << "| " << setw(10) << "Stok Tiket"
         << "| " << setw(21) << "Harga (Rp)"
         << "|\n";
    cout << "+-------------------------+-------------------+------------------+-------------------------------+------------+-----------------------+\n";
    for (int i = 0; i < katalog.size(); i++) {
        cout << "| " << setw(23) << left << katalog[i].nama
             << "| " << setw(17) << katalog[i].negara
             << "| " << setw(16) << katalog[i].provinsi
             << "| " << setw(29) << katalog[i].alamat_lengkap
             << "| " << setw(10) << katalog[i].stok_tiket
             << "| " << setw(21) << katalog[i].harga
             << "|\n";
    }
    cout << "+-------------------------+-------------------+------------------+-------------------------------+------------+-----------------------+\n";
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
