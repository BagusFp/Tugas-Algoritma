#include <iostream>
#include <string>
using namespace std;

// Node untuk pohon biner pencarian (BST)
struct VideoNode {
    string title;
    int duration;
    string status; // "tersedia", "dalam antrean", "sedang diputar"
    VideoNode* left;
    VideoNode* right;
};
// Node untuk playlist (Queue)
struct PlaylistNode {
    string title;
    int duration;
    PlaylistNode* next;
};
// Node for History (Stack)
struct HistoryNode {
    string title;
    int duration;
    HistoryNode* next;
};
// Node untuk Undo (Stack)
struct UndoNode {
    string action; // "add", "delete", "add_playlist", "watch"
    string title;
    int duration;
    string status;
    UndoNode* next;
};
// variabel global
VideoNode* root = nullptr; // BST root
PlaylistNode* playlistHead = nullptr; // Playlist queue
HistoryNode* historyHead = nullptr; // History stack
UndoNode* undoStack = nullptr; // Undo stack
string currentPlaying = ""; // Track current playing video
// Helper functions for BST
VideoNode* createVideoNode(string title, int duration) {
    VideoNode* newNode = new VideoNode;
    newNode->title = title;
    newNode->duration = duration;
    newNode->status = "tersedia";
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
VideoNode* insertBST(VideoNode* node, string title, int duration) {
    if (!node) return createVideoNode(title, duration);
    if (title < node->title) node->left = insertBST(node->left, title, duration);
    else if (title > node->title) node->right = insertBST(node->right, title, duration);
    return node;
}
void displayBST(VideoNode* node) {
    if (node) {
        displayBST(node->left);
        cout << "Judul: " << node->title << ", Durasi: " << node->duration << " menit, Status: " << node->status << endl;
        displayBST(node->right);
    }
}
VideoNode* findVideo(VideoNode* node, string title) {
    if (!node || node->title == title) return node;
    if (title < node->title) return findVideo(node->left, title);
    return findVideo(node->right, title);
}
VideoNode* findMin(VideoNode* node) {
    while (node && node->left) node = node->left;
    return node;
}
VideoNode* deleteBST(VideoNode* node, string title) {
    if (!node) return nullptr;
    if (title < node->title) node->left = deleteBST(node->left, title);
    else if (title > node->title) node->right = deleteBST(node->right, title);
    else {
        if (!node->left) {
            VideoNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            VideoNode* temp = node->left;
            delete node;
            return temp;
        }
        VideoNode* temp = findMin(node->right);
        node->title = temp->title;
        node->duration = temp->duration;
        node->status = temp->status;
        node->right = deleteBST(node->right, temp->title);
    }
    return node;
}
void addToPlaylist(string title) {
    VideoNode* video = findVideo(root, title);
    if (!video) {
        cout << "Video tidak ditemukan!" << endl;
        return;
    }
    if (video->status != "tersedia") {
        cout << "Video sudah ada di playlist atau sedang diputar!" << endl;
        return;
    }
    PlaylistNode* newNode = new PlaylistNode;
    newNode->title = title;
    newNode->duration = video->duration;
    newNode->next = nullptr;
    if (!playlistHead) {
        playlistHead = newNode;
        video->status = "sedang diputar";
        currentPlaying = title;
    } else {
        PlaylistNode* temp = playlistHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        video->status = "dalam antrean";
    }
    UndoNode* undo = new UndoNode;
    undo->action = "add_playlist";
    undo->title = title;
    undo->duration = video->duration;
    undo->status = "tersedia";
    undo->next = undoStack;
    undoStack = undo;
    cout << "Video ditambahkan ke playlist!" << endl;
}
void deletePlaylistNode(string title) {
    PlaylistNode* current = playlistHead;
    PlaylistNode* prev = nullptr;
    while (current && current->title != title) {
        prev = current;
        current = current->next;
    }
    if (current) {
        if (prev) prev->next = current->next;
        else playlistHead = current->next;
        if (current->title == currentPlaying) currentPlaying = "";
        delete current;
    }
}
void addToHistory(string title, int duration) {
    HistoryNode* newNode = new HistoryNode;
    newNode->title = title;
    newNode->duration = duration;
    newNode->next = historyHead;
    historyHead = newNode;
}
void displayHistory() {
    if (!historyHead) {
        cout << "Riwayat tontonan kosong!" << endl;
        return;
    }
    HistoryNode* current = historyHead;
    while (current) {
        cout << "Judul: " << current->title << ", Durasi: " << current->duration << " menit" << endl;
        current = current->next;
    }
}
void addVideo(string title, int duration) {
    if (findVideo(root, title)) {
        cout << "Judul video sudah ada!" << endl;
        return;
    }
    root = insertBST(root, title, duration);
    UndoNode* undo = new UndoNode;
    undo->action = "add";
    undo->title = title;
    undo->duration = duration;
    undo->status = "tersedia";
    undo->next = undoStack;
    undoStack = undo;
    cout << "Video berhasil ditambahkan!" << endl;
}
void displayVideos() {
    if (!root) {
        cout << "Tidak ada video!" << endl;
        return;
    }
    displayBST(root);
    string choice;
    cout << "Apakah Anda ingin mencari video (y/t)? ";
    cin >> choice;
    if (choice == "y" || choice == "Y") {
        string title;
        cout << "Masukkan judul video: ";
        cin.ignore();
        getline(cin, title);
        VideoNode* video = findVideo(root, title);
        if (video) {
            cout << "Judul: " << video->title << ", Durasi: " << video->duration << " menit, Status: " << video->status << endl;
        } else {
            cout << "Video tidak ditemukan!" << endl;
        }
    }
}
void watchVideo() {
    if (!playlistHead) {
        cout << "Playlist kosong!" << endl;
        return;
    }
    PlaylistNode* current = playlistHead;
    playlistHead = current->next;
    VideoNode* video = findVideo(root, current->title);
    if (video) {
        video->status = "tersedia";
        addToHistory(current->title, current->duration);
        UndoNode* undo = new UndoNode;
        undo->action = "watch";
        undo->title = current->title;
        undo->duration = current->duration;
        undo->status = "sedang diputar";
        undo->next = undoStack;
        undoStack = undo;
    }
    currentPlaying = "";
    if (playlistHead) {
        VideoNode* nextVideo = findVideo(root, playlistHead->title);
        if (nextVideo) {
            nextVideo->status = "sedang diputar";
            currentPlaying = nextVideo->title;
        }
    }
    delete current;
    cout << "Video selesai ditonton!" << endl;
}
void deleteVideo(string title) {
    VideoNode* video = findVideo(root, title);
    if (!video) {
        cout << "Video tidak ditemukan!" << endl;
        return;
    }
    if (video->status == "sedang diputar" || video->status == "dalam antrean") {
        string choice;
        cout << "Video yang ingin dihapus " << video->status << ". Yakin untuk tetap menghapus? (y/t) ";
        cin >> choice;
        if (choice != "y" && choice != "Y") return;
    }
    UndoNode* undo = new UndoNode;
    undo->action = "delete";
    undo->title = video->title;
    undo->duration = video->duration;
    undo->status = video->status;
    undo->next = undoStack;
    undoStack = undo;
    if (video->status == "sedang diputar" || video->status == "dalam antrean") {
        deletePlaylistNode(video->title);
    }
    root = deleteBST(root, title);
    cout << "Video berhasil dihapus!" << endl;
}
void undoAction() {
    if (!undoStack) {
        cout << "Tidak ada aksi untuk dibatalkan!" << endl;
        return;
    }
    UndoNode* undo = undoStack;
    undoStack = undo->next;
    if (undo->action == "add") {
        root = deleteBST(root, undo->title);
    }
    else if (undo->action == "delete") {
        root = insertBST(root, undo->title, undo->duration);
        VideoNode* video = findVideo(root, undo->title);
        if (video) video->status = undo->status;
        if (undo->status == "sedang diputar" || undo->status == "dalam antrean") {
            PlaylistNode* newNode = new PlaylistNode;
            newNode->title = undo->title;
            newNode->duration = undo->duration;
            newNode->next = nullptr;
            if (!playlistHead) {
                playlistHead = newNode;
                if (undo->status == "sedang diputar") currentPlaying = undo->title;
            } else {
                PlaylistNode* temp = playlistHead;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
        }
    }
    else if (undo->action == "add_playlist") {
        VideoNode* video = findVideo(root, undo->title);
        if (video) video->status = "tersedia";
        deletePlaylistNode(undo->title);
    }
    else if (undo->action == "watch") {
        PlaylistNode* newNode = new PlaylistNode;
        newNode->title = undo->title;
        newNode->duration = undo->duration;
        newNode->next = playlistHead;
        playlistHead = newNode;
        VideoNode* video = findVideo(root, undo->title);
        if (video) video->status = "sedang diputar";
        currentPlaying = undo->title;
        if (historyHead && historyHead->title == undo->title) {
            HistoryNode* temp = historyHead;
            historyHead = historyHead->next;
            delete temp;
        }
    }
    cout << "Aksi terakhir dibatalkan!" << endl;
    delete undo;
}
void displayMenu() {
    cout << "\n=== IDLIX Tube ===" << endl;
    cout << "1. Tambah Video" << endl;
    cout << "2. Tampilkan Daftar Video" << endl;
    cout << "3. Tambahkan ke Playlist" << endl;
    cout << "4. Tonton Video" << endl;
    cout << "5. Riwayat Tontonan" << endl;
    cout << "6. Hapus Video" << endl;
    cout << "7. Undo Tindakan Terakhir" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilih opsi: ";
}
int main() {
    int choice;
    string title;
    int duration;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "Masukkan judul video: ";
            getline(cin, title);
            cout << "Masukkan durasi video (menit): ";
            cin >> duration;
            cin.ignore();
            addVideo(title, duration);
        }
        else if (choice == 2) {
            displayVideos();
        }
        else if (choice == 3) {
            cout << "Masukkan judul video: ";
            getline(cin, title);
            addToPlaylist(title);
        }
        else if (choice == 4) {
            watchVideo();
        }
        else if (choice == 5) {
            displayHistory();
        }
        else if (choice == 6) {
            cout << "Masukkan judul video: ";
            getline(cin, title);
            deleteVideo(title);
        }
        else if (choice == 7) {
            undoAction();
        }
        else if (choice == 8) {
            cout << "Terima kasih telah menggunakan IDLIX Tube!" << endl;
            break;
        }
        else {
            cout << "Opsi tidak valid!" << endl;
        }
    }
    return 0;
}