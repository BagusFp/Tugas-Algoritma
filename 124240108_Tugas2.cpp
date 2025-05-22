#include <iostream>
#include <string>
using namespace std;
struct Pesanan
{
    string nama;
    string jenisRoti;
    double totalHarga;
};
struct Node
{
    Pesanan data;
    Node *next;
};
Node *front = nullptr;
Node *rear = nullptr;
Node *top = nullptr;
void enqueue(string nama, string jenisRoti, double totalHarga)
{
    Node *newNode = new Node;
    newNode->data.nama = nama;
    newNode->data.jenisRoti = jenisRoti;
    newNode->data.totalHarga = totalHarga;
    newNode->next = nullptr;
    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Pesanan atas nama " << nama << " ditambahkan ke antrean.\n";
}
Pesanan dequeue()
{
    if (front == nullptr)
    {
        cout << "Antrean kosong!\n";
    }
    Node *temp = front;
    Pesanan data = temp->data;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
    return data;
}
void cancelLast()
{
    if (rear == nullptr)
    {
        cout << "Antrean kosong, tidak ada pesanan untuk dibatalkan!\n";
        return;
    }
    if (front == rear)
    {
        delete front;
        front = rear = nullptr;
        cout << "Pesanan terakhir dibatalkan.\n";
        return;
    }
    Node *current = front;
    while (current->next != rear)
    {
        current = current->next;
    }
    delete rear;
    rear = current;
    rear->next = nullptr;
    cout << "Pesanan terakhir dibatalkan.\n";
}
void displayQueue()
{
    if (front == nullptr)
    {
        cout << "Antrean kosong.\n";
        return;
    }
    cout << "\nDaftar Pesanan dalam Antrean:\n";
    cout << "----------------------------------------------------------\n";
    Node *current = front;
    int index = 1;
    while (current != nullptr)
    {
        cout << index << ". Nama: " << current->data.nama
             << ", Jenis Roti: " << current->data.jenisRoti
             << ", Total Harga: Rp" << current->data.totalHarga << "\n";
        current = current->next;
        index++;
    }
    cout << "----------------------------------------------------------\n";
}
bool isQueueEmpty()
{
    return front == nullptr;
}
void push(Pesanan pesanan)
{
    Node *newNode = new Node;
    newNode->data = pesanan;
    newNode->next = top;
    top = newNode;
}

void displayHistory()
{
    if (top == nullptr)
    {
        cout << "Riwayat pesanan kosong.\n";
        return;
    }
    cout << "\nRiwayat Pesanan yang Sudah Dilayani:\n";
    cout << "----------------------------------------------------------\n";
    Node *current = top;
    int index = 1;
    while (current != nullptr)
    {   
        cout << index << ". Nama: " << current->data.nama
             << ", Jenis Roti: " << current->data.jenisRoti
             << ", Total Harga: Rp" << current->data.totalHarga << "\n";
        current = current->next;
        index++;
    }
    cout << "----------------------------------------------------------\n";
}
int main()
{
    int pilihan;
    string nama, jenisRoti;
    double totalHarga;
    do
    {
        cout << "\n=== Sistem Manajemen Pesanan Toko Roti Manis Lezat ===\n";
        cout << "1. Ambil Antrean\n";
        cout << "2. Layani Pembeli\n";
        cout << "3. Tampilkan Pesanan\n";
        cout << "4. Batalkan Pesanan\n";
        cout << "5. Tampilkan History Pesanan\n";
        cout << "6. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan nama pelanggan: ";
            getline(cin, nama);
            cout << "Masukkan jenis roti: ";
            getline(cin, jenisRoti);
            cout << "Masukkan total harga: Rp";
            cin >> totalHarga;
            enqueue(nama, jenisRoti, totalHarga);
            break;
        case 2:
            if (!isQueueEmpty())
            {
                Pesanan pesanan = dequeue();
                push(pesanan);
                cout << "Pesanan atas nama " << pesanan.nama << " telah dilayani.\n";
            }
            else
            {
                cout << "Antrean kosong!\n";
            }
            break;
        case 3:
            displayQueue();
            break;

        case 4:
            cancelLast();
            break;

        case 5:
            displayHistory();
            break;
        case 6:
            cout << "Terima kasih telah menggunakan sistem ini!\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);
    return 0;
}