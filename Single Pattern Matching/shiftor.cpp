#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const int maxn = 256;
long long table[maxn];

void shiftOr(string t, string p) {
    int k = p.length();
    long phi = ~1; // All bits set to 0

    for (int i = 0; i <=255; ++i){
        table[i] = ~0;
    }
    for (int i = 0; i < k; ++i){ 
        table[p[i]] &= ~(1L << i);
    }
    for (int i = 0; i < t.length(); ++i) {
        phi |= table[t[i]];
        phi <<= 1;
        if ((phi & (1L << k)) == 0) {
        cout << "pattern " << p << " found at index " << i - p.length() + 1 << endl;
        }
    }
}


int main(int argc, char * argv[])
{
    string txt, pat;
    freopen(argv[1], "r", stdin);
    while(cin) {
        string line;
        getline(cin, line);
        txt += line;
    }
    pat = argv[2];

    // Make lower case
    for (int i = 0; i<txt.size(); i++) {
        txt[i] = tolower(txt[i]);
    }
    for (int i = 0; i<pat.size(); i++) {
        pat[i] = tolower(pat[i]);
    }
    auto start = high_resolution_clock::now();
    shiftOr(txt, pat);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}