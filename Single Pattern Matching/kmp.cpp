#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int * preprocess(string s) {
    int n = (int)s.length();
    int * pi = (int *)malloc(n * sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

void search(string p, string t) {
    string z = p + '#' + t;
    int * pi = preprocess(z);
    for (int i = 0; i < z.length(); i++) {
        if (pi[i] == p.length()) {
           cout << "pattern " << p << " found at index " << i - 2*p.length() << endl;
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
    search(pat, txt);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}