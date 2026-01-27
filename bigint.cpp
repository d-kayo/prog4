#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct BigInt {
    string value;

    BigInt(string v = "0") : value(v) {}

    
    BigInt operator+(const BigInt& other) const {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry + (i >= 0 ? value[i--] - '0' : 0) + (j >= 0 ? other.value[j--] - '0' : 0);
            res += to_string(sum % 10);
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    
    BigInt operator-(const BigInt& other) const {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, borrow = 0;
        while (i >= 0) {
            int sub = (value[i--] - '0') - (j >= 0 ? other.value[j--] - '0' : 0) - borrow;
            if (sub < 0) { sub += 10; borrow = 1; }
            else borrow = 0;
            res += to_string(sub);
        }
        while (res.length() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

     
    BigInt operator*(const BigInt& other) const {
        if (value == "0" || other.value == "0") return BigInt("0");
        vector<int> res(value.size() + other.value.size(), 0);
        for (int i = value.size() - 1; i >= 0; i--) {
            for (int j = other.value.size() - 1; j >= 0; j--) {
                res[i + j + 1] += (value[i] - '0') * (other.value[j] - '0');
                res[i + j] += res[i + j + 1] / 10;
                res[i + j + 1] %= 10;
            }
        }
        string s = "";
        int i = 0;
        while (i < res.size() && res[i] == 0) i++;
        while (i < res.size()) s += to_string(res[i++]);
        return BigInt(s);
    }

    
    friend ostream& operator<<(ostream& os, const BigInt& bi) {
        os << bi.value;
        return os;
    }
};

int main() {
    string s1, s2;
    char operation;


    if (!(cin >> s1 >> operation >> s2)) return 0;

    BigInt num1(s1), num2(s2);

    cout << "="<<endl;
    if (operation == '+') {
        cout << num1 + num2 << endl;
    } else if (operation == '-') {
    
        if (s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2)) {
            cout << "-" << num2 - num1 << endl;
        } else {
            cout << num1 - num2 << endl;
        }
    } else if (operation == '*') {
        cout << num1 * num2 << endl;
    } else {
        cout << "Nepoznata operacija!" << endl;
    }

    return 0;
}
