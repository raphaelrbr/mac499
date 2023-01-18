/* C++ Program for Bad Character Heuristic of Boyer
Moore String Matching Algorithm */
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
# define NO_OF_CHARS 256


void preprocess(int * bc, int * shift, int * F, string pat, int m) {
    
    // Bad Character Heuristic
    for (int i = 0; i < NO_OF_CHARS; i++)
        bc[i] = -1;
 
    for (int i = 0; i < m; i++)
        bc[(int) pat[i]] = i;

    int i=m, j=m+1;
    F[i]=j;
    // Strong suffix rule
    while(i>0)
    {

        while(j<=m && pat[i-1] != pat[j-1])
        {

            if (shift[j]==0)
                shift[j] = j-i;

            j = F[j];
        }

        i--;j--;
        F[i] = j; 
    }

    // Part 2
    for(int i=0, j = F[0]; i<=m; i++)
    { 
        if(shift[i]==0)
            shift[i] = j;
  
        if (i==j)
            j = F[j];
    }
}

void search( string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
 
    int bc[NO_OF_CHARS];
    int F[m+1], shift[m+1];

    for(int i=0;i<m+1;i++) shift[i]=0;

    preprocess(bc, shift, F, pat,m);

    int s = 0; 
    while(s <= (n - m))
    {
        int j = m-1;
        while(j >= 0 && pat[j] == txt[s + j])
            j--;
 

        if (j < 0)
        {
            cout << "pattern " << pat << " found at index = " <<  s << endl;

            int badCharShift = (s + m < n)? m-bc[txt[s + m]] : 1;
            int goodSuffixShift = shift[0];
            s += max(badCharShift, goodSuffixShift);
        }
 
        else {
            int badCharShift = max(1, j - bc[txt[s + j]]);
            int goodSuffixShift = shift[j+1];
            s += max(badCharShift, goodSuffixShift);
        }
    }
}
 
/* Driver code */
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