# 🧩 Mata Kuliah: Struktur Data  
**Proyek Akhir – Katalog Wisata & Pemesanan Paket Liburan**  
**Paralel P4 – Kelompok 3**

---

## 👥 Anggota Kelompok
- **Afif Fakhri Muhammad** – G6401231007  
- **Tsabitha Naylasafa Aurora** – G6401231036  
- **Jason Bagaskara Mulyono** – G6401231088  

---

## 📌 Deskripsi Singkat  
Program ini merupakan simulasi sistem **katalog destinasi wisata dan pemesanan paket liburan** berbasis terminal menggunakan C++.  
User dapat melihat katalog, memesan destinasi, menggunakan kode diskon, serta membatalkan dan memproses pesanan menggunakan struktur data yang efisien.

---

## 🎯 Fitur Utama

- 📖 **Lihat Katalog Destinasi**  
  Menampilkan daftar destinasi liburan yang tersimpan dalam vector, dapat diurutkan berdasarkan nama, negara, atau harga.

- ➕ **Tambah Pesanan**  
  User dapat memilih destinasi untuk ditambahkan ke daftar pesanan.

- 💸 **Masukkan Kode Diskon**  
  User dapat memasukkan kode diskon yang disimpan dalam hash table.

- 📋 **Lihat Daftar Pesanan**  
  Menampilkan semua pesanan yang telah dibuat, dalam urutan pemesanan.

- 🗑️ **Hapus Pesanan**  
  Menghapus pesanan dari antrian jika tidak jadi dipesan.

- ↩️ **Undo Pesanan Terakhir**  
  Mengembalikan pesanan terakhir yang ditambah atau dihapus menggunakan stack.

- ✅ **Proses Semua Pesanan**  
  Memproses seluruh pesanan dalam queue dan menampilkan ringkasan konfirmasi.

---

## 🧠 Struktur Data yang Digunakan

| Fitur Utama                  | Struktur Data yang Digunakan          | Penjelasan                                                                 |
|-----------------------------|---------------------------------------|----------------------------------------------------------------------------|
| Katalog Destinasi           | `vector` + Insertion Sort             | Menyimpan data destinasi secara dinamis dan efisien, serta mudah diurutkan.|
| Menambah & Melihat Pesanan  | `queue`                               | Menjamin urutan pemesanan (FIFO).                                         |
| Undo Pesanan Terakhir       | `stack`                               | Menyimpan riwayat pesanan untuk dibatalkan (LIFO).                        |
| Kode Diskon                 | `unordered_map` (Hash Table)          | Memungkinkan pencarian diskon cepat dengan kompleksitas rata-rata O(1).   |

---

## 🔁 Alur Umum Sistem

1. User masuk ke **Dashboard**.
2. Melihat **Katalog Destinasi**.
3. Menambahkan destinasi ke **daftar pesanan**.
4. (Opsional) Memasukkan **kode diskon**.
5. Melihat daftar pesanan
6. Menghapus pesanan.
7. **Undo** pesanan terakhir
8. Memproses semua pesanan
9. Keluar dari program.

---

## 🛠️ Teknologi & Bahasa
- Bahasa Pemrograman: **C++**

---

## ▶️ Cara Menjalankan

1. Clone repositori ini:
   ```bash
   git clone https://github.com/jasonbagaskaraa/Manajemen-Destinasi-Wisata/blob/main/main.cpp
