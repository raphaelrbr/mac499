#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
 
void preprocess(int * skip, string pattern) {
    
    int m = pattern.size();
    for (int i = 0; i<256; i++) {
        skip[i] = m;
    }
    for (int i = 0; i<m-1; i++) {
        skip[pattern[i]] = m - i -1;
    }
}

void search(string text, string pattern) {
    int skip[256];
    preprocess(skip, pattern);
    int shift = 0;
    int n = text.size();
    int m = pattern.size();
    while (shift <= (n-m)) {
        // Check match
        int i = 0;
        int j = m-1;
        while (j >= 0 && text[shift + i] == pattern[j]) {
            i++;
            j--;
        }
        if (j < 0) {
            cout << "pattern " << pattern << " found at index " << shift << endl;
            shift++;
        }
        else{
            shift += skip[text[shift + m - 1]];
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
    // Make lower case and remove non-asci characters
    for (int i = 0; i<txt.size(); i++) {
        if ((int)txt[i] >= 255 || (int)txt[i] < 0) {
            txt[i] = ' ';
        }
        txt[i] = tolower(txt[i]);
    }
    for (int i = 0; i<pat.size(); i++) {
        pat[i] = tolower(pat[i]);
    }
    auto start = high_resolution_clock::now();
    search(txt, pat);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}