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

#define DEBUG 0
#define ARR_SIZE(x) ((sizeof(x)) / (sizeof(x[0])))

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

class JumpFurther {

public:
  int furthest(int N, int badStep) {
    int solution = (N * (N + 1)) / 2;

    bool found = false;
    int i;
    for (i = 1; i < N; ++i) {
      if ((i * (i + 1)) / 2 == badStep) {
        found = true;
        break;
      }
    }
    if (found) {
      if (i > 1)
        solution -= (i - 1);
      else
        solution -= i;
    }
    return solution;
  }

  bool runTest(int N, int badStep, int solution) {
    int output = furthest(N, badStep);

    if (output != solution)
    {
      cerr << "Failed for " << N << ", " << badStep << endl;
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
  JumpFurther test;
  test.runTest(2, 2, 3);
  test.runTest(2, 1, 2);
  test.runTest(3, 3, 5);
  test.runTest(1313, 5858, 862641);
  test.runTest(1, 757065, 1);
}

