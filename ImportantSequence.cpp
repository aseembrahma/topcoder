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
#include <unordered_map>

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

class ImportantSequence {
  /*
   */

public:
  int getCount(vector<int> B, string operators) {
    pii range(1, INF_INT);

    for (int i = 0; i < operators.size(); ++i) {
      if ('+' == operators[i]) {
        range.second = min(range.second, B[i]);
      }
      else if ('-' == operators[i]){
        if (B[i] <= 0) {
          range.first -= B[i];
          range.second -= B[i];
        }
        else {
          range.first = max(range.first, 1 + B[i]);
        }
      }

      if (range.second < range.first) {
        return 0;
      }
    }

    if (INF_INT == range.second) {
      return -1;
    }
    else {
      return (range.second - range.first);
    }
  }

  bool runTest(vector<int> B, string operators, int solution) {
    int output = getCount(B, operators);

    if (output != solution)
    {
      cerr << "Failed for " << operators << endl;
      print_vector(B);
      cerr << "Expected: " << solution << endl;
      cerr << "Found instead: " << output << endl;
      return false;
    }
    else {
      return true;
    }
  }
};

int main(int argc, char* argv[]) {
  ImportantSequence test;
  {
    test.runTest({3, -1, 7}, "+-+", 2);
    test.runTest({1}, "-", -1);
    test.runTest({1}, "+", 0);
    test.runTest({10}, "+", 9);
    test.runTest({540, 2012, 540, 2012, 540, 2012, 540}, "-+-+-+-", 1471);
  }
}

