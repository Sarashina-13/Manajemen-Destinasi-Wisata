#include <iostream>
#include <vector>
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
    int jumlah_tiket;
    Destinasi destinasi_dipesan;
};

// fromatting untuk harga
string formatRupiah(int angka) {
    string angkaStr = to_string(angka);
    string hasil;

    int count = 0;
    // Loop mundur dari belakang string angka
    for (int i = (int)angkaStr.size() - 1; i >= 0; i--) {
        hasil.push_back(angkaStr[i]);
        count++;
        // Setiap 3 digit tambahkan titik, kecuali di paling depan
        if (count % 3 == 0 && i != 0) {
            hasil.push_back('.');
        }
    }
    reverse(hasil.begin(), hasil.end());
    return "Rp " + hasil;
}

const int MAX_STACK = 100;

// Stack untuk Undo
struct Stack {
    Pesanan data[MAX_STACK];
    int top = -1;

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_STACK - 1;
    }

    void push(Pesanan p) {
        if (isFull()) {
            cout << "❌ Stack penuh!\n";
            return;
        }
        data[++top] = p;
    }
    Pesanan pop() {
        if (isEmpty()) {
            cout << "❌ Stack kosong!\n";
            return {};
        }
        return data[top--];
    }

    Pesanan peek() {
        if (isEmpty()) {
            return {};
        }
        return data[top];
    }
};

// Queue dengan Array
const int MAX_ANTRIAN = 100;

struct Queue {
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
            cout << "❌ Queue penuh!\n";
            return;
        }
        rear = (rear + 1) % MAX_ANTRIAN;
        data[rear] = p;
        count++;
    }

    Pesanan dequeue() {
        if (isEmpty()) {
            cout << "❌ Queue kosong!\n";
            return {};
        }
        Pesanan p = data[front];
        front = (front + 1) % MAX_ANTRIAN;
        count--;
        return p;
    }

    void tampilkan() {
        cout << "\n🎟️ DAFTAR PESANAN 🎟️\n";
        cout << "======================================================================================================================\n";
        cout << left << setw(4)  << "No"
            << setw(20) << "Nama Pemesan"
            << setw(25) << "Nama Destinasi"
            << setw(20) << "Negara"
            << setw(20) << "Provinsi"
            << setw(15) << "Jumlah Tiket"
            << setw(20) << "Total Harga" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAX_ANTRIAN;
            const Pesanan& p = data[idx];
            cout << left << setw(4)  << i + 1
                << setw(20) << p.nama_pemesan
                << setw(25) << p.destinasi_dipesan.nama
                << setw(20) << p.destinasi_dipesan.negara
                << setw(20) << p.destinasi_dipesan.provinsi
                << setw(15) << p.jumlah_tiket
                << setw(20) << formatRupiah(p.jumlah_tiket * p.destinasi_dipesan.harga) << endl;
    }

    cout << "======================================================================================================================\n";
}


    // Fungsi hapus pesanan berdasarkan nomor urut tampilan
    Pesanan hapusPesananByIndex(int index) {
        Pesanan pesananKosong = {};
        
        if (index < 1 || index > count) {
            return pesananKosong; // Return empty pesanan jika gagal
        }
        
        // Ambil pesanan yang akan dihapus berdasarkan nomor tampilan
        int targetIdx = (front + index - 1) % MAX_ANTRIAN;
        Pesanan pesananDihapus = data[targetIdx];
        
        // Hapus pesanan dengan rebuild queue
        Pesanan temp[MAX_ANTRIAN];
        int tempCount = 0;
        
        // Copy semua pesanan kecuali yang dihapus
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAX_ANTRIAN;
            if (i != (index - 1)) { // Skip pesanan yang akan dihapus
                temp[tempCount++] = data[idx];
            }
        }
        
        // Reset queue dan masukkan kembali data yang tersisa
        front = 0;
        rear = -1;
        count = 0;
        for (int i = 0; i < tempCount; i++) {
            enqueue(temp[i]);
        }
        
        return pesananDihapus; // Return pesanan yang berhasil dihapus
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

void insertionSortByName(vector<Destinasi>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Destinasi key = arr[i];
        int j = i - 1;
        
        // Pindahkan elemen yang lebih besar dari key ke posisi setelahnya
        while (j >= 0 && arr[j].nama > key.nama) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Insertion Sort untuk mengurutkan berdasarkan negara (A-Z)
void insertionSortByCountry(vector<Destinasi>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Destinasi key = arr[i];
        int j = i - 1;
        
        // Pindahkan elemen yang lebih besar dari key ke posisi setelahnya
        while (j >= 0 && arr[j].negara > key.negara) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Insertion Sort untuk mengurutkan berdasarkan harga (termurah-termahal)
void insertionSortByPrice(vector<Destinasi>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Destinasi key = arr[i];
        int j = i - 1;
        
        // Pindahkan elemen yang lebih mahal dari key ke posisi setelahnya
        while (j >= 0 && arr[j].harga > key.harga) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void pauseLanjut() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void tampilkanKatalog(const vector<Destinasi>& katalog) {
    cout << "\n📌 KATALOG DESTINASI WISATA 📌\n";
    cout << "=============================================================================================\n";
    cout << left << setw(4) << "No"
         << setw(25) << "Nama Destinasi"
         << setw(20) << "Negara"
         << setw(20) << "Provinsi"
         << setw(17) << "Harga"
         << setw(10) << "Stok" << endl;
    cout << "---------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < katalog.size(); i++) {
        cout << left << setw(4) << i + 1
             << setw(25) << katalog[i].nama
             << setw(20) << katalog[i].negara
             << setw(20) << katalog[i].provinsi
             << setw(17) << formatRupiah(katalog[i].harga)
             << setw(10) << katalog[i].stok_tiket << endl;
    }

    cout << "=============================================================================================\n";
}

void menuSort(vector<Destinasi>& katalog) {
    vector<Destinasi> katalog_terurut = katalog;
    int opsi_sort;
    
    do {
        cout << "\n📊 MENU SORTING 📊\n";
        cout << "==========================\n";
        cout << "1. Urutkan Berdasarkan Nama (A-Z)\n";
        cout << "2. Urutkan Berdasarkan Negara (A-Z)\n";
        cout << "3. Urutkan Berdasarkan Harga (Termurah-Termahal)\n";
        cout << "4. Tampilkan Katalog Asli\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih opsi (0-4): ";
        cin >> opsi_sort;

        switch (opsi_sort) {
            case 1:
                insertionSortByName(katalog_terurut);
                cout << "\n✅ Katalog diurutkan berdasarkan nama (A-Z)\n";
                tampilkanKatalog(katalog_terurut);
                break;
            case 2:
                insertionSortByCountry(katalog_terurut);
                cout << "\n✅ Katalog diurutkan berdasarkan negara (A-Z)\n";
                tampilkanKatalog(katalog_terurut);
                break;
            case 3:
                insertionSortByPrice(katalog_terurut);
                cout << "\n✅ Katalog diurutkan berdasarkan harga (Termurah-Termahal)\n";
                tampilkanKatalog(katalog_terurut);
                break;
            case 4:
                katalog_terurut = katalog; // Reset ke data asli
                cout << "\n✅ Menampilkan data asli\n";
                tampilkanKatalog(katalog_terurut);
                break;
            case 0:
                cout << "🔙 Kembali ke menu utama...\n";
                break;
            default:
                cout << "⚠️ Pilihan tidak valid!\n";
        }
        
        if (opsi_sort != 0) {
            pauseLanjut();
        }
    } while (opsi_sort != 0);
}

void tampilkanDashboard() {
    cout << "\n=============================================\n";
    cout << "      🌍 Manejemen Destinasi Wisata 🌍      \n";
    cout << "=============================================\n";
    cout << "1. Lihat Katalog Destinasi\n";
    cout << "2. Tambah Pesanan\n";
    cout << "3. Lihat Daftar Pesanan\n";
    cout << "4. Hapus Pesanan\n";
    cout << "6. Undo Pesanan Terakhir\n";
    cout << "5. Proses Semua Pesanan\n";
    cout << "0. Keluar\n";
    cout << "---------------------------------------------\n";
    cout << "Pilih menu (1-5): ";
}

int main() {
    vector<Destinasi> katalog = {
        {"Labuan Bajo", "Indonesia", "NTT", "Flores Island", 20, 800000},
        {"Fushimi Inari", "Japan", "Kyoto", "Fushimi Ward, Kyoto", 30, 100000},
        {"Tana Toraja", "Indonesia", "Sulawesi Selatan", "Makale", 15, 200000},
        {"Petra", "Jordan", "Ma'an", "Wadi Musa", 15, 500000},
        {"Angkor Wat", "Kamboja", "Siem Reap", "Angkor Archaeological Park", 25, 300000},
        {"Grand Canyon", "USA", "Arizona", "Grand Canyon Village", 50, 200000},
        {"Borobudur", "Indonesia", "Jawa Tengah", "Magelang, Jawa Tengah", 45, 75000},
        {"Mount Merbabu", "Indonesia", "Jawa Tengah", "Boyolali", 25, 50000},
        {"Bagan Temples", "Myanmar", "Mandalay", "Bagan Archaeological Zone", 20, 250000},
        {"Sydney Opera", "Australia", "NSW", "Bennelong Point, Sydney", 30, 300000},
        {"Table Mountain", "South Africa", "Western Cape", "Cape Town", 30, 150000},
        {"Cappadocia", "Turkey", "Nevşehir", "Central Anatolia", 25, 350000},
        {"Stonehenge", "UK", "Wiltshire", "Amesbury", 20, 250000},
        {"Pyramids of Giza", "Egypt", "Giza", "Al Haram, Giza", 35, 300000},
        {"Burj Khalifa", "UAE", "Dubai", "Downtown Dubai", 40, 500000},
        {"Taj Mahal", "India", "Uttar Pradesh", "Agra", 40, 200000},
        {"Agra Fort", "India", "Uttar Pradesh", "Agra", 35, 100000},
        {"North Pole", "Arctic", "Polar Region", "Arctic Ocean", 5, 5000000},
        {"Christ Redeemer", "Brazil", "Rio de Janeiro", "Corcovado Mountain", 40, 150000},
        {"Chichen Itza", "Mexico", "Yucatan", "Tinum Municipality", 25, 180000},
        {"Acropolis", "Greece", "Attica", "Athens", 35, 200000},
        {"Colosseum", "Italy", "Lazio", "Piazza del Colosseo, Rome", 40, 400000},
        {"Florence Cathedral", "Italy", "Lazio", "Florence", 30, 250000},
        {"Sagrada Familia", "Spain", "Catalonia", "Barcelona", 30, 350000},
        {"Raja Ampat", "Indonesia", "Papua Barat", "Waigeo Island", 15, 1200000},
        {"Wamena Valley", "Indonesia", "Papua Barat", "Jayawijaya", 10, 600000},
        {"Space Station", "Low Orbit", "Space", "ISS", 3, 10000000},
        {"Victoria Falls", "Zambia", "Southern Province", "Livingstone", 20, 400000},
        {"Neuschwanstein", "Germany", "Bavaria", "Schwangau", 25, 300000},
        {"Munich Residenz", "Germany", "Bavaria", "Munich", 20, 250000},
        {"Milford Sound", "New Zealand", "Southland", "Fiordland NP", 15, 250000},
        {"Great Wall", "China", "Beijing", "Huairou District", 35, 350000},
        {"Forbidden City", "China", "Beijing", "Dongcheng District", 30, 300000},
        {"Niagara Falls", "Canada", "Ontario", "Niagara River", 45, 120000},
        {"Algonquin Park", "Canada", "Ontario", "Ontario Forest", 20, 90000},
        {"Bromo Tengger", "Indonesia", "Jawa Timur", "Probolinggo", 25, 150000},
        {"Ijen Crater", "Indonesia", "Jawa Timur", "Bondowoso", 20, 120000},
        {"Pura Besakih", "Indonesia", "Bali", "Karangasem, Bali", 30, 50000},
        {"Eiffel Tower", "France", "Île-de-France", "Champ de Mars, Paris", 50, 450000},
        {"Lake Toba", "Indonesia", "Sumatera Utara", "Samosir Island", 20, 175000}
    };


    Queue antrianPesanan;
    Stack undoStack;
    int pilihan;

    do {
        tampilkanDashboard();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                tampilkanKatalog(katalog);
                menuSort(katalog);
                break;
            }

            case 2: {
                tampilkanKatalog(katalog);
                Pesanan pesanan;
                int indeks;

                cout << "Pilih destinasi (1-" << katalog.size() << "): ";
                cin >> indeks;
                if (indeks < 1 || indeks > katalog.size()) {
                    cout << "❌ Pilihan tidak valid.\n";
                } else if (katalog[indeks - 1].stok_tiket == 0) {
                    cout << "❌ Stok tiket habis!\n";
                    
                } else {
                    cout << "Nama Pemesan: ";
                    getline(cin >> ws, pesanan.nama_pemesan);
                    cout << "Jumlah tiket yang dipesan: ";
                    cin >>  pesanan.jumlah_tiket;
                    if (pesanan.jumlah_tiket > katalog[indeks - 1].stok_tiket)
                        cout << "❌ Stok tiket kurang!\n";
                    else if (pesanan.jumlah_tiket < 1)
                        cout << "❌ Jumlah tidak valid.\n";
                    else {
                        pesanan.destinasi_dipesan = katalog[indeks - 1];
                        katalog[indeks - 1].stok_tiket -= pesanan.jumlah_tiket;
                        antrianPesanan.enqueue(pesanan);
                        undoStack.push(pesanan);
                        cout << "✅ Pesanan berhasil ditambahkan!\n";
                    }   
                }
                pauseLanjut();
                break;
            }
            
            case 3: {
                antrianPesanan.tampilkan();
                pauseLanjut();
                break;
            }

            case 4: {
                cout << "\n🗑️ HAPUS PESANAN 🗑️\n";
                if (!antrianPesanan.isEmpty()) {
                    antrianPesanan.tampilkan();
                    int pilihan_penghapusan;
                    cout << "Pilih pesanan yang ingin dihapus (1-" << antrianPesanan.count << "): ";
                    cin >> pilihan_penghapusan;

                    if (pilihan_penghapusan < 1 || pilihan_penghapusan > antrianPesanan.count) {
                        cout << "❌ Pilihan tidak valid.\n";
                    } else {
                        // Hapus pesanan dan dapatkan data pesanan yang dihapus
                        Pesanan pesananDihapus = antrianPesanan.hapusPesananByIndex(pilihan_penghapusan);
                        
                        // Cek apakah berhasil dihapus (pesanan tidak kosong)
                        if (!pesananDihapus.nama_pemesan.empty()) {
                            // Kembalikan stok tiket ke katalog
                            for (auto& d : katalog) {
                                if (d.nama == pesananDihapus.destinasi_dipesan.nama) {
                                    d.stok_tiket += pesananDihapus.jumlah_tiket;
                                    break;
                                }
                            }
                            
                            // Simpan ke undo stack untuk bisa di-restore
                            undoStack.push(pesananDihapus);
                            
                            cout << "✅ Pesanan atas nama " << pesananDihapus.nama_pemesan 
                                 << " ke " << pesananDihapus.destinasi_dipesan.nama 
                                 << " berhasil dihapus!\n";
                        } else {
                            cout << "❌ Gagal menghapus pesanan.\n";
                        }
                    }
                } else {
                    cout << "📭 Tidak ada pesanan yang bisa dihapus.\n";
                }
                pauseLanjut();
                break;
            }

            case 5: {
                  if (!undoStack.isEmpty()) {
                    Pesanan terakhir = undoStack.pop();
                    bool dihapus = antrianPesanan.hapusPesanan(terakhir);
                    if (dihapus) {
                        // Kembalikan stok tiket
                        for (auto& d : katalog) {
                            if (d.nama == terakhir.destinasi_dipesan.nama) {
                                d.stok_tiket += terakhir.jumlah_tiket;
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

            case 6: {
                if (antrianPesanan.isEmpty()) {
                    cout << "📭 Tidak ada pesanan dalam antrian.\n";
                } else {
                    antrianPesanan.tampilkan();
                    cout << "\n🚚 Memproses Semua Antrian Pesanan...\n";
                    while (!antrianPesanan.isEmpty()) {
                        Pesanan p = antrianPesanan.dequeue();
                        for (int i = 0; i < p.jumlah_tiket; i++) {
                            cout << "👤 Pesanan atas nama " << p.nama_pemesan << "untuk destinasi "
                                << p.destinasi_dipesan.nama << " berhasil diproses!" 
                                << " [Tiket ke-" << (i + 1) << "] - "
                                << formatRupiah(p.destinasi_dipesan.harga) << endl;
                        }

                    }
                }
                pauseLanjut();
                break;
            }

            case 0:
                cout << "👋 Terima kasih telah menggunakan aplikasi!\n";
                break;

            default:
                cout << "⚠️  Pilihan tidak valid!\n";
                pauseLanjut();
        }

    } while (pilihan != 0);
        

    return 0;
}
