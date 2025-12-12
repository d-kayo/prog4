#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool endw;
    vector<Node*> nxt;

    Node() : endw(false), nxt(26, nullptr) {}

    ~Node() {
        for (Node* p : nxt) {
            delete p;
        }
    }
};

class Trie {
private:
    Node* rt;

public:
    Trie() {
        rt = new Node();
    }

    ~Trie() {
        delete rt;
    }

    void add(const string& s) {
        Node* cur = rt;

        for (char c : s) {
            if (!isalpha(c)) continue;
            c = tolower(c);
            int i = c - 'a';

            if (cur->nxt[i] == nullptr) {
                cur->nxt[i] = new Node();
            }
            cur = cur->nxt[i];
        }

        cur->endw = true;
    }

    bool has(const string& s) const {
        Node* cur = rt;

        for (char c : s) {
            if (!isalpha(c)) continue;
            c = tolower(c);
            int i = c - 'a';

            if (cur->nxt[i] == nullptr) return false;
            cur = cur->nxt[i];
        }

        return cur->endw;
    }
};

int main() {
    Trie t;
    ifstream f("zborovi.txt");

    if (!f.is_open()) {
        cout << "Error\n";
        return 1;
    }

    string w;
    int cnt = 0;

    while (getline(f, w)) {
        t.add(w);
        cnt++;
    }

    f.close();

    cout << cnt << "\n";
    cout << t.has("Checks") << "\n";
    

    return 0;
}