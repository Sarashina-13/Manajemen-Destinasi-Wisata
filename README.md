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
Program ini merupakan simulasi sistem **katalog wisata dan pemesanan paket liburan** berbasis terminal menggunakan C++.  
User dapat melihat katalog, menambah dan menghapus pesanan, serta memproses pesanan dengan struktur data yang efisien dan sederhana.

---

## 🎯 Fitur Utama

- 📖 **Melihat Katalog Destinasi**  
  Menampilkan daftar destinasi liburan, dapat diurutkan berdasarkan harga atau rating.

- ➕ **Menambah Pesanan**  
  User dapat memilih destinasi dan menambahkannya ke dalam daftar pesanan.

- 📋 **Melihat Daftar Pesanan**  
  Menampilkan semua pesanan yang telah dibuat oleh user.

- 🗑️ **Hapus Pesanan**  
  User dapat menghapus pesanan dari daftar jika berubah pikiran.

- ↩️ **Undo Pesanan Terakhir**  
  Mengembalikan pesanan terakhir yang dihapus (fitur undo).

- ✅ **Memproses Semua Pesanan**  
  Semua pesanan dalam antrian akan diproses secara berurutan dan sistem memberikan konfirmasi.

---

## 🧠 Struktur Data yang Digunakan

| Fitur Utama                  | Struktur Data yang Digunakan          | Penjelasan                                                                 |
|-----------------------------|---------------------------------------|----------------------------------------------------------------------------|
| Melihat Katalog Destinasi   | Array + Insertion Sort                | Karena hanya ada 20 data, insertion sort cukup efisien dan sederhana.     |
| Menambah Pesanan            | Queue                                 | Pesanan dimasukkan ke antrian agar diproses secara FIFO.                  |
| Melihat Daftar Pesanan      | Queue                                 | Menampilkan isi antrian pemesanan.                                        |
| Hapus Pesanan               | Queue + Stack (backup untuk Undo)     | Saat menghapus pesanan, datanya disimpan di stack untuk undo.             |
| Undo Pesanan Terakhir       | Stack                                 | Mengembalikan pesanan terakhir yang dihapus (LIFO).                       |
| Memproses Semua Pesanan     | Queue                                 | Pesanan diproses dari antrian satu per satu sesuai urutan.                |

---

## 🧾 Alur Umum Sistem

1. User membuka program.
2. Program menampilkan katalog destinasi wisata (sudah diurutkan).
3. User menambah destinasi ke daftar pesanan.
4. User dapat melihat atau menghapus pesanan.
5. Jika salah hapus, user bisa melakukan **Undo**.
6. Saat siap, semua pesanan diproses dari antrian.
7. Konfirmasi pemrosesan ditampilkan ke user.

---

## 🛠️ Teknologi & Bahasa
- Bahasa Pemrograman: **C++**
- Paradigma: **Struktur Data**, **Prosedural**

---

## ▶️ Cara Menjalankan

1. Clone repositori ini:
   ```bash
   git clone https://github.com/Sarashina-13/Manajemen-Destinasi-Wisata.git
