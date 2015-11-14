#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream> 
#include <queue>
#include <string>
#include <cmath>
#include <set>
#include <limits>
#include <numeric>
#include <bitset>
#include <stack>
#include <utility>
#include <unordered_set>

#define DEBUG 0
#define ARR_SIZE(x) ((sizeof(x)) / (sizeof(x[0])))
#define INF_INT numeric_limits<int>::max()
#define MIN_INT numeric_limits<int>::min()

using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int, int> pii;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

template <typename K, typename V>
V GetWithDef(const  std::map <K,V> & m, const K & key, const V & defval ) {
    typename std::map<K,V>::const_iterator it = m.find( key );
    if ( it == m.end() ) {
        return defval;
    }
    else {
        return it->second;
    }
}

template<typename T>
void print_vector(const vector<T> &v) {
  cerr << " { ";
  for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
    cerr << *it << ", ";
  }
  cerr << " } " << endl;
}

class CuttingBitString {
  /*
  */

  string convertDecimalToBinary(unsigned long long x) {
    string s;
    while (x) {
      s += ('0' + (x % 2));
      x = x / 2;
    }
    reverse(s.begin(), s.end());
    return s;
  }

public:
  int getmin(string s) {
    unordered_set<string> powers;

    for (unsigned long long i = 1; ; i *= 5) {
      string s = convertDecimalToBinary(i);
      if (s.size() > 50)
        break;
      else
        powers.insert(s);
    }

    vector<int> partial_soln(s.size(), INF_INT);

    for (int i = 0; i < s.size(); ++i) {
      if (powers.find(s.substr(0, i + 1)) != powers.end()) {
        partial_soln[i] = 1;
      }
      else {
        for (int j = 0; j < i; ++j) {
          if (partial_soln[j] != INF_INT &&
              powers.end() != powers.find(s.substr(j + 1, i - j))) {
            partial_soln[i] = min(partial_soln[i], 1 + partial_soln[j]);
          }
        }
      }
    }
    if (partial_soln.back() == INF_INT)
      return -1;
    else
      return partial_soln.back();
  }

  bool runTest(string s, int solution) {
    int output = getmin(s);

    if (output != solution)
    {
      cerr << "Failed for " << s << endl;
      cerr << "Expected: " << solution << endl;
      cerr << "Found instead:" << output << endl;
      return false;
    }
    else {
      return true;
    }
  }
};

int main(int argc, char* argv[]) {
  CuttingBitString test;
  {
    test.runTest("101101101", 3);
  }
  {
    test.runTest("1111101", 1);
  }
  {
    test.runTest("00000", -1);
  }
  {
    test.runTest("110011011", 3);
  }
  {
    test.runTest("1000101011", -1);
  }
  {
    test.runTest("111011100110101100101110111", 5);
  }
}

