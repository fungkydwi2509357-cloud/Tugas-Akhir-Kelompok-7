#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_MENU = 10;
const int MAX_PESANAN = 20;
const double PAJAK = 0.10;

string menuNama[MAX_MENU] = {
    "Nasi Goreng", "Mie Ayam", "Ayam Bakar", "Sate Ayam",
    "Gado-gado", "Soto Ayam", "Bakso", "Es Teh", "Es Jeruk", "Kopi"
};
double menuHarga[MAX_MENU] = {
    15000, 12000, 20000, 18000,
    10000, 13000, 15000, 5000, 6000, 8000
};

int pesananKode[MAX_PESANAN];
int pesananQty[MAX_PESANAN];
int totalPesanan = 0;

double hitungSubtotal() {
    double subtotal = 0;
    for(int i = 0; i < totalPesanan; i++) {
        subtotal += menuHarga[pesananKode[i]-1] * pesananQty[i];
    }
    return subtotal;
}

void tampilkanMenu() {
    cout << "\n=======================================" << "\n";
    cout << "         MENU RESTORAN A.R. Excelus" << "\n";
    cout << "=======================================" << "\n";
    cout << setw(3) << "No" << setw(20) << "Menu" << setw(12) << "Harga" << "\n";
    cout << "---------------------------------------" << "\n";

    for(int i = 0; i < MAX_MENU; i++) {
        cout << setw(3) << i+1 << setw(20) << menuNama[i]
             << setw(12) << menuHarga[i] << "\n";
    }
    cout << "=======================================" << "\n";
}

void tambahPesanan() {
    int kode, qty;
    cout << "\n--- TAMBAH PESANAN ---" << "\n";
    cout << "Kode menu (1-" << MAX_MENU << "): "; cin >> kode;

    if(kode < 1 || kode > MAX_MENU) { cout << "Kode tidak valid!" << "\n"; return; }

    cout << "Jumlah: "; cin >> qty;
    if(qty <= 0) { cout << "Jumlah harus > 0!" << "\n"; return; }

    for(int i = 0; i < totalPesanan; i++) {
        if(pesananKode[i] == kode) {
            pesananQty[i] += qty;
            cout << "Jumlah " << menuNama[kode-1] << " ditambah. Total: " << pesananQty[i] << "\n";
            return;
        }
    }

    if(totalPesanan < MAX_PESANAN) {
        pesananKode[totalPesanan] = kode;
        pesananQty[totalPesanan] = qty;
        totalPesanan++;
        cout << menuNama[kode-1] << " x" << qty << " berhasil ditambahkan!" << "\n";
    } else {
        cout << "Maaf, maksimal " << MAX_PESANAN << " jenis menu!" << "\n";
    }
}

void tampilkanPesanan() {
    if(totalPesanan == 0) { cout << "\nBelum ada pesanan!" << "\n"; return; }

    cout << "\n==========================================" << "\n";
    cout << "            PESANAN SEMENTARA" << "\n";
    cout << "==========================================" << "\n";
    cout << setw(3) << "No" << setw(15) << "Menu" << setw(10) << "Qty" << setw(12) << "Subtotal" << "\n";
    cout << "------------------------------------------" << "\n";

    double total = 0;
    for(int i = 0; i < totalPesanan; i++) {
        int kode = pesananKode[i];
        int qty = pesananQty[i];
        double subtotal = menuHarga[kode-1] * qty;
        total += subtotal;

        cout << setw(3) << i+1 << setw(15) << menuNama[kode-1]
             << setw(10) << qty << setw(12) << subtotal << "\n";
    }

    cout << "------------------------------------------" << "\n";
    cout << setw(28) << "Total: " << setw(12) << total << "\n";
    cout << "==========================================" << "\n";
}

void hapusPesanan() {
    if(totalPesanan == 0) { cout << "\nBelum ada pesanan!" << "\n"; return; }

    tampilkanPesanan();
    int nomor;
    cout << "\nNomor pesanan yang dihapus (1-" << totalPesanan << "): "; cin >> nomor;

    if(nomor < 1 || nomor > totalPesanan) { cout << "Nomor tidak valid!" << "\n"; return; }

    int index = nomor - 1;
    cout << "Pesanan " << menuNama[pesananKode[index]-1] << " dihapus!" << "\n";

    for(int i = index; i < totalPesanan - 1; i++) {
        pesananKode[i] = pesananKode[i+1];
        pesananQty[i] = pesananQty[i+1];
    }
    totalPesanan--;
}

void cetakStruk() {
    if(totalPesanan == 0) { cout << "\nTidak ada pesanan!" << "\n"; return; }

    double subtotal = hitungSubtotal();
    double pajak = subtotal * PAJAK;
    double totalBayar = subtotal + pajak;
    double bayar, kembalian;

    cout << "\n===================================================" << "\n";
    cout << "              STRUK PEMBAYARAN" << "\n";
    cout << "===================================================" << "\n";
    cout << setw(15) << "Menu" << setw(10) << "Qty" << setw(12) << "Harga" << setw(12) << "Subtotal" << "\n";
    cout << "----------------------------------------------------" << "\n";

    for(int i = 0; i < totalPesanan; i++) {
        int kode = pesananKode[i];
        cout << setw(15) << menuNama[kode-1] << setw(10) << pesananQty[i]
             << setw(12) << menuHarga[kode-1] << setw(12) << menuHarga[kode-1] * pesananQty[i] << "\n";
    }

    cout << "---------------------------------------------------" << "\n";
    cout << setw(37) << "Subtotal: " << setw(12) << subtotal << "\n";
    cout << setw(37) << "Pajak (10%): " << setw(12) << pajak << "\n";
    cout << setw(37) << "Total Bayar: " << setw(12) << totalBayar << "\n";

    cout << "\nMasukkan jumlah uang pembayaran: "; cin >> bayar;

    if(bayar < totalBayar) {
        cout << "Uang kurang! Kurang: " << (totalBayar - bayar) << "\n";
        return;
    }

    kembalian = bayar - totalBayar;
    cout << setw(37) << "Bayar: " << setw(12) << bayar << "\n";
    cout << setw(37) << "Kembalian: " << setw(12) << kembalian << "\n";
    cout << "==========================================" << "\n";
    cout << "      TERIMA KASIH ATAS KUNJUNGANNYA!" << "\n";
    cout << "==========================================" << "\n";

    totalPesanan = 0;
}

int main() {
    int pilihan;

    cout << "==========================================" << "\n";
    cout << "      APLIKASI KASIR RESTORAN SEDERHANA" << "\n";
    cout << "==========================================" << "\n";

    do {
        cout << "\n=== MENU UTAMA ===" << "\n"
             << "1. Tampilkan Menu" << "\n"
             << "2. Tambah Pesanan" << "\n"
             << "3. Tampilkan Pesanan" << "\n"
             << "4. Hapus Pesanan" << "\n"
             << "5. Cetak Struk" << "\n"
             << "0. Keluar" << "\n"
             << "Pilihan: ";
        if (!(cin >> pilihan)) {
            cout << "Input tidak valid! Keluar." << "\n";
            break;
        }

        switch(pilihan) {
            case 1: tampilkanMenu(); break;
            case 2: tambahPesanan(); break;
            case 3: tampilkanPesanan(); break;
            case 4: hapusPesanan(); break;
            case 5: cetakStruk(); break;
            case 0: cout << "\nTerima kasih telah menggunakan aplikasi!" << "\n"; break;
            default: cout << "Pilihan tidak valid!" << "\n";
        }
    } while(pilihan != 0);

    return 0;
}