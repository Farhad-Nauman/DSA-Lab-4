#include <iostream>
using namespace std;
struct Node {
    int id;
    Node* next;

    Node(int i) {
        id = i;
        next = nullptr;
    }
};

class Josephus {
private:
    Node* head;

public:
    Josephus() {
        head = nullptr;
    }

    ~Josephus() {
        if (!head) return;

        Node* curr = head->next;
        while (curr != head) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        delete head;
        head = nullptr;
    }

    void createCircle(int n) {
        if (n <= 0) return;

        head = new Node(1);
        Node* prv = head;

        for (int i = 2; i <= n; i++) {
            Node* nNode = new Node(i);
            prv->next = nNode;
            prv = nNode;
        }
        prv->next = head;
    }

    void runElimination(int k) {
        if (!head || k <= 0) return;

        Node* curr = head;
        Node* prv = nullptr;

        cout << "\n--- Elimination Order ---\n";
        while (curr->next != curr) {
            for (int c = 1; c < k; c++) {
                prv = curr;
                curr = curr->next;
            }

            cout << "Eliminated person: " << curr->id << endl;

            prv->next = curr->next;
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }

        head = curr;
        cout << "\nSurvivor: Person " << head->id << endl;
    }
};

int main() {
    int n, k;

    cout << "=== Josephus Problem Simulation ===\n";
    cout << "Enter total number of people (N): ";
    cin >> n;
    cout << "Enter elimination step count (k): ";
    cin >> k;

    if (n <= 0 || k <= 0) {
        cout << "Invalid input. N and k must be positive integers.\n";
        return 0;
    }

    Josephus sim;
    sim.createCircle(n);
    sim.runElimination(k);

    return 0;
}