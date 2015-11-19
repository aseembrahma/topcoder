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

class FoxPaintingBalls {
  /*
   * The colors R, G, B don't matter - the total number of balls is distributed
   * evenly, and one color might have 1 more than the others.
   * If the number of each color is the same, the problem is simplified
   * considerably.
   * If not, for example, if the number of balls required to make up the
   * triangle is {4, 3, 3}, then see how many times you can take out 10
   * (4 + 3 + 3) from each of the colors.
   * Once that step is complete, run a brute force.
   */

public:
  LL theMax(LL R, LL G, LL B, int N) {
    vector<LL> colors;
    colors.push_back(R);
    colors.push_back(G);
    colors.push_back(B);

    LL total_balls = (N * (N + 1)) / 2;
    int lo_balls, hi_balls;
    lo_balls = hi_balls = total_balls / 3;

    bool all_eq = true;
    if (total_balls % 3 == 1) {
      all_eq = false;
      ++hi_balls;
    }

    LL result = 0;
    sort(colors.begin(), colors.end(), greater<LL>());
    if (all_eq)
      return (colors.back() / lo_balls);

    LL temp = colors.back() / total_balls;
    result += (temp  * 3);
    temp *= total_balls;
    for (int i = 0; i < colors.size(); ++i)
      colors[i] -= temp;

    vector<LL> balls;
    balls.push_back(hi_balls);
    balls.push_back(lo_balls);
    balls.push_back(lo_balls);
    while (colors.front() >= balls[0]) {
      for (int i = 0; i < colors.size(); ++i) {
        colors[i] -= balls[i];
      }
      ++result;
      sort(colors.begin(), colors.end(), greater<LL>());
    }

    return result;
  }

  bool runTest(LL R, LL G, LL B, int N, LL solution) {
    LL output = theMax(R, G, B, N);

    if (output != solution)
    {
      cerr << "Failed for " << R << ", " << G << ", " << B << ", " << N << endl;
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
  FoxPaintingBalls test;
  {
    test.runTest(2, 2, 2, 3, 1);
  }
  {
    test.runTest(1, 2, 3, 3, 0);
  }
  {
    test.runTest(8, 6, 6, 4, 2);
  }
  {
    test.runTest(7, 6, 7, 4, 2);
  }
  {
    test.runTest(100, 100, 100, 4, 30);
  }
  {
    test.runTest(1, 1, 1, 1, 3);
  }
  {
    test.runTest(19330428391852493, 48815737582834113, 11451481019198930, 3456, 5750952686);
  }
}

