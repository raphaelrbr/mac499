#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
 
 
int out[1000];
int failure[1000];
int go[1000][255];

void read_txt(const char * file, string* output) {


    ifstream infile(file); 
    string line;
    string txt;
    while(getline(infile, line)) {
        txt += line;
        txt += "\n";
    }
    // Make lower case and remove non-asci characters
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
 

int buildMatchingMachine(string arr[], int k)
{
    memset(out, 0, sizeof out);
    memset(go, -1, sizeof go);
    memset(failure, -1, sizeof failure);
    
    int states = 1;
 
    for (int i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        int currentState = 0;
 
        for (int j = 0; j < word.size(); ++j)
        {
            int ch = word[j];
 
            if (go[currentState][ch] == -1)
                go[currentState][ch] = states++;
 
            currentState = go[currentState][ch];
        }
 
        out[currentState] |= (1 << i);
    }
    
    for (int ch = 0; ch < 255; ++ch)
        if (go[0][ch] == -1)
            go[0][ch] = 0;
 
    
    queue<int> q;
    
    for (int ch = 0; ch < 255; ++ch)
    {
        if (go[0][ch] != 0)
        {
            failure[go[0][ch]] = 0;
            q.push(go[0][ch]);
        }
    }

    while (q.size())
    {

        int state = q.front();
        q.pop();

        for (int ch = 0; ch < 255; ++ch)
        {

            if (go[state][ch] != -1)
            {

                int failureNode = failure[state];
 
                while (go[failureNode][ch] == -1)
                      failureNode = failure[failureNode];
 
                failureNode = go[failureNode][ch];
                failure[go[state][ch]] = failureNode;
 
                out[go[state][ch]] |= out[failureNode];
 
                q.push(go[state][ch]);
            }
        }
    }
    return states;
}
 
int next(int currentState, int c)
{
    while (go[currentState][c] == -1)
        currentState = failure[currentState];
 
    return go[currentState][c];
}
 
void search(string txt, string * pat, int k)
{

    buildMatchingMachine(pat, k);
    int currentState = 0;
    for (int i = 0; i < txt.size(); ++i)
    {
        currentState = next(currentState, txt[i]);
 

        if (out[currentState] == 0)
             continue;

        for (int j = 0; j < k; ++j)
        {
            if (out[currentState] & (1 << j))
            {
               cout << "pattern " << pat[j] << " found at index " << i - pat[j].size() + 1 << endl;
            }
        }
    }
}

int main(int argc, char * argv[])
{
    string txt;
    string * pat;
    int k;
    
    k =  strtol(argv[3], NULL, 10);
    pat = (string*) malloc(k * sizeof(string));

    read_txt(argv[1], &txt);
    read_patterns(argv[2], pat);

    auto start = high_resolution_clock::now();
    search(txt, pat, k);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}