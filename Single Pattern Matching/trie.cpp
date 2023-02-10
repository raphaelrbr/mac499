#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
#define MAX_CHAR 256


class Trie
{

    map<char, Trie *> next;
    vector<int> children;

public:
    Trie(string text)
    {
        int length = text.length();
        for (int j = 0; j < length; j++)
        {
            string suffix = text.substr(j);
            insert(suffix, j);
        }
    }

    Trie()
    {
    }

    void insert(string suffix, int j)
    {
        Trie *currentNode = this;
        for (auto c : suffix)
        {
            if (currentNode->next[c] == NULL)
            {
                currentNode->next[c] = new Trie();
            }
            currentNode = currentNode->next[c];
            currentNode->children.push_back(j);
        }
    }

    void search(string pattern)
    {
        Trie *currentNode = this;
        for (auto c : pattern)
        {
            if (currentNode->next[c] == NULL)
            {
                return;
            }

            currentNode = currentNode->next[c];
        }
        print(pattern, currentNode);
    }

    void print(string pattern, Trie *currentNode)
    {
        
        for (auto index : currentNode->children)
        {
            cout << "pattern " << pattern << " found at: " << index << endl;;
        }

    }
};

int main(int argc, char *argv[])
{
    string txt, pat;
    freopen(argv[1], "r", stdin);
    while (cin)
    {
        string line;
        getline(cin, line);
        txt += line;
    }
    pat = argv[2];

    // Make lower case
    for (int i = 0; i < txt.size(); i++)
    {
        txt[i] = tolower(txt[i]);
    }
    for (int i = 0; i < pat.size(); i++)
    {
        pat[i] = tolower(pat[i]);
    }
    auto start = high_resolution_clock::now();
    Trie *suffixTree = new Trie(txt);
    suffixTree->search(pat);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}
