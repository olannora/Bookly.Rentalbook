#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

// Struktur data untuk buku
struct Buku {
    int id;
    string judul;
    string penulis;
    int tahunTerbit;
    string penerbit;
    string status; // tersedia atau dipinjam
};

// Struktur data untuk pelanggan
struct Pelanggan {
    int id;
    string nama;
    string email;
    string noTelepon;
    string password;
    vector<int> pinjaman; // daftar ID buku yang dipinjam
    double denda;
    vector<string> logPeminjaman; // log peminjaman dan pengembalian
};

// Struktur data untuk admin
struct Admin {
    string username;
    string password;
};

// Database simulasi
vector<Buku> daftarBuku;
vector<Pelanggan> daftarPelanggan;
Admin admin = {"admin", "admin123"}; // default admin

// Fungsi mendapatkan waktu sekarang dalam bentuk string
string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string waktu(dt);
    return waktu.substr(0, waktu.size() - 1); // Menghilangkan karakter newline
}

// Fungsi inisialisasi buku awal
void inisialisasiBuku() {
    Buku buku1 = {1, "Valorant", "Zakhrova", 2020, "Gramedia", "tersedia"};
    Buku buku2 = {2, "Buried Shadow", "Annora Farah", 2018, "Gramedia", "tersedia"};
    Buku buku3 = {3, "Cincin", "Ninda Alifa", 2021, "Gramedia", "tersedia"};
    daftarBuku.push_back(buku1);
    daftarBuku.push_back(buku2);
    daftarBuku.push_back(buku3);
    cout << "Haloo Halooo temen-temen semuaa celamat datang di Bookly hihii.\n";
}

// Fungsi pendaftaran pelanggan
void tambahPelanggan() {
    Pelanggan pelanggan;
    cout << "Masukin ID mu dongg;): ";
    cin >> pelanggan.id;
    cout << "Masukin nama mu jugaa yaaa hihi: ";
    cin.ignore();
    getline(cin, pelanggan.nama);
    cout << "Eh email kamuu?: ";
    cin >> pelanggan.email;
    cout << "Sama nomer telponn yahh: ";
    cin >> pelanggan.noTelepon;
    cout << "Biar gada yg tau, janlup masukin password: ";
    cin >> pelanggan.password;
    pelanggan.denda = 0;
    daftarPelanggan.push_back(pelanggan);
    cout << "Yeyy pendaftaran berhasill.\n";
}

// Fungsi login pelanggan
Pelanggan* loginPelanggan() {
    int id;
    string password;
    cout << "Id kamuu: ";
    cin >> id;
    cout << "Sama password: ";
    cin >> password;
    for (auto &pelanggan : daftarPelanggan) {
        if (pelanggan.id == id && pelanggan.password == password) {
            cout << "Ciehh login berhasill.\n";
            return &pelanggan;
        }
    }
    cout << "Yahh login gagal, coba diinget-inget lagii yg salah apa.\n";
    return nullptr;
}

// Fungsi login admin
bool loginAdmin() {
    string username, password;
    cout << "Infoo username adminn: ";
    cin >> username;
    cout << "Minn password minnn: ";
    cin >> password;
    if (username == admin.username && password == admin.password) {
        cout << "Yeyyy login berhasil niehh min.\n";
        return true;
    }
    cout << "Yah min loginnya masih gagall, coba lagii.\n";
    return false;
}

// Fungsi menampilkan daftar buku
void tampilkanBuku() {
    cout << "\nDaftar Bukuu:\n";
    for (const auto &buku : daftarBuku) {
        cout << "ID: " << buku.id << " | Judulnya?: " << buku.judul 
             << " | Penulis bukuu: " << buku.penulis 
             << " | Statusnya??: " << buku.status << "\n";
    }
}

// Fungsi memilih buku
void pilihBuku(Pelanggan &pelanggan) {
    int idBuku;
    tampilkanBuku();
    cout << "Masukkan ID bukunya yg mau dipinjem yaah: ";
    cin >> idBuku;
    for (auto &buku : daftarBuku) {
        if (buku.id == idBuku && buku.status == "oii tersedia") {
            pelanggan.pinjaman.push_back(idBuku);
            pelanggan.logPeminjaman.push_back("Meminjam buku ID " + to_string(idBuku) + " pada " + getCurrentTime());
            buku.status = "dipinjam";
            cout << "Buku berhasil dipinjam nichhh.\n";
            return;
        }
    }
    cout << "Yahh Buku tidak tersedia gaiss atau ID kamu yg salah huhuu.\n";
}

// Fungsi pembayaran denda
void pembayaranDenda(Pelanggan &pelanggan) {
    if (pelanggan.denda > 0) {
        cout << "Total denda Kamu: Rp" << pelanggan.denda << "\n";
        double jumlah;
        cout << "Masukkan jumlah pembayaran dongg (ketik 50 untuk 50% atau 100 untuk 100%): ";
        cin >> jumlah;
        if (jumlah == 50) {
            pelanggan.denda *= 0.5;
            cout << "Pembayaran 50% berhasil ciee. Sisa denda Anda: Rp" << pelanggan.denda << "\n";
        } else if (jumlah == 100) {
            pelanggan.denda = 0;
            cout << "Denda lunass. Terima kasih yaa. Semoga rejekinya diperluas Aaamiin\n";
        } else {
            cout << "Jumlah pembayaranmu tidak valid boyy.\n";
        }
    } else {
        cout << "Yeyyy, tepat waktu jadi gausah bayar dendaa.\n";
    }
}

// Fungsi pengembalian buku
void kembalikanBuku(Pelanggan &pelanggan) {
    int idBuku;
    cout << "Masukkan ID bukumu yang mau dikembalikan yaa: ";
    cin >> idBuku;
    for (auto it = pelanggan.pinjaman.begin(); it != pelanggan.pinjaman.end(); ++it) {
        if (*it == idBuku) {
            pelanggan.pinjaman.erase(it);
            pelanggan.logPeminjaman.push_back("Mengembalikan buku ID " + to_string(idBuku) + " pada " + getCurrentTime());
            for (auto &buku : daftarBuku) {
                if (buku.id == idBuku) {
                    buku.status = "uhuyy tersedia";
                    cout << "Celamatt Buku kamu berhasil dikembalikann.\n";
                    pelanggan.denda += 10; // Simulasi denda Rp10
                    return;
                }
            }
        }
    }
    cout << "Yahh,ID bukunya ga ada di daftar pinjaman, coba ulang.\n";
}

// Fungsi cek denda
void cekDenda(const Pelanggan &pelanggan) {
    cout << "Total denda kamu segini nihh:(): Rp" << pelanggan.denda << "\n";
}

// Fungsi menampilkan profil pelanggan
void tampilkanProfil(const Pelanggan &pelanggan) {
    cout << "\nProfil Kamuu ciehh:\n";
    cout << "ID: " << pelanggan.id << "\nNamamuu: " << pelanggan.nama 
         << "\nEmail: " << pelanggan.email << "\nNomer Telepon: " << pelanggan.noTelepon << "\n";
    cout << "Log Aktivitas:\n";
    for (const auto &log : pelanggan.logPeminjaman) {
        cout << log << "\n";
    }
}

// Fungsi utama untuk menu admin
void menuAdmin() {
    int pilihan;
    do {
        cout << "\n=== Menu Admin ===\n";
        cout << "1. Tampilkan Buku\n2. Tambahkan Buku Baru\n3. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
            tampilkanBuku();
        } else if (pilihan == 2) {
            Buku buku;
            cout << "Masukkan ID buku: ";
            cin >> buku.id;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, buku.judul);
            cout << "Masukkan penulis buku: ";
            getline(cin, buku.penulis);
            cout << "Masukkan tahun terbit buku: ";
            cin >> buku.tahunTerbit;
            cout << "Masukkan penerbit buku: ";
            cin.ignore();
            getline(cin, buku.penerbit);
            buku.status = "tersedia";
            daftarBuku.push_back(buku);
            cout << "Buku baru berhasil ditambahkan.\n";
        }
    } while (pilihan != 3);
}

// Fungsi utama
int main() {
    inisialisasiBuku();
    int pilihan;
    do {
        cout << "\n=== Pilihan di Bookly ===\n";
        cout << "1. Buat akun kamu yaa\n2. Janlup Login\n3. Login Admin\n4. Yahh, Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tambahPelanggan();
        } else if (pilihan == 2) {
            Pelanggan *pelanggan = loginPelanggan();
            if (pelanggan) {
                int subPilihan;
                do {
                    cout << "\n=== Menu Pelanggan ===\n";
                    cout << "1. Daftar Buku\n2. Pilih Buku duluu\n3. Pengembalian Buku\n4. Cek Denda\n5. Pembayaran Denda\n6. Profilmu\n7. Keluar\n";
                    cout << "Pilihan: ";
                    cin >> subPilihan;

                    if (subPilihan == 1) tampilkanBuku();
                    else if (subPilihan == 2) pilihBuku(*pelanggan);
                    else if (subPilihan == 3) kembalikanBuku(*pelanggan);
                    else if (subPilihan == 4) cekDenda(*pelanggan);
                    else if (subPilihan == 5) pembayaranDenda(*pelanggan);
                    else if (subPilihan == 6) tampilkanProfil(*pelanggan);
                } while (subPilihan != 7);
            }
        } else if (pilihan == 3) {
            if (loginAdmin()) {
                menuAdmin();
            }
        }
    } while (pilihan != 4);

    cout << "Terimakasii teman-temann udah mau mampir di Bookly.\n";
    return 0;
}
