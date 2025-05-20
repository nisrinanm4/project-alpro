#include <iostream>
#include <iomanip>
using namespace std;

const int BIOSKOP = 100; 

struct film{
    char judul[100];
    int tahun;
    string type;
    string genre;
    int rating;
};

// Array tipe genre yang valid
string genre[4] = {"horor", "komedi", "action", "romance"};

film daftarFilm[BIOSKOP];
int jumlahFilm = 0;

//pointer mengecek jenis genre
bool cekgenreValid(string type){
    string *ptr = genre;
    for (int i = 0; i < 4; i++){
        if (*(ptr + i) == type){
            return true;
        }
    }
    return false;
}

bool kembaliKeMenu() {
    char pilihan;
    cout << "\nBalik ke menu? (y/n): ";
    cin >> pilihan;
    return (pilihan == 'y' || pilihan == 'Y');
}

//Fungsi Menampilkan Menu
void tampilkanMenu(){
        cout << "\n"
             << "=== MENU BIOSKOP ===\n"
             << "1. Tambah Film\n"
             << "2. Tampilkan Rating Film Dari Yang Terendah\n"
             << "3. Tampilkan Rating Film Dari Yang Tertinggi\n"
             << "4. Cari Data Film\n"
             << "5. Hapus Data Film\n"
             << "6. Keluar\n"
             << "Pilih menu: ";
}

// Fungsi FILE Menyimpan data film
void simpanDataFilm(){
    FILE* file = fopen("data_film.txt", "w");
    if(file == NULL) {
        cout << "Gagal membuka file." << endl;
        return;
    }

    for (int i = 0; i < jumlahFilm; i++) {
        fprintf(file, "%s,%d,%s,%d\n",
                daftarFilm[i].judul,
                daftarFilm[i].tahun,
                daftarFilm[i].genre,
                daftarFilm[i].rating);
    }

    fclose(file);
    cout << "Data film berhasil disimpan ke file." << endl;
}

// Fungsi FILE Menampilkan data Film
void fileTampilkanFilm(){
    FILE *file = fopen("data_film.txt", "r");
    if (file == nullptr) {
        cout << "Gagal membuka file!\n";
        return;
    }

    film daftarFilm[BIOSKOP];  
    int jumlahFilm = 0;  

    film f;
    char line[200];
    
    while (fgets(line, sizeof(line), file) && jumlahFilm < BIOSKOP) {
        if (sscanf(line, "%[^,],%d,%[^,],%d", f.judul, f.tahun, f.genre, &f.rating) == 4) {
            daftarFilm[jumlahFilm] = f;  
            jumlahFilm++;
        }
    }
    
    fclose(file);
}

// fungsi menambahkan film
void tambahFilm(){
    FILE *file = fopen("data_film.txt", "a");
    if (file == nullptr) {
        cout << "Gagal membuka file!\n";
        return;
    }

    film newFilm;
    cout << endl;
    cout << "Judul Film : "; 
    cin.ignore();
    cin.getline(newFilm.judul, 100);

    cout << "Tahun Film : "; 
    cin >> newFilm.tahun;

    cin.ignore();
    cout << "Genre : ";
    getline(cin, newFilm.genre); 

    // Validasi tipe pasukan
    if (!cekgenreValid(newFilm.genre)) {
        cout << "Error: Genre Film tidak valid. Harus salah satu dari: horor, komedi, action, romance." << endl;
        return;
    }

    cout << "Rating Film : "; 
    cin >> newFilm.rating;

    // Tambahkan batalyon ke array
    daftarFilm[jumlahFilm] = newFilm;
    jumlahFilm++;
    simpanDataFilm();
}

// Tampilkan Data Film Bubble Sort Secara Ascending
void bubbleSortAscending(film daftarFilm[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftarFilm[j].rating > daftarFilm[j + 1].rating) {  
                film temp = daftarFilm[j];
                daftarFilm[j] = daftarFilm[j + 1];
                daftarFilm[j + 1] = temp;
            }
        }
    }
}

void tampilkanRatingFilmAscending(){
    if (jumlahFilm == 0) {
        cout << "Belum ada data film." << endl;
        return;
    }

    bubbleSortAscending(daftarFilm, jumlahFilm);

    
    cout << setw(20) << left << "Judul" 
         << setw(10) << "Tahun" 
         << setw(15) << "Genre" 
         << setw(10) << "Rating" << endl;
    cout << string(55, '=') << endl;

    for (int i = 0; i < jumlahFilm; i++) {
        cout << left 
             << setw(20) << daftarFilm[i].judul
             << setw(10) << daftarFilm[i].tahun
             << setw(15) << daftarFilm[i].genre 
             << setw(10)  << daftarFilm[i].rating
             << endl;
    }
    cout << string(55, '=') << endl;
    if (!kembaliKeMenu()) {
        exit(0); // Keluar dari program jika pengguna tidak ingin kembali
    }
    fileTampilkanFilm();
}

// Tampilkan Data Film Bubble Sort Secara Descending
void bubbleSortDescending(film daftarFilm[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftarFilm[j].rating < daftarFilm[j + 1].rating) {  
                film temp = daftarFilm[j];
                daftarFilm[j] = daftarFilm[j + 1];
                daftarFilm[j + 1] = temp;
            }
        }
    }
}

void tampilkanRatingFilmDescending(){
    if (jumlahFilm == 0) {
        cout << "Belum ada data film." << endl;
        return;
    }

    bubbleSortDescending(daftarFilm, jumlahFilm);

    cout << setw(20) << left << "Judul" 
         << setw(10) << "Tahun" 
         << setw(15) << "Genre" 
         << setw(10) << "Rating" << endl;
    cout << string(55, '=') << endl;

    for (int i = 0; i < jumlahFilm; i++) {
        cout << left 
             << setw(20) << daftarFilm[i].judul
             << setw(10) << daftarFilm[i].tahun
             << setw(15) << daftarFilm[i].genre 
             << setw(10) << daftarFilm[i].rating
             << endl;
    }
    cout << string(55, '=') << endl;

    if (!kembaliKeMenu()) {
        exit(0); // Keluar dari program jika pengguna tidak ingin kembali
    }

    fileTampilkanFilm();
}


int main(){

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
    
    switch (pilihan) {
            case 1: 
                tambahFilm();
                break;
            case 2:
                tampilkanRatingFilmAscending();
                break;
            case 3:
                tampilkanRatingFilmDescending();
                break;
            case 4:
                break;
            case 5:{
                
                break;
            }
            case 6:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                system("pause");
        }
}while (pilihan != 6);
}
