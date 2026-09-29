#include <iostream>
#include <string>
using namespace std;

struct Node {
    int id;
    string nm;
    string dur;
    Node* prev;
    Node* next;

    Node(int i, string n, string d) {
        id = i;
        nm = n;
        dur = d;
        prev = nullptr;
        next = nullptr;
    }
};
class Playlist {
private:
    Node* head;
    Node* tail;
    Node* curr;
public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        curr = nullptr;
    }
    Playlist() {
        Node* tmp = head;
        while (tmp) {
            Node* nxt = tmp->next;
            delete tmp;
            tmp = nxt;
        }
    }
    void addSong(int i, string n, string d) {
        Node* nNode = new Node(i, n, d);
        if (!head) {
            head = tail = curr = nNode;
            cout << "Song added successfully.\n";
            return;
        }
        tail->next = nNode;
        nNode->prev = tail;
        tail = nNode;
        cout << "Song added successfully.\n";
    }
    void deleteSong(int i) {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* tmp = head;
        while (tmp && tmp->id != i) {
            tmp = tmp->next;
        }

        if (!tmp) {
            cout << "Song ID not found.\n";
            return;
        }

        if (tmp == curr) {
            curr = tmp->next ? tmp->next : tmp->prev;
        }

        if (tmp == head && tmp == tail) {
            head = tail = curr = nullptr;
        } else if (tmp == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (tmp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
        }

        delete tmp;
        cout << "Song deleted successfully.\n";
    }
    void displayForward() {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }
        Node* tmp = head;
        cout << "\n--- Playlist (Forward) ---\n";
        while (tmp) {
            cout << "ID: " << tmp->id << " | Name: " << tmp->nm << " | Duration: " << tmp->dur << endl;
            tmp = tmp->next;
        }
    }
    void displayBackward() {
        if (!tail) {
            cout << "Playlist is empty.\n";
            return;
        }
        Node* tmp = tail;
        cout << "\n--- Playlist (Backward) ---\n";
        while (tmp) {
            cout << "ID: " << tmp->id << " | Name: " << tmp->nm << " | Duration: " << tmp->dur << endl;
            tmp = tmp->prev;
        }
    }
    void searchSong(int i) {
        Node* tmp = head;
        while (tmp) {
            if (tmp->id == i) {
                cout << "Found -> ID: " << tmp->id << " | Name: " << tmp->nm << " | Duration: " << tmp->dur << endl;
                return;
            }
            tmp = tmp->next;
        }
        cout << "Song not found.\n";
    }

    void playNext() {
        if (!curr) {
            cout << "Playlist is empty.\n";
            return;
        }
        if (curr->next) {
            curr = curr->next;
            cout << "Now Playing: " << curr->nm << endl;
        } else {
            cout << "Reached end of playlist. Now Playing: " << curr->nm << endl;
        }
    }
    void playPrevious() {
        if (!curr) {
            cout << "Playlist is empty.\n";
            return;
        }
        if (curr->prev) {
            curr = curr->prev;
            cout << "Now Playing: " << curr->nm << endl;
        } else {
            cout << "Reached start of playlist. Now Playing: " << curr->nm << endl;
        }
    }
    void reversePlaylist() {
        if (!head || !head->next) {
            cout << "Playlist reversed.\n";
            return;
        }

        Node* ptr = head;
        Node* tmp = nullptr;
        tail = head;

        while (ptr) {
            tmp = ptr->prev;
            ptr->prev = ptr->next;
            ptr->next = tmp;
            ptr = ptr->prev;
        }

        if (tmp) {
            head = tmp->prev;
        }
        cout << "Playlist reversed successfully.\n";
    }
};
int main() {
    Playlist p;
    int ch, i;
    string n, d;

    while (true) {
        cout << "\n=== Playlist Menu ===\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 9) break;

        switch (ch) {
            case 1:
                cout << "Enter Song ID: ";
                cin >> i;
                cin.ignore();
                cout << "Enter Song Name: ";
                getline(cin, n);
                cout << "Enter Duration (m:s): ";
                getline(cin, d);
                p.addSong(i, n, d);
                break;
            case 2:
                cout << "Enter Song ID to delete: ";
                cin >> i;
                p.deleteSong(i);
                break;
            case 3:
                p.displayForward();
                break;
            case 4:
                p.displayBackward();
                break;
            case 5:
                cout << "Enter Song ID to search: ";
                cin >> i;
                p.searchSong(i);
                break;
            case 6:
                p.playNext();
                break;
            case 7:
                p.playPrevious();
                break;
            case 8:
                p.reversePlaylist();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}