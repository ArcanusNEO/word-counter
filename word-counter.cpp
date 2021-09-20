#include <bits/extc++.h>
#include <unistd.h>
using namespace std;

class Trie {
  struct Node {
    char c;
    bool stop;
    Node* son,* sibling;
    Node(char ch = '\0', Node* _son = nullptr, Node* _sibling = nullptr) :
      c(ch), son(_son), sibling(_sibling), stop(false) {}
  };
  Node* root;
  virtual void __clear(Node* root) {
    if (root == nullptr) {return;}
    __clear(root->son);
    __clear(root->sibling);
    delete root;
  }
public: 
  Trie() : root(new Node()) {}
  virtual ~Trie() {
    __clear(root);
  }
  virtual void clear() {
    __clear(root);
    root = new Node();
  }
  virtual void insert(const string & word) {
    auto root = this->root;
    auto ptr = root->son;
    int i = 0; while (i < word.size()) {
      for (ptr = root->son; ptr != nullptr; ptr = ptr->sibling) {
        if (word[i] == ptr->c) {
          root = ptr;
          ++i;
          break;
        }
      }
      if (ptr == nullptr) {break;}
    }
    for (; i < word.size(); ++i) {
      root->son = new Node(word[i], nullptr, root->son);
      root = root->son;
    }
    root->stop = true;
  }
  virtual bool search(const string & word) {
    auto root = this->root;
    auto ptr = root->son;
    int i = 0; while (i < word.size()) {
      for (ptr = root->son; ptr != nullptr; ptr = ptr->sibling) {
        if (word[i] == ptr->c) {
          root = ptr;
          ++i;
          break;
        }
      }
      if (ptr == nullptr) {return false;}
    }
    return root->stop;
  }
};

class Solution {
private:
  string iPath, oPath, sPath;
  map<string, int> freq;
  Trie trie;

public:
  Solution(string i, string o, string s) :
    iPath(i), oPath(o), sPath(s) {
    initStopWords(sPath);
  }
  void initStopWords(const string & path) {
    auto oldcin = cin.rdbuf();
    if (path != "") {
      cin.rdbuf(ifstream(path).rdbuf());
    }
    string word;
    while (cin >> word) {
      trie.insert(word);
    }
  }
  void format(vector<string> & words) {
    int i, j;
    string word = words[0];
    words.clear();
    for (i = 0; i < word.size(); ++i) {
      if (word[i] >= 'A' && word[i] <= 'Z') {
        word[i] += 32;
      }
    }
    for (i = 0; i < word.size(); ++i) {
      if (word[j] >= 'a' && word[j] <= 'z' || word[j] == '\'') {break;}
    }
    while (i < word.size()) {
      for (j = i + 1; j < word.size(); ++j) {
        if (!(word[j] >= 'a' && word[j] <= 'z')) {break;}
      }
      if (!(i + 1 == j && word[i] == '\'')) {
        words.push_back(word.substr(i, j - i));
      }
      for (i = j; i < word.size(); ++i) {
        if (word[j] >= 'a' && word[j] <= 'z' || word[j] == '\'') {break;}
      }
    }
  }
  void readArticle(const string & path) {
    if (path != "") {
      cin.rdbuf(ifstream(path).rdbuf());
    }
    string word;
    int64_t tot = 0;
    while (cin >> word) {
      vector<string> container;
      container.push_back(word);
      format(container);
      for (auto word : container) {
        if (!trie.search(word)) {
          ++freq[word];
          ++tot;
        }
      }
    }
    cout << "Total words: " << tot << endl;
  }
  void sortWords(vector<pair<string, int>> & arr) {
    for (auto wordPair : freq) {
      arr.push_back(wordPair);
    }
    sort(arr.begin(), arr.end(), [](const pair<string, int> & pairX, const pair<string, int> & pairY) {
      return (pairX.second > pairY.second || pairX.second == pairY.second && pairX.first < pairY.first);
    });
  }
  void writeToFile(const string & path, const vector<pair<string, int>> & arr) {
    if (path != "") {
      cout.rdbuf(ofstream(path).rdbuf());
    }
    if (arr.empty()) {
      cout << "{}";
      return;
    }
    cout << "{\n\t\"" << arr[0].first << "\": " << arr[0].second;
    for (int i = 1; i < arr.size(); ++i) {
      cout << ",\n\t\"" << arr[i].first << "\": " << arr[i].second;
    }
    cout << "\n}";
  }
  void solve() {
    readArticle(iPath);
    vector<pair<string, int>> arr;
    sortWords(arr);
    writeToFile(oPath, arr);
  }
};

signed main(int argc, char* argv[]) {
  int opt;
  string iPath = "", oPath = "", sPath = "Stop Words.txt";
  while (~(opt = getopt(argc, argv, "i::o::s::"))) {
    switch (opt) {
      case 'i': {
        iPath = ((optarg == nullptr || strcmp(optarg, "-") == 0) ? "" : optarg);
      break;}
      case 'o': {
        oPath = ((optarg == nullptr || strcmp(optarg, "-") == 0) ? "" : optarg);
      break;}
      case 's': {
        sPath = ((optarg == nullptr || strcmp(optarg, "-") == 0) ? "" : optarg);
      break;}
      default: {
        cerr << "Error arguments" << endl;
        exit(1);
      break;}
    }
  }
  if (iPath == "" && sPath == "") {
    cerr << "Cannot have two options to read from standard input" << endl;
    exit(1);
  }
  // ios_base::sync_with_stdio(false);
  // if (iPath != "" && oPath != "" && sPath != "") {
  //   cin.tie(nullptr); cout.tie(nullptr);
  // }
  Solution s(iPath, oPath, sPath);
  s.solve();
}