#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

using namespace std;

class Trie {
public:
    Trie* deca[31];
    bool zbor;
    Trie() {
        for (int i = 0; i < 31; i++) deca[i] = nullptr;
        zbor = false;
    }
};

u32string azbuka = U"абвгдѓежзѕијклљмнњопрстќуфхцчџш";

int indeks(char32_t c) {
    for (int i = 0; i < 31; i++)
        if (azbuka[i] == c) return i;
    return -1;
}

void insert(Trie* root, const u32string& zbor) {
    Trie* cur = root;
    for (char32_t c : zbor) {
        int i = indeks(c);
        if (i == -1) continue;
        if (!cur->deca[i]) cur->deca[i] = new Trie();
        cur = cur->deca[i];
    }
    cur->zbor = true;
}

bool prebaraj(Trie* root, const u32string& zbor) {
    Trie* cur = root;
    for (char32_t c : zbor) {
        int i = indeks(c);
        if (i == -1) return false;
        if (!cur->deca[i]) return false;
        cur = cur->deca[i];
    }
    return cur->zbor;
}

int main() {
    Trie* root = new Trie();
    wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    insert(root, conv.from_bytes("македонија"));
    cout << prebaraj(root, conv.from_bytes("македонија")) << endl;
    cout << prebaraj(root, conv.from_bytes("македонијааа")) << endl;
}