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

class PatrolRoute {
  /*
   * Each triplet of points can be thought to lie along/within a sub-rectangle
   * of the original grid.
   * [case 1]
   * If for the first column, the point chosen is neither the top-most nor the
   * bottom-most, then there are (r - 2) ways to choose this point.
   * Since the point for the first column was chosen to be an 'internal' point,
   * the point for the last column must be the top-most or bottom-most,
   * because otherwise the 3 points would define a smaller rectangle.
   * There are 2 ways to choose this point
   * For the 3rd point, which must lie along one of the remaining (c - 2)
   * columns, it must lie along the top row or the bottom row. We don't have a
   * choice of row since we must pick whatever was not picked for col 1.
   * So we have a choice of (c - 2) points
   *
   * [case 2]
   * If the point chosen from the 1st col is either the top-most or bottom-most
   * and the point chosen from the last col is also the top-most or bottom-most
   * then we have 2 ways to choose these points.
   * The 3rd point can lie anywhere within the inner rectangle of dimensions
   * (r - 2) * (c - 2)
   *
   * [case 3]
   * Point chosen from col1 is top-most or bottom-most (2 ways to choose), and
   * point in last col is internal ((r - 2) ways to choose)
   * then the 3rd point must lie along the top row or bottom row ((c - 2) ways
   * to choose)
   *
   * Overall: (2 + 2 + 2) * ((r - 2) * (c - 2))
   */

public:
  int countRoutes(int X, int Y, int minT, int maxT) {
    const int mod = 1000000007;
    int result = 0;
    for (int i = 3; i <= X; ++i) {
      for (int j = 3; j <= Y; ++j) {
        int perimeter = (2 * (i + j)) - 4;
        if (perimeter >= minT && perimeter <= maxT) {
          ULL n = (X - i + 1) * (Y - j + 1);
          ULL temp_result = 6 * (i - 2) * (j - 2);

          //cout << "[" << i << ", " << j << "] " <<  n << " x " << temp_result << endl;

          temp_result %= mod;
          temp_result *= n;
          temp_result %= mod;

          result += temp_result;
          result %= mod;
        }
      }
    }
    return result;
  }

  bool runTest(int X, int Y, int minT, int maxT, int solution) {
    int output = countRoutes(X, Y, minT, maxT);

    if (output != solution)
    {
      cerr << "Failed for " << X << ", " << Y << ", " << minT << ", " << maxT
           << endl;
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
  PatrolRoute test;
  {
    test.runTest(3, 3, 1, 20000, 6);
    test.runTest(3, 3, 4, 7, 0);
    test.runTest(4, 6, 9, 12, 264);
    test.runTest(7, 5, 13, 18, 1212);
    test.runTest(4000, 4000, 4000, 14000, 859690013);
  }
}

