#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_MENU = 10;
const int MAX_PESANAN = 20;

string menuNama[MAX_MENU] = {
    "Nasi Goreng", "Mie Ayam", "Ayam Bakar", "Sate Ayam",
    "Gado-gado", "Soto Ayam", "Bakso", "Es Teh", "Es Jeruk", "Kopi"
};

double menuHarga[MAX_MENU] = {
    15000, 12000, 20000, 18000,
    10000, 13000, 15000, 5000, 6000, 8000
};

string menuKategori[MAX_MENU] = {
    "Makanan", "Makanan", "Makanan", "Makanan",
    "Makanan", "Makanan", "Makanan", "Minuman", "Minuman", "Minuman"
};

int pesananKode[MAX_PESANAN];
int pesananQty[MAX_PESANAN];
int totalPesanan = 0;

void tampilkanMenu() {
    cout << "\n==========================================" << endl;
    cout << "      MENU RESTORAN The A.R. Excelus" << endl;
    cout << "==========================================" << endl;
    cout << setw(3) << "No" << setw(15) << "Menu" << setw(12) << "Kategori" << setw(10) << "Harga" << endl;
    cout << "------------------------------------------" << endl;

    for(int i = 0; i < MAX_MENU; i++) {
        cout << setw(3) << i+1 << setw(15) << menuNama[i]
             << setw(12) << menuKategori[i]
             << setw(10) << menuHarga[i] << endl;
    }
    cout << "==========================================" << endl;
}

void tambahPesanan() {
    int kode, qty;

    cout << "\n--- TAMBAH PESANAN ---" << endl;
    cout << "Masukkan kode menu (1-" << MAX_MENU << "): ";
    cin >> kode;

    if(kode < 1 || kode > MAX_MENU) {
        cout << "Kode menu tidak valid!" << endl;
        return;
    }

    cout << "Masukkan Jumlah: ";
    cin >> qty;

    if(qty <= 0) {
        cout << "Jumlah harus lebih dari 0!" << endl;
        return;
    }

    bool sudahAda = false;
    for(int i = 0; i < totalPesanan; i++) {
        if(pesananKode[i] == kode) {
            pesananQty[i] += qty;
            sudahAda = true;
            cout << "Jumlah untuk " << menuNama[kode-1] << " ditambah menjadi " << pesananQty[i] << endl;
            break;
        }
    }

    if(!sudahAda && totalPesanan < MAX_PESANAN) {
        pesananKode[totalPesanan] = kode;
        pesananQty[totalPesanan] = qty;
        totalPesanan++;
        cout << menuNama[kode-1] << " sebanyak " << qty << " porsi berhasil ditambahkan!" << endl;
    } else if(totalPesanan >= MAX_PESANAN) {
        cout << "Maaf, maksimal pesanan adalah " << MAX_PESANAN << " jenis menu!" << endl;
    }
}

void tampilkanPesanan() {
    if(totalPesanan == 0) {
        cout << "\nBelum ada pesanan!" << endl;
        return;
    }

    cout << "\n==========================================" << endl;
    cout << "           PESANAN SEMENTARA" << endl;
    cout << "==========================================" << endl;
    cout << setw(3) << "No" << setw(15) << "Menu" << setw(10) << "Qty" << setw(12) << "Subtotal" << endl;
    cout << "------------------------------------------" << endl;

    double total = 0;
    for(int i = 0; i < totalPesanan; i++) {
        int kode = pesananKode[i];
        int qty = pesananQty[i];
        double subtotal = menuHarga[kode-1] * qty;
        total += subtotal;

        cout << setw(3) << i+1 << setw(15) << menuNama[kode-1]
             << setw(10) << qty
             << setw(12) << subtotal << endl;
    }

    cout << "------------------------------------------" << endl;
    cout << setw(28) << "Total: " << setw(12) << total << endl;
    cout << "==========================================" << endl;
}

void cetakStruk() {
    if(totalPesanan == 0) {
        cout << "\nTidak ada pesanan untuk dicetak!" << endl;
        return;
    }

    double subtotal = 0;
    double pajak, totalBayar, bayar, kembalian;

    for(int i = 0; i < totalPesanan; i++) {
        int kode = pesananKode[i];
        subtotal += menuHarga[kode-1] * pesananQty[i];
    }

    pajak = subtotal * 0.1;
    totalBayar = subtotal + pajak;

    cout << "\n===================================================" << endl;
    cout << "                STRUK PEMBAYARAN" << endl;
    cout << "===================================================" << endl;
    cout << setw(15) << "Menu" << setw(10) << "Qty" << setw(12) << "Harga" << setw(12) << "Subtotal" << endl;
    cout << "----------------------------------------------------" << endl;

    for(int i = 0; i < totalPesanan; i++) {
        int kode = pesananKode[i];
        cout << setw(15) << menuNama[kode-1]
             << setw(10) << pesananQty[i]
             << setw(12) << menuHarga[kode-1]
             << setw(12) << menuHarga[kode-1] * pesananQty[i] << endl;
    }

    cout << "---------------------------------------------------" << endl;
    cout << setw(37) << "Subtotal: " << setw(12) << subtotal << endl;
    cout << setw(37) << "Pajak (10%): " << setw(12) << pajak << endl;
    cout << setw(37) << "Total Bayar: " << setw(12) << totalBayar << endl;

    cout << "\nMasukkan jumlah uang pembayaran: ";
    cin >> bayar;

    if(bayar < totalBayar) {
        cout << "Uang pembayaran kurang! Kurang: " << (totalBayar - bayar) << endl;
        return;
    }

    kembalian = bayar - totalBayar;

    cout << setw(37) << "Bayar: " << setw(12) << bayar << endl;
    cout << setw(37) << "Kembalian: " << setw(12) << kembalian << endl;
    cout << "==========================================" << endl;
    cout << "      TERIMA KASIH ATAS KUNJUNGANNYA!" << endl;
    cout << "==========================================" << endl;

    totalPesanan = 0;
}

void hapusPesanan() {
    if(totalPesanan == 0) {
        cout << "\nBelum ada pesanan!" << endl;
        return;
    }

    tampilkanPesanan();
    int nomor;
    cout << "\nMasukkan nomor pesanan yang akan dihapus (1-" << totalPesanan << "): ";
    cin >> nomor;

    if(nomor < 1 || nomor > totalPesanan) {
        cout << "Nomor pesanan tidak valid!" << endl;
        return;
    }

    int index = nomor - 1;
    cout << "Pesanan " << menuNama[pesananKode[index]-1] << " dihapus!" << endl;

    for(int i = index; i < totalPesanan - 1; i++) {
        pesananKode[i] = pesananKode[i+1];
        pesananQty[i] = pesananQty[i+1];
    }

    totalPesanan--;
}

int main() {
    int pilihan;

    cout << "==========================================" << endl;
    cout << "     APLIKASI KASIR RESTORAN SEDERHANA" << endl;
    cout << "==========================================" << endl;

    do {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Tampilkan Menu" << endl;
        cout << "2. Tambah Pesanan" << endl;
        cout << "3. Tampilkan Pesanan" << endl;
        cout << "4. Hapus Pesanan" << endl;
        cout << "5. Cetak Struk" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                tampilkanMenu();
                break;
            case 2:
                tambahPesanan();
                break;
            case 3:
                tampilkanPesanan();
                break;
            case 4:
                hapusPesanan();
                break;
            case 5:
                cetakStruk();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan aplikasi!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while(pilihan != 0);

    return 0;
}

