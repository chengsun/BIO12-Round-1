#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

bool anagram(unsigned long a, unsigned long b) {
    ostringstream ssa;
    ssa << (a);
    string sa = ssa.str();
    ostringstream ssb;
    ssb << (b);
    string sb = ssb.str();
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    return (sa == sb);
}


bool _anagram(unsigned long b) {
    ostringstream ssb;
    ssb << (b);
    string sb = ssb.str();
    sort(sb.begin(), sb.end());
    return ("123456789" == sb);
}
void a() {
    unsigned long gen;
    bool anyfound = false;
    cin >> gen;
    for (unsigned m = 2; m <= 9; ++m) {
        unsigned long num = gen * m;
        if (anagram(gen, num)) {
            cout << m << ' ';
            anyfound = true;
        }
    }
    if (!anyfound) cout << "NO";
    cout << endl;
}

void b() {
    unsigned long gen;
    cin >> gen;
    for (unsigned m = 2; m <= 9; ++m) {
        ldiv_t d = ldiv(gen, m);
        if (d.rem == 0 && anagram(gen, d.quot)) {
            cout << d.quot << ' ';
        }
    }
}

void c() {
    string str = "123456789";
    unsigned ctr = 0;
    do {
        long s = atol(str.c_str());
        unsigned long num;
        for (unsigned m = 2; (num = s * m) <= 987654321; ++m) {
            if (_anagram(num)) {
                ++ctr;
                break;
            }
        }
    } while (next_permutation(str.begin(), str.end()));
    cout << ctr << endl;
}

int main() {
    a();
    return 0;
}
