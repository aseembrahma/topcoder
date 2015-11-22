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

class KingdomAndTrees {
  /*
   * When looking at the ith tree the max diff should atleast be i, so as to be
   * able to support an ordering like x, x+1, x+2, ...
   */

public:
  int minLevel(vector<int> heights) {
    int result = 0;
    for (int i = 1; i < heights.size(); ++i) {
      if (heights[i] <= heights[i - 1]) {
        int diff = heights[i - 1] - heights[i];
        if (diff % 2)
          diff = (diff + 1) / 2;
        else
          diff = (diff / 2) + 1;

        diff = max(diff, i);
        result = max(result, diff);
      }
    }
    return result;
  }

  bool runTest(vector<int> heights, int solution) {
    int output = minLevel(heights);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(heights);
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
  KingdomAndTrees test;
  {
    test.runTest({9, 5, 11}, 3);
    test.runTest({5, 8}, 0);
    test.runTest({1, 1, 1, 1, 1}, 4);
    test.runTest({548, 47, 58, 250, 2012}, 251);
  }
}

