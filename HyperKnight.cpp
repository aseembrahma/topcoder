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

#define DEBUG 0
#define ARR_SIZE(x) ((sizeof(x)) / (sizeof(x[0])))
#define INF_INT numeric_limits<int>::max()

typedef unsigned long long ULL;
typedef long long LL;

using namespace std;

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

class HyperKnight {

  /*

  |          a      |                   |        a        |
  |_b__|____________|___________________|_________________|
  | 1  |      2     |         7         |     2'    |  1' |
  |____|____________|___________________|___________|_____|
  |    |            |                   |           |     |
  |  3 |      4     |         8         |     4'    |  3' |
  |    |            |                   |           |     |
  |____|____________|___________________|___________|_____|
  |    |            |                   .                 |
  |    |            |                   .                 |
  |    |            |                   .                 |
  |    |            |                   .                 |
  | 5  |      6     |         9         .                 |
  |    |            |                   .                 |
  |    |            |                   .                 |
  |    |            |                   .                 |
  |____|____________|....................                 |
  |                                                       |
  |                                                       |
  |                                                       |
  |                                                       |
  |                                                       |
  |_______________________________________________________|

  Square : moves
  1, 1' : 2
  2, 2' : 3
  3, 3' : 3
  4, 4' : 4
  5     : 4
  6     : 6
  7     : 4
  8     : 6
  9     : 8

  */

public:
  ULL countCells(int a, int b, int numRows, int numColumns, int k) {

    if (a < b)
      swap(a, b);

    if (2 == k) {
      return 4 * (b * b);
    }
    else if (3 == k) {
      return 8 * ((a - b) * b);
    }
    else if (4 == k) {
      return 2 * (
              (2 * ((a - b) * (a - b))) +
              (b * (numRows - (2 * a))) +
              (b * (numColumns - (2 * a)))
            );
    }
    else if (6 == k) {
      return 2 * (
                  ((a - b) * (numRows - (2 * a))) +
                  ((a - b) * (numColumns - (2 * a)))
                 );
    }
    else if (8 == k) {
      return ULL(numRows - (2 * a)) * (numColumns - (2 * a));
    }
    else {
      //if (0 == k || 1 == k || 5 == k || 7 == k)
      return 0;
    }
  }

  bool runTest(int a, int b, int r, int c, int k, ULL solution) {
    ULL output = countCells(a, b, r, c, k);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      cerr << a << ", " << b << ", " << r << ", " << c << ", " << k << endl;
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
  HyperKnight test;
  {
    test.runTest(2, 1, 8, 8, 4, 20);
  }
  {
    test.runTest(3, 2, 8, 8, 2, 16);
  }
  {
    test.runTest(1, 3, 7, 11, 0, 0);
  }
  {
    test.runTest(3, 2, 10, 20, 8, 56);
  }
  {
    test.runTest(1, 4, 100, 10, 6, 564);
  }
  {
    test.runTest(2, 3, 1000000000, 1000000000, 8, 999999988000000036ull);
  }
}

