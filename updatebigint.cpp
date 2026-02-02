#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct BigInt {
    string value;

    BigInt(string v = "0") {
        if (v.empty()) v = "0";
        size_t first = v.find_first_not_of('0');
        if (string::npos == first) value = "0";
        else value = v.substr(first);
    }

    bool operator<(const BigInt& other) const {
        if (value.length() != other.value.length())
            return value.length() < other.value.length();
        return value < other.value;
    }

    bool operator==(const BigInt& other) const {
        return value == other.value;
    }

    static pair<BigInt, BigInt> divmod(BigInt dividend, BigInt divisor) {
        if (divisor.value == "0") return {BigInt("0"), BigInt("0")}; 
        if (dividend < divisor) return {BigInt("0"), dividend};
        string quotient = "";
        BigInt remainder("0");
        for (char c : dividend.value) {
            if (remainder.value == "0") remainder.value = string(1, c);
            else remainder.value += c;
            int count = 0;
            while (!(remainder < divisor)) {
                remainder = remainder - divisor;
                count++;
            }
            quotient += to_string(count);
        }
        return {BigInt(quotient), remainder};
    }

    BigInt operator/(const BigInt& other) const { return divmod(*this, other).first; }
    BigInt operator%(const BigInt& other) const { return divmod(*this, other).second; }

    BigInt operator+(const BigInt& other) const {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry + (i >= 0 ? value[i--] - '0' : 0) + (j >= 0 ? other.value[j--] - '0' : 0);
            res += (char)(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator-(const BigInt& other) const {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, borrow = 0;
        while (i >= 0) {
            int val1 = value[i--] - '0';
            int val2 = (j >= 0 ? other.value[j--] - '0' : 0);
            int sub = val1 - val2 - borrow;
            if (sub < 0) { sub += 10; borrow = 1; }
            else borrow = 0;
            res += (char)(sub + '0');
        }
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
        for (int x : res) s += (char)(x + '0');
        return BigInt(s);
    }

    
    bool is_prime() const {
        if (value == "0" || value == "1") return false;
        if (value == "2" || value == "3") return true;
        if ((value.back() - '0') % 2 == 0) return false;

    
        for (BigInt i("3"); i * i < *this || i * i == *this; i = i + BigInt("2")) {
            if ((*this % i).value == "0") return false;
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const BigInt& bi) {
        os << bi.value;
        return os;
    }
};

int main() {
    string s1;
    char op;

    cout << "107 ? da se proveri za dali e prost, ili '10 + 5'): " << endl;
    while (cin >> s1 >> op) {
        BigInt n1(s1);

        if (op == '?') {
            if (n1.is_prime()) cout << n1 << " e prost" << endl;
            else cout << n1 << " e slozen" << endl;
        } else {
            string s2;
            cin >> s2;
            BigInt n2(s2);
            if (op == '+') cout << n1 + n2 << endl;
            else if (op == '-') cout << n1 - n2 << endl;
            else if (op == '*') cout << n1 * n2 << endl;
            else if (op == '/') cout << n1 / n2 << endl;
            else if (op == '%') cout << n1 % n2 << endl;
        }
    }
    return 0;
}