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

class XorTravelingSalesman {
public:
  int maxProfit(vector<int> cityValues, vector<string> roads) {
    vector<bool> g_visited(cityValues.size(), false);
    // 1-indexed
    vector<int> max_bit_set(cityValues.size(), 0);
    for (int i = 0; i < cityValues.size(); ++i) {
      int j = 0;
      for (int temp = cityValues[i]; temp; ++j, temp = temp >> 1);
      max_bit_set[i] = j;
      cout << j << endl;
    }

    queue<int> gq;
    g_visited[0] = true;
    gq.push(0);

    while (!gq.empty()) {

    }

    int max_profit = 0;
    return max_profit;
  }

  bool runTest(vector<int> cityValues, vector<string> roads, int solution) {
    int output = maxProfit(cityValues, roads);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(cityValues);
      print_vector(roads);
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
  XorTravelingSalesman test;
  {
    test.runTest(
      vector<int>{0, 7, 11, 5, 2},
      vector<string>{"NYNYY",
                     "YNYNN",
                     "NYNNN",
                     "YNNNN",
                     "YNNNN"},
      14);
  }
}

