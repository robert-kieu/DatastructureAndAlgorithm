#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include<fstream>

using namespace std;

#define EMPTY_STRING ""

struct NODE
{
    char c;
    int freq;
    NODE* pL, * pR;
};

NODE* getNode(char ch, int freq, NODE* pL, NODE* pR)
{
    NODE* pnode = new NODE();

    pnode->c = ch;
    pnode->freq = freq;
    pnode->pL = pL;
    pnode->pR = pR;

    return pnode;
}

struct COMPRESS { bool operator()(NODE* l, NODE* r) { return l->freq > r->freq; } };


bool isLeaf(NODE* pnode) { return !pnode->pL && !pnode->pR; }

void encoding(NODE* pnode, string s, unordered_map<char, string>& code)
{
    if (!pnode) return;

    
    if (isLeaf(pnode))  code[pnode->c] = (s != EMPTY_STRING) ? s : "1";

    encoding(pnode->pL, s + "0", code);
    encoding(pnode->pR, s + "1", code);
}

void decode(NODE* pnode, int& pos, string s, string& response)
{
    if (!pnode)  return;

    if (isLeaf(pnode)) {
        cout << pnode->c;
        response += pnode->c;
        return;
    }

    ++pos;

    if (s[pos] == '0')  decode(pnode->pL, pos, s, response);
    else  decode(pnode->pR, pos, s, response);
}

void huffmanTree() {
    string s = "";
    ifstream read;
    read.open("input.txt");
    while (!read.eof()) {
        string temp;
        getline(read, temp);
        s += temp;
    }
    cout << "\nOriginal string is : " << s << '\n';
    read.close();

    if (s == EMPTY_STRING) return;

    ofstream write;

    write.open("output.txt");

    unordered_map<char, int> f;
    for (char c : s)  ++f[c];

    priority_queue<NODE*, vector<NODE*>, COMPRESS> pq;

    for (auto pair : f)  pq.push(getNode(pair.first, pair.second, NULL, NULL));

    while (pq.size() != 1) {
        NODE* pL = pq.top(); pq.pop();
        NODE* pR = pq.top(); pq.pop();
        int sum = pL->freq + pR->freq;
        pq.push(getNode('\0', sum, pL, pR));
    }
    NODE* root = pq.top();
    unordered_map<char, string> huffmanCode;
    encoding(root, EMPTY_STRING, huffmanCode);

    cout << "Huffman Codes : " << '\n';
    for (auto p : huffmanCode)
        cout << p.first << " " << p.second << '\n';

    string str;
    for (char c : s) str += huffmanCode[c];

    cout << "\nEncoded string is : " << str << '\n';
    write << str;
    write.close();

    ifstream read2;
    s = "";
    read2.open("output.txt");
    while (!read2.eof()) {
        string temp;
        read2 >> temp;
        s += temp;
    }
    read2.close();

    cout << "\nDecoded string is : ";

    ofstream write2; str = s;
    string res;
    write2.open("uncompressFile.txt");
    if (isLeaf(root))
        while (root->freq > 0) {
            cout << root->c;
            write2 << root->c;
            --root->freq;
        }
    else {
        int index = -1;
        while (index < (int)str.size() - 1) decode(root, index, str, res);
    }
    write2 << res;
    write2.close();
}

int main()
{
    huffmanTree();
    return 0;
}