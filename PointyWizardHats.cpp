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

class PointyWizardHats {
  /*
   * The radius of a top hat must be less than a bottom hat. In addition, if
   * the apexes touch, then we get 2 similar triangles - so Htop/Rtop = 
   * Hbottom/Rbottom. So for the apexes to not touch, Htop must be greater than
   * (Hbottom/Rbottom) * Rtop.
   * Create a graph with an edge from each top hat to a potential bottom hat.
   * Also add a source and a sink.
   * The numbering of the vertices would then be [0 (source), tn top hat nodes,
   * bn bottom hat nodes, tn + bn + 1 (sink node)]
   * When each edge is added with capacity 1, also add a reverse edge with
   * capacity 0.
   * Now check if there is an augmenting path/path from src to sink - and if
   * so, we can push one more unit of flow.
   */

public:
  int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius) {
    int tn = topHeight.size(), bn = bottomHeight.size();
    vector<vector<int> > edges(tn + bn + 2, vector<int>(tn + bn + 2, -1));
    for (int i = 0; i < tn; ++i) {
      edges[0][1 + i] = 1;
      edges[1 + i][0] = 0;
      for (int j = 0; j < bn; ++j) {
        if (topRadius[i] < bottomRadius[j]) {
          if (double(topHeight[i]) >
             (double(bottomHeight[j] * topRadius[i]) / bottomRadius[j])) {
            edges[1 + i][1 + tn + j] = 1;
            edges[1 + tn + j][1 + i] = 0;
          }
        }
      }
    }

    for (int i = 0; i < bn; ++i) {
      edges[1 + tn + i][1 + tn + bn] = 1;
      edges[1 + tn + bn][1 + tn + i] = 0;
    }

    int result = 0;
    while (true) {
      // find path
      queue<int> q;
      unordered_map<int, bool> visited;
      unordered_map<int, int> prev;

      q.push(0);
      visited[0] = true;
      prev[0] = -1;

      while (!q.empty()) {
        int u = q.front();
        q.pop();
        bool sink_found = false;

        for (int i = 0; i < edges[u].size(); ++i) {
          int v = i;
          if (!visited[v] && edges[u][v] > 0) {
            q.push(v);
            visited[v] = true;
            prev[v] = u;

            if (v == tn + bn + 1) {
              sink_found = true;
              break;
            }
          }
        }
        if (sink_found)
          break;
      }

      if (visited[tn + bn + 1] == false)
        break;

      ++result;

      for (int i = tn + bn + 1; prev[i] != -1; i = prev[i]) {
        edges[prev[i]][i] -= 1;
        edges[i][prev[i]] += 1;
      }
    }
    return result;
  }

  bool runTest(vector<int> th, vector<int> tr, vector<int> bh, vector<int> br, int solution) {
    int output = getNumHats(th, tr, bh, br);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(th);
      print_vector(tr);
      print_vector(bh);
      print_vector(br);
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
  PointyWizardHats test;
  {
    test.runTest({30}, {3}, {3}, {30}, 1);
  }
  {
    test.runTest({4,4}, {4,3}, {5,12}, {5,4}, 1);
  }
  {
    test.runTest({3}, {3}, {1,1}, {2,4}, 1);
  }
  {
    test.runTest({10,10}, {2,5}, {2,9}, {3,6}, 2);
  }
  {
    test.runTest({3,4,5}, {5,4,3}, {3,4,5}, {3,8,5}, 2);
  }
  {
    test.runTest({1,2,3,4,5}, {2,3,4,5,6}, {2,3,4,5,6}, {1,2,3,4,5}, 0);
  }
  {
    test.runTest({123,214,232,323,342,343},
                 {123,123,232,123,323,434},
                 {545,322,123,545,777,999},
                 {323,443,123,656,767,888}, 5);
  }
  {
    test.runTest({999,999,999,10000,10000,10000},
                 {10000,10000,10000,1,2,3},
                 {2324,2323,234,5454,323,232},
                 {1,2,3222,434,5454,23}, 3);
  }
}

