#include <iostream>
using namespace std;
struct Mahasiswa
{
    string nama;
    int nim;
    float ipk;
};
void TampilkanMahasiswa(Mahasiswa *mhs, int n)
{
    cout << "Daftar mahasiswa:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nName: " << mhs[i].nama << "\t";
        cout << "NIM : " << mhs[i].nim << "\t";
        cout << "IPK : " << mhs[i].ipk << "\t";
    }
    cout << endl;
}
int SequentialSearch(Mahasiswa *mhs, int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (mhs[i].nim == x)
            return i;
    }
    return -1;
}
int partitionNama(Mahasiswa *mhs, int awal, int akhir)
{
    string pivot = mhs[akhir].nama;
    int i = (awal - 1);
    for (int j = awal; j < akhir; j++)
    {
        if (mhs[j].nama < pivot)
        {
            i++;
            swap(mhs[i], mhs[j]);
        }
    }
    swap(mhs[i + 1], mhs[akhir]);
    return (i + 1);
}
void QuickSortNama(Mahasiswa *mhs, int awal, int akhir)
{
    if (awal < akhir)
    {
        int ip = partitionNama(mhs, awal, akhir);
        QuickSortNama(mhs, awal, ip - 1);
        QuickSortNama(mhs, ip + 1, akhir);
    }
}
int BinarySearchNama(Mahasiswa *mhs, int n, string x)
{
    int i = 0, j = n - 1, t;
    bool found = false;
    while ((!found) && (i <= j))
    {
        t = (i + j) / 2;
        if (mhs[t].nama == x)
            found = true;
        else if (x < mhs[t].nama)
            j = t - 1;
        else
            i = t + 1;
    }
    return found ? t : -1;
}
void BubbleSort(Mahasiswa *mhs, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (mhs[j].ipk < mhs[j + 1].ipk)
            {
                swap(mhs[j], mhs[j + 1]);
            }
        }
    }
}
int partition(Mahasiswa *mhs, int awal, int akhir)
{
    float pivot = mhs[akhir].ipk;
    int i = (awal - 1);
    for (int j = awal; j < akhir; j++)
    {
        if (mhs[j].ipk < pivot)
        {
            i++;
            swap(mhs[i], mhs[j]);
        }
    }
    swap(mhs[i + 1], mhs[akhir]);
    return (i + 1);
}
void QuickSort(Mahasiswa *mhs, int awal, int akhir)
{
    if (awal < akhir)
    {
        int ip = partition(mhs, awal, akhir);
        QuickSort(mhs, awal, ip - 1);
        QuickSort(mhs, ip + 1, akhir);
    }
}
int main()
{
    Mahasiswa mhs[11] = {
        {"Antony", 124240001, 3.99},
        {"Mudryk", 124240002, 3.98},
        {"Cris", 124240003, 3.7},
        {"Mesi", 124240004, 3.8},
        {"Onana", 124240005, 3.9},
        {"White", 124240006, 3.4},
        {"Nunez", 124240007, 3.3},
        {"Raspord", 124240008, 3.2},
        {"Reus", 124240009, 3.1},
        {"Dg", 124240010, 3.0},
        {"Yamal", 124240010, 2.5}};
    int pilihan, cariNIM;
    string cariNama;
    do
    {
        cout << "\n1. Tampilkan mahasiswa\n"
             << "2. Cari berdasarkan NIM\n"
             << "3. Cari berdasarkan nama\n"
             << "4. Sort IPK mahasiswa (asc)\n"
             << "5. Sort IPK mahasiswa (desc)\n"
             << "6. Exit\n"
             << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 1:
            system("cls");
            TampilkanMahasiswa(mhs, 11);
            cout << endl;
            system("pause");
            break;
        case 2:
            int indexNIM;
            cout << "Masukkan NIM: ";
            cin >> cariNIM;
            indexNIM = SequentialSearch(mhs, 11, cariNIM);
            if (indexNIM != -1)
                cout << "Mahasiswa ditemukan!\nNama: " << mhs[indexNIM].nama << "\nNIM: " << mhs[indexNIM].nim << "\nIPK: " << mhs[indexNIM].ipk << endl;
            else
                cout << "Mahasiswa tidak ditemukan.\n";
            system("pause");
            break;
        case 3:
            QuickSortNama(mhs, 0, 10);
            cout << "Masukkan Nama: ";
            getline(cin, cariNama);
            int indexNama;
            indexNama = BinarySearchNama(mhs, 11, cariNama);
            if (indexNama != -1)
                cout << "Mahasiswa ditemukan!\nNama: " << mhs[indexNama].nama << "\nNIM: " << mhs[indexNama].nim << "\nIPK: " << mhs[indexNama].ipk << endl;
            else
                cout << "Mahasiswa tidak ditemukan.\n";
            system("pause");
            break;
        case 4:
            system("cls");
            QuickSort(mhs, 0, 10);
            cout << "Data telah diurutkan (Ascending)\n";
            TampilkanMahasiswa(mhs, 11);
            system("pause");
            break;
        case 5:
            system("cls");
            BubbleSort(mhs, 11);
            cout << "Data telah diurutkan (Descending)\n";
            TampilkanMahasiswa(mhs, 11);
            system("pause");
            break;
        }
    } while (pilihan != 6);

    return 0;
}
