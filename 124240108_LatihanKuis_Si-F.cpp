#include <iostream>
using namespace std;

const int MAX_MAHASISWA = 100;
struct Mahasiswa
{
    char nama[50], jurusan[50];
    int nim, tahun_masuk;
    float ipk;
};
Mahasiswa dataMahasiswa[MAX_MAHASISWA];
int jumlahMahasiswa = 0;
void tambahMahasiswa()
{
    int jumlah;
    if (jumlahMahasiswa >= MAX_MAHASISWA)
    {
        cout << "Data mahasiswa penuh!" << endl;
        return;
    }
    FILE *file = fopen("MahasiswaData.dat", "ab");
    if (file == nullptr)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    cout << "masukan jumlah mahasiswa = ";
    cin >> jumlah;
    for (int i = 0; i < jumlah; i++)
    {
        Mahasiswa m;
        cout << "\nmahasiswa ke-" << i + 1 << endl;
        cout << "Masukkan Nama: ";
        cin.ignore();
        cin.getline(m.nama, 50);
        cout << "Masukkan NIM: ";
        cin >> m.nim;
        cout << "Masukkan Jurusan: ";
        cin.ignore();
        cin.getline(m.jurusan, 50);
        cout << "Masukkan Tahun Masuk: ";
        cin >> m.tahun_masuk;
        m.ipk = 0.0;
        fwrite(&m, sizeof(Mahasiswa), 1, file);
    }
    fclose(file);
    cout << "Mahasiswa berhasil ditambahkan!\n";
}
int partition(Mahasiswa arr[], int awal, int akhir)
{
    float pivot = arr[akhir].nim;
    int i = (awal - 1);
    for (int j = awal; j < akhir; j++)
    {
        if (arr[j].nim <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[akhir]);
    return (i + 1);
}
void QuickSort(Mahasiswa arr[], int awal, int akhir)
{
    if (awal < akhir)
    {
        int ip = partition(arr, awal, akhir);
        QuickSort(arr, awal, ip - 1);
        QuickSort(arr, ip + 1, akhir);
    }
}
int BinarySearch(Mahasiswa arr[], int n, int x)
{
    int i = 0, j = n - 1, t;
    while (i <= j)
    {
        t = (i + j) / 2;
        if (arr[t].nim == x)
            return t;
        else if (x < arr[t].nim)
            j = t - 1;
        else
            i = t + 1;
    }
    return -1;
}
void tampilkanMahasiswa()
{
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file == nullptr)
    {
        cout << "Tidak ada data mahasiswa!" << endl;
        return;
    }
    Mahasiswa m;
    jumlahMahasiswa = 0;
    while (fread(&m, sizeof(Mahasiswa), 1, file) == 1)
    {
        dataMahasiswa[jumlahMahasiswa++] = m;
    }
    fclose(file);
    QuickSort(dataMahasiswa, 0, jumlahMahasiswa - 1);
    for (int i = 0; i < jumlahMahasiswa; i++)
    {
        cout << "NIM: " << dataMahasiswa[i].nim
             << " | Nama: " << dataMahasiswa[i].nama
             << " | Jurusan: " << dataMahasiswa[i].jurusan
             << " | Tahun Masuk: " << dataMahasiswa[i].tahun_masuk
             << " | IPK: " << dataMahasiswa[i].ipk << endl;
    }
}
void cariMahasiswaNIM()
{
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file == nullptr)
    {
        cout << "Tidak ada data mahasiswa!" << endl;
        return;
    }
    Mahasiswa m;
    jumlahMahasiswa = 0;
    while (fread(&m, sizeof(Mahasiswa), 1, file) == 1)
    {
        dataMahasiswa[jumlahMahasiswa++] = m;
    }
    fclose(file);
    QuickSort(dataMahasiswa, 0, jumlahMahasiswa - 1);
    int nim;
    cout << "Masukkan NIM: ";
    cin >> nim;
    int hasil = BinarySearch(dataMahasiswa, jumlahMahasiswa, nim);
    if (hasil != -1)
    {
        cout << "Mahasiswa ditemukan: " << dataMahasiswa[hasil].nama << " | IPK: " << dataMahasiswa[hasil].ipk << endl;
    }
    else
    {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
    }
}
void cariMahasiswaJurusan()
{
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file == nullptr)
    {
        cout << "Tidak ada data mahasiswa!" << endl;
        return;
    }
    Mahasiswa m;
    char jurusan[50];
    bool found = false;
    cout << "Masukkan jurusan: ";
    cin.ignore();
    cin.getline(jurusan, 50);
    while (fread(&m, sizeof(Mahasiswa), 1, file) == 1)
    {
        string jurusanMahasiswa = m.jurusan;
        if (jurusanMahasiswa == jurusan)
        {
            cout << "NIM: " << m.nim << " | Nama: " << m.nama << " | IPK: " << m.ipk << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Mahasiswa dengan jurusan " << jurusan << " tidak ditemukan!\n";
    fclose(file);
}
void perbaruiIPK()
{
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file == nullptr)
    {
        cout << "Tidak ada data mahasiswa!" << endl;
        return;
    }
    Mahasiswa mhs[MAX_MAHASISWA];
    int jumlah = 0;
    while (fread(&mhs[jumlah], sizeof(Mahasiswa), 1, file) == 1)
    {
        jumlah++;
    }
    fclose(file);
    int nim;
    float ipkBaru;
    bool found = false;
    cout << "Masukkan NIM mahasiswa: ";
    cin >> nim;
    for (int i = 0; i < jumlah; i++)
    {
        if (mhs[i].nim == nim)
        {
            cout << "Mahasiswa ditemukan!\n";
            cout << "Nama: " << mhs[i].nama << " | IPK saat ini: " << mhs[i].ipk << endl;
            cout << "Masukkan IPK baru: ";
            cin >> ipkBaru;
            if (ipkBaru < 0.0 || ipkBaru > 4.0)
            {
                cout << "IPK tidak valid! Harus antara 0.0 - 4.0\n";
                return;
            }
            mhs[i].ipk = ipkBaru;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!\n";
        return;
    }
    file = fopen("MahasiswaData.dat", "wb");
    if (file == nullptr)
    {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }
    fwrite(mhs, sizeof(Mahasiswa), jumlah, file);
    fclose(file);
    cout << "IPK berhasil diperbarui!\n";
}
void hapusMahasiswa()
{
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file == nullptr)
    {
        cout << "Tidak ada data mahasiswa!" << endl;
        return;
    }
    FILE *tempFile = fopen("TempData.dat", "wb");
    if (tempFile == nullptr)
    {
        cout << "Gagal membuat file sementara!" << endl;
        fclose(file);
        return;
    }
    Mahasiswa m;
    int nim;
    bool found = false;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> nim;
    while (fread(&m, sizeof(Mahasiswa), 1, file) == 1)
    {
        if (m.nim == nim)
        {
            found = true;
        }
        else
        {
            fwrite(&m, sizeof(Mahasiswa), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("MahasiswaData.dat");
    rename("TempData.dat", "MahasiswaData.dat");

    if (found)
    {
        cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus!" << endl;
    }
    else
    {
        cout << "Mahasiswa tidak ditemukan!" << endl;
    }
}
int main()
{
    system("cls");
    int pilihan;
    do
    {
        cout << "\n===== SmartCampus++ =====\n";
        cout << "1. Tambah Mahasiswa Baru\n";
        cout << "2. Tampilkan Semua Mahasiswa\n";
        cout << "3. Cari Mahasiswa Berdasarkan NIM\n";
        cout << "4. Cari Mahasiswa Berdasarkan Jurusan\n";
        cout << "5. Perbarui IPK Mahasiswa\n";
        cout << "6. Hapus Mahasiswa\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            tambahMahasiswa();
            system("pause");
            break;
        case 2:
            tampilkanMahasiswa();
            system("pause");
            break;
        case 3:
            cariMahasiswaNIM();
            system("pause");
            break;
        case 4:
            cariMahasiswaJurusan();
            system("pause");
            break;
        case 5:
            perbaruiIPK();
            system("pause");
            break;
        case 6:
            hapusMahasiswa();
            system("pause");
            break;
        case 7:
            cout << "Terima kasih telah menggunakan SmartCampus++!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 7);
    return 0;
}