#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    int type;
    string s;
};

struct TrieNode {
    TrieNode* next[26];
    bool endOfWord;
    bool visited;
    TrieNode() {
        for(int i=0;i<26;i++) {
            next[i]=nullptr;
        }
        endOfWord=false;
        visited=false;
    }
};

class Trie {
    private:
        TrieNode* root;
    public:
        Trie() {
            root = new TrieNode();
        }
        TrieNode* get_root() {
            return root;
        }
        void insert(string word) {
            TrieNode* node=root;
            for(char ch: word) {
                int index=ch-'a';
                if(!node->next[index]) {
                    node->next[index]=new TrieNode();
                }
                node=node->next[index];
            }
            node->endOfWord=true;
        }
        bool search(string word) {
            TrieNode* node=root;
            for(char ch: word) {
                int index=ch-'a';
                if(!node->next[index]) {
                    return false;
                }
                node=node->next[index];
            }
            return node->endOfWord;
        }
        TrieNode* nodeOfPrefix(string prefix) {
            TrieNode* node=root;
            for(char ch:prefix) {
                int index=ch-'a';
                if(!node->next[index]) {
                    return nullptr;
                }
                node=node->next[index];
            }
            return node;
        }
        void searchFromHere(TrieNode* node, string ssf, vector<string>& matchings) {
            if(node->endOfWord) {
                matchings.push_back(ssf);
            }
            for(int i=0;i<26;i++) {
                if(node->next[i]) {
                    char ch=(char)i+'a';
                    searchFromHere(node->next[i], ssf+ch, matchings);
                }
            }
        }
        void recurse(TrieNode* node, int i, int k, string s, string ssf, vector<string>& res) {
            if(k>3) return;
            int len=s.size();
            if(node->endOfWord && (k+(s.size()-i))<3) {
                if(!node->visited) {
                    res.push_back(ssf);
                    node->visited=true;
                }
            } 
            if(node->endOfWord) {
                k+=len-i;
                if(k<=3) {
                    if(!node->visited) {
                        res.push_back(ssf);
                        node->visited=true;
                    }
                }
                k-=len-i;
            }
            if(i==len) {
                for(int j=0;j<26;j++) {
                    char ch='a'+j;
                    if(node->next[j]!=NULL) {
                        recurse(node->next[j], i, k+1, s, ssf+ch, res);
                    }
                }
            }
            for(int j=0;j<26;j++) {
                if(node->next[j]!=NULL) {
                    char ch='a'+j;
                    if(s[i]==ch) {
                        recurse(node->next[j], i+1, k, s, ssf+ch, res);
                    }
                    recurse(node->next[j], i+1, k+1, s, ssf+ch, res);
                    recurse(node, i+1, k+1, s, ssf, res);
                    recurse(node->next[j], i, k+1, s, ssf+ch, res);
                }
            }
        }
        void devisit(TrieNode* node) {
            if(node->endOfWord) node->visited=false;
            for(int i=0;i<26;i++) {
                if(node->next[i]!=NULL) {
                    devisit(node->next[i]);
                }
            }
        }
};

int main() {
    Trie trie;
    int n, q;
    cin >> n >> q;
    Query queries[q];
    string s;
    for(int i=0;i<n;i++) {
        cin >> s;
        trie.insert(s);
    }
    for(int i=0;i<q;i++) {
        cin >> queries[i].type >> queries[i].s;
    }
    for(int i=0;i<q;i++) {
        if(queries[i].type==1) {
            cout << trie.search(queries[i].s) << endl;
        }
        else if(queries[i].type==2) {
            vector<string> v;
            int num;
            TrieNode* temp=trie.nodeOfPrefix(queries[i].s);
            if(temp!=NULL) {
                trie.searchFromHere(temp, queries[i].s, v);
            }
            num=v.size();
            sort(v.begin(), v.end());
            cout<<num<<endl;
            for(int i=0;i<num;i++) {
                cout << v[i]<<endl;
            }
        }
        else if(queries[i].type==3) {
            TrieNode* temp_node=trie.get_root();
            vector<string> auto_correct;
            trie.recurse(temp_node, 0, 0, queries[i].s, "", auto_correct);
            int len=auto_correct.size();
            sort(auto_correct.begin(), auto_correct.end());
            cout<<len<<endl;
            for(int i=0;i<len;i++) {
                cout<<auto_correct[i]<<endl;
            }
            TrieNode* temp_node1=trie.get_root();
            trie.devisit(temp_node1);
        }
    }
    // cout << trie.search(s) << endl;
    // vector<string> v;
    // int n;
    // TrieNode* temp=trie.nodeOfPrefix(s);
    // if(temp!=NULL) {
    //     trie.searchFromHere(temp, s, v);
    // }
    // n=v.size();
    // cout<<n<<endl;
    // for(int i=0;i<n;i++) {
    //     cout << v[i]<<endl;
    // }

    // TrieNode* temp_node=trie.get_root();
    // vector<string> auto_correct;
    // trie.recurse(temp_node, 0, 0, s, "", auto_correct);
    // int len=auto_correct.size();
    // cout<<len<<endl;
    // for(int i=0;i<len;i++) {
    //     cout<<auto_correct[i]<<endl;
    // }
    // TrieNode* temp_node1=trie.get_root();
    // trie.devisit(temp_node1);
    return 0;
}