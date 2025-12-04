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