#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Trie {
  struct Node {
    char c;
    int counter;
    Node* son,* sibling;
    Node(char ch = '\0', Node* _son = nullptr, Node* _sibling = nullptr) :
      c(ch), son(_son), sibling(_sibling), counter(0) {}
  };
  Node* root;
  virtual void __clear(Node* root) {
    if (root == nullptr) {return;}
    __clear(root->son);
    __clear(root->sibling);
    delete root;
  }
  virtual void __dump(Node* root, string & word, vector<pair<string, int>> & arr) {
    if (root == nullptr) {return;}
    __dump(root->sibling, word, arr);
    if (root->c != '\0') {word.push_back(root->c);}
    if (root->counter > 0) {
      arr.push_back(make_pair(word, root->counter));
    }
    __dump(root->son, word, arr);
    if (!word.empty()) {word.pop_back();}
  }
public: 
  Trie() : root(new Node()) {}
  virtual ~Trie() {
    __clear(root);
  }
  virtual void dump(vector<pair<string, int>> & arr) {
    string word = "";
    __dump(root, word, arr);
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
    ++(root->counter);
  }
  virtual int count(const string & word) {
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
      if (ptr == nullptr) {return 0;}
    }
    return (root->counter);
  }
};

class Solution {
private:
  string iPath, oPath, sPath;
  Trie stopWords, record;
  bool printTot;

public:
  Solution(string i, string o, string s, bool p) :
    iPath(i), oPath(o), sPath(s), printTot(p) {
    initStopWords(sPath);
  }
  void initStopWords(const string & path) {
    ifstream ifs;
    streambuf* cinOrig;
    if (path != "") {
      ifs.open(path);
      cinOrig = cin.rdbuf(ifs.rdbuf());
    }
    string word;
    while (cin >> word) {
      stopWords.insert(word);
    }
    if (path != "") {
      cin.rdbuf(cinOrig);
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
      if (word[i] >= 'a' && word[i] <= 'z' || word[i] == '\'') {break;}
    }
    while (i < word.size()) {
      for (j = i + 1; j < word.size(); ++j) {
        if (!(word[j] >= 'a' && word[j] <= 'z')) {break;}
      }
      if (!(i + 1 == j && word[i] == '\'')) {
        words.push_back(word.substr(i, j - i));
      }
      for (i = j; i < word.size(); ++i) {
        if (word[i] >= 'a' && word[i] <= 'z' || word[i] == '\'') {break;}
      }
    }
  }
  void readArticle(const string & path) {
    ifstream ifs;
    streambuf* cinOrig;
    if (path != "") {
      ifs.open(path);
      cinOrig = cin.rdbuf(ifs.rdbuf());
    }
    string content;
    int64_t tot = 0;
    while (cin >> content) {
      vector<string> container;
      container.push_back(content);
      format(container);
      for (auto word : container) {
        if (stopWords.count(word) == 0) {
          record.insert(word);
          ++tot;
        }
      }
    }
    if (path != "") {
      cin.rdbuf(cinOrig);
    }
    if (printTot) {
      cout << "Total words: " << tot << endl;
    }
  }
  void sortWords(vector<pair<string, int>> & arr) {
    record.dump(arr);
    sort(arr.begin(), arr.end(), [](const pair<string, int> & pairX, const pair<string, int> & pairY) {
      return (pairX.second > pairY.second || pairX.second == pairY.second && pairX.first < pairY.first);
    });
  }
  void writeToFile(const string & path, const vector<pair<string, int>> & arr) {
    ofstream ofs;
    streambuf* coutOrig;
    if (path != "") {
      ofs.open(path);
      coutOrig = cout.rdbuf(ofs.rdbuf());
    }
    if (arr.empty()) {
      cout << "{}\n";
      return;
    }
    cout << "{\n\t\"" << arr[0].first << "\": " << arr[0].second;
    for (int i = 1; i < arr.size(); ++i) {
      cout << ",\n\t\"" << arr[i].first << "\": " << arr[i].second;
    }
    cout << "\n}\n";
    if (path != "") {
      cout.rdbuf(coutOrig);
    }
  }
  void solve() {
    readArticle(iPath);
    vector<pair<string, int>> arr;
    sortWords(arr);
    writeToFile(oPath, arr);
  }
};

signed main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  int opt;
  bool printTot = false;
  string iPath = "", oPath = "", sPath = "Stop Words.txt";
  while (~(opt = getopt(argc, argv, "i:o:s:w"))) {
    switch (opt) {
      case 'i': {
        iPath = ((optarg == "-" || optarg == "--") ? "" : optarg);
      break;}
      case 'o': {
        oPath = ((optarg == "-" || optarg == "--") ? "" : optarg);
      break;}
      case 's': {
        sPath = ((optarg == "-" || optarg == "--") ? "" : optarg);
      break;}
      case 'w': {
        printTot = true;
      break;}
      default: {
        cerr << "Error arguments" << endl;
        exit(1);
      break;}
    }
  }
  if (iPath == "" && sPath == "") {
    cerr << "There cannot be more than one stream read from standard input at the same time" << endl;
    exit(1);
  }
  Solution s(iPath, oPath, sPath, printTot);
  s.solve();
}