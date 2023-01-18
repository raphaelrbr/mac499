#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int m; // Minimun length of a pattern
int B = 2; // Wu-Manber block size

map<long long, vector<pair<long long,int>>> TABLE;
map<long long,int> SHIFT;

void read_txt(const char * file, string* output) {


    ifstream infile(file); 
    string line;
    string txt;
    while(getline(infile, line)) {
        txt += line;
    }
    // Make lower case and remove non ascii characters
    for (int i = 0; i<txt.size(); i++) {
        if ((int)txt[i] >= 255 || (int)txt[i] < 0) {
            txt[i] = ' ';
        }
        txt[i] = tolower(txt[i]);
    }
    (*output) = txt;
}

void read_patterns(const char * file, string * pat) {

    ifstream infile(file); 
    int i = 0;
    string pattern;
    while(getline(infile, pattern)) {
        pat[i] = pattern;
        i++;
    }
}

long long compute_hash(string s) {
    int p = 31;
    int MOD = 1e9 + 9;
    long long hash = 0;
    long long power = 1;
    for (char c : s) {
        hash = (hash + (c - 'a' + 1) * power) % MOD;
        power = (power * p) % MOD;
    }
    return hash;
}

void preprocess(string * patterns, int k){
    m = INT_MAX; 
    for (int i = 0; i<k; i++) {
        m = min(int(patterns[i].size()), m);
    }
    for (int i = 0; i < 50000; i++) {
        SHIFT[i] = m - B + 1;
    }
    
    for (int i = 0; i<k; i++) {
        for (int j = m; j>=B; j--) {
            long long hash = compute_hash(patterns[i].substr(j-B, B));
            int shift = m - j;
            SHIFT[hash] = min(SHIFT[hash], shift);
            if (shift == 0) {
                long long prefixHash = compute_hash(patterns[i].substr(0, 2));
                int idx = i;
                TABLE[hash].push_back(make_pair(prefixHash, idx));
            }
        }
    }
}

void scan(string text, string * patterns) {
    int idx = m-1;
    int n = text.size();
    while(idx < n) {
        long long h = compute_hash(text.substr(idx-B+1, B));

        if (SHIFT[h] > 0) {
            idx += SHIFT[h];
        }
        
        // Possible match
        else{
            long long prefixHash = compute_hash(text.substr(idx-m+1, B));
            for (auto candidate : TABLE[h]) {
                if (candidate.first == prefixHash) {
                    string pattern = patterns[candidate.second];
                    int nEqual = 0;
                    int i = idx-m+1;
                    int j = 0;
                    int m = pattern.size();
                    bool equal = true;
                    while (i < n && j < m) {
                        if (pattern[j] != text[i]) {
                            equal = false;
                            break;
                        }
                        i++;
                        j++;
                    }
                    if (equal && j == m) {
                        cout << "pattern " << pattern << " found at index " << idx << endl;
                    }
                }
            }
            idx++;
        }
    }
}
    

int main(int argc, char * argv[]) {
    string txt;
    string * pat;
    int k;

    k =  strtol(argv[3], NULL, 10);
    pat = (string*) malloc(k * sizeof(string));
 
    read_txt(argv[1], &txt);
    read_patterns(argv[2], pat);

    auto start = high_resolution_clock::now();


    preprocess(pat, k);
    scan(txt, pat);

    

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}
