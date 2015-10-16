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

class Stamp {
public:
  int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
    int N = desiredColor.size();

    vector<vector<int> > v(N + 1, vector<int>(N + 1, numeric_limits<int>::max()));
    for (int i = 0; i <  v[0].size(); ++i)
      v[0][i] = 0;

    for (int i = 1; i <= N; ++i) {
      set<char> colors;
      for (int j = i; j >= 1; --j) {
        if (desiredColor[j - 1] != '*') {
          colors.insert(desiredColor[j - 1]);
          if (colors.size() > 1)
            break;
        }
        int stampSize = i - j + 1;
        for (int k = i - stampSize; k < i; ++k) {
          if (v[k][stampSize] != numeric_limits<int>::max()) {
            v[i][stampSize] = min(v[i][stampSize], pushCost + v[k][stampSize]);
          }
        }
      }
      //print_vector(v[i]);
    }

    int minCost = v[N][0];
    for (int i = 1; i <= N; ++i)
      if (v[N][i] != numeric_limits<int>::max())
        minCost = min(minCost, (stampCost * i) + v[N][i]);
    return minCost;
  }

  bool runTest(string d, int s, int p, int solution) {
    int output = getMinimumCost(d, s, p);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      cerr << d << ", " << s << ", " << p << endl;
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
  Stamp test;
  {
    test.runTest("RRGGBB", 1, 1, 5);
  }
  {
    test.runTest("R**GB*", 1, 1, 5);
  }
  {
    test.runTest("BRRB", 2, 7, 30);
  }
  {
    test.runTest("R*RR*GG", 10, 58, 204);
  }
  {
    test.runTest("*B**B**B*BB*G*BBB**B**B*", 5, 2, 33);
  }
  {
    test.runTest("*R*RG*G*GR*RGG*G*GGR***RR*GG", 7, 1, 30);
  }
}

