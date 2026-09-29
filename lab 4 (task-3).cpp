#include <iostream>
#include <string>

using namespace std;

struct Node {
    int bit;
    Node* prev;
    Node* next;

    Node(int b) {
        bit = b;
        prev = nullptr;
        next = nullptr;
    }
};

class BinDLL {
public:
    Node* head;
    Node* tail;

    BinDLL() {
        head = nullptr;
        tail = nullptr;
    }

    BinDLL(const BinDLL& other) {
        head = nullptr;
        tail = nullptr;
        Node* tmp = other.head;
        while (tmp) {
            pushBack(tmp->bit);
            tmp = tmp->next;
        }
    }

    BinDLL& operator=(const BinDLL& other) {
        if (this != &other) {
            clear();
            Node* tmp = other.head;
            while (tmp) {
                pushBack(tmp->bit);
                tmp = tmp->next;
            }
        }
        return *this;
    }

    ~BinDLL() {
        clear();
    }

    void clear() {
        Node* tmp = head;
        while (tmp) {
            Node* nxt = tmp->next;
            delete tmp;
            tmp = nxt;
        }
        head = nullptr;
        tail = nullptr;
    }

    void pushBack(int b) {
        Node* nNode = new Node(b);
        if (!head) {
            head = tail = nNode;
            return;
        }
        tail->next = nNode;
        nNode->prev = tail;
        tail = nNode;
    }

    void pushFront(int b) {
        Node* nNode = new Node(b);
        if (!head) {
            head = tail = nNode;
            return;
        }
        nNode->next = head;
        head->prev = nNode;
        head = nNode;
    }

    void storeBinary(const string& str) {
        clear();
        for (char c : str) {
            if (c == '0' || c == '1') {
                pushBack(c - '0');
            }
        }
        padBlock();
    }

    BinDLL onesComplement() const {
        BinDLL res;
        Node* tmp = head;
        while (tmp) {
            res.pushBack(tmp->bit == 0 ? 1 : 0);
            tmp = tmp->next;
        }
        return res;
    }

    BinDLL twosComplement() const {
        BinDLL res = onesComplement();

        Node* tmp = res.tail;
        int cry = 1;

        while (tmp && cry > 0) {
            int sum = tmp->bit + cry;
            tmp->bit = sum % 2;
            cry = sum / 2;
            tmp = tmp->prev;
        }

        if (cry > 0) {
            res.pushFront(cry);
            res.padBlock();
        }

        return res;
    }

    static BinDLL add(const BinDLL& b1, const BinDLL& b2) {
        BinDLL res;
        Node* t1 = b1.tail;
        Node* t2 = b2.tail;
        int cry = 0;

        while (t1 || t2 || cry > 0) {
            int sum = cry;
            if (t1) {
                sum += t1->bit;
                t1 = t1->prev;
            }
            if (t2) {
                sum += t2->bit;
                t2 = t2->prev;
            }

            res.pushFront(sum % 2);
            cry = sum / 2;
        }

        res.padBlock();
        return res;
    }

    static BinDLL multiply(const BinDLL& b1, const BinDLL& b2) {
        BinDLL res;
        res.pushBack(0);

        Node* t2 = b2.tail;
        int sh = 0;

        while (t2) {
            if (t2->bit == 1) {
                BinDLL tmp;
                Node* t1 = b1.head;
                while (t1) {
                    tmp.pushBack(t1->bit);
                    t1 = t1->next;
                }
                for (int i = 0; i < sh; i++) {
                    tmp.pushBack(0);
                }
                res = add(res, tmp);
            }
            sh++;
            t2 = t2->prev;
        }

        return res;
    }

    long long toDecimal() const {
        long long val = 0;
        Node* tmp = head;
        while (tmp) {
            val = (val * 2) + tmp->bit;
            tmp = tmp->next;
        }
        return val;
    }

    void print() const {
        Node* tmp = head;
        int cnt = 0;
        while (tmp) {
            cout << tmp->bit;
            cnt++;
            if (cnt % 8 == 0 && tmp->next) {
                cout << " ";
            }
            tmp = tmp->next;
        }
        cout << endl;
    }

private:
    void padBlock() {
        int cnt = 0;
        Node* tmp = head;
        while (tmp) {
            cnt++;
            tmp = tmp->next;
        }

        if (cnt == 0) {
            pushBack(0);
            cnt = 1;
        }

        if (cnt % 8 != 0) {
            int pad = 8 - (cnt % 8);
            for (int i = 0; i < pad; i++) {
                pushFront(0);
            }
        }
    }
};

int main() {
    BinDLL num1, num2;
    string s1, s2;

    cout << "=== Binary Arithmetic DLL ===\n";
    cout << "Enter first binary number: ";
    cin >> s1;
    cout << "Enter second binary number: ";
    cin >> s2;

    num1.storeBinary(s1);
    num2.storeBinary(s2);

    cout << "\nBinary Number 1: ";
    num1.print();
    cout << "Decimal Value: " << num1.toDecimal() << endl;

    cout << "\nBinary Number 2: ";
    num2.print();
    cout << "Decimal Value: " << num2.toDecimal() << endl;

    BinDLL oComp = num1.onesComplement();
    cout << "\n1's Complement of Number 1: ";
    oComp.print();

    BinDLL tComp = num1.twosComplement();
    cout << "2's Complement of Number 1: ";
    tComp.print();

    BinDLL sumRes = BinDLL::add(num1, num2);
    cout << "\nAddition Result: ";
    sumRes.print();
    cout << "Decimal Value: " << sumRes.toDecimal() << endl;

    BinDLL mulRes = BinDLL::multiply(num1, num2);
    cout << "\nMultiplication Result: ";
    mulRes.print();
    cout << "Decimal Value: " << mulRes.toDecimal() << endl;

    return 0;
}