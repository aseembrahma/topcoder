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

class EllysXors {
  /*
   */

public:
  LL getXor(LL l, LL r) {
    LL result = l;
    if (r - l < 4) {
      for (LL i = l + 1; i <= r; ++i)
        result = result ^ i;
    }
    else {
      LL l_ceil = ((l + 4) / 4) * 4;
      LL r_floor = (r / 4) * 4;

      for (LL i = l + 1; i < l_ceil; ++i)
        result = result ^ i;
      for (LL i = r_floor; i <= r; ++i)
        result = result ^ i;
    }
    return result;
  }

  LL getXor2(LL l, LL r) {
    LL result = l;
    for (LL i = l + 1; i <= r; ++i)
      result = result ^ i;
    return result;
  }

  bool runTest(LL l, LL r, LL solution) {
    LL output = getXor(l, r);

    if (output != solution)
    {
      cerr << "Failed for " << l << ", " << r << endl;
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
  EllysXors test;
  {
    test.runTest(3, 10, 8);
    test.runTest(5, 5, 5);
    test.runTest(13, 42, 39);
    test.runTest(666, 1337, 0);
    test.runTest(1234567, 89101112, 89998783);
  }
}

