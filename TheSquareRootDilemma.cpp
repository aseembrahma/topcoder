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

class TheSquareRootDilemma {
  vector<int> squares_lt_max_arr;
  map<int, bool> squares_lt_max;

public:
  int countPairs(int N, int M) {
    int solution = 0;

    static bool is_inited = false;
    if (!is_inited) {
      for (int root = 1; root <= 77777; ++root)
        squares_lt_max[root * root] = true;
      is_inited = true;
    }

    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= M; ++j) {
        if (squares_lt_max[i * j]) {
#if DEBUG
          cout << "(" << i << ", " << j << ")" << endl;
#endif
          solution++;
        }
      }
    }

    return solution;
  }

  bool runTest(int N, int M, int solution) {
    int output = countPairs(N, M);

    if (output != solution)
    {
      cerr << "Failed for " << N << ", " << M << endl;
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
  TheSquareRootDilemma test;
  test.runTest(2, 2, 2);
  test.runTest(10, 1, 3);
  test.runTest(3, 8, 5);
  test.runTest(100, 100, 310);
}

