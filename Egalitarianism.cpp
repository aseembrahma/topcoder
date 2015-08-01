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

class Egalitarianism {

public:
  int maxDifference(vector<string> friends, int d) {
    int solution = 0;

    size_t max_depth = 0;

    // Run a BFS from each node
    for (size_t j = 0; j < friends.size(); ++j) {
      vector<bool> visited(friends.size());
      vector<size_t> depth(friends.size());
      queue<size_t> q;
      size_t visited_count = 0;

      for (size_t i = 0; i < friends.size(); ++i)
        visited[i] = false;

      q.push(j);
      depth[j] = 0;
      visited[j] = true;
      visited_count++;

      while (!q.empty()) {
        size_t v = q.front();
        q.pop();
        for (size_t i = 0; i < friends[v].size(); ++i) {
          if (friends[v][i] == 'Y' && false == visited[i]) {
            visited[i] = true;
            visited_count++;
            q.push(i);
            depth[i] = depth[v] + 1;
            max_depth = max(max_depth, depth[i]);
          }
        }
      }
      if (visited_count != friends.size()) {
        solution = -1;
        break;
      }
    }

    if (-1 != solution)
      solution = max_depth * d;

    return solution;
  }

  bool runTest(vector<string> friends, int d, int solution) {
    int output = maxDifference(friends, d);

    if (output != solution)
    {
      cerr << "Failed for d = " << d << endl;
      print_vector(friends);
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
  Egalitarianism test;
  {
    const char * friends_arr[] =
    {"NYN",
     "YNY",
     "NYN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 10, 20);
  }
  {
    const char * friends_arr[] =
    {"NN",
     "NN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 1, -1);
  }
  {
    const char * friends_arr[] =
    {"NNYNNN",
     "NNYNNN",
     "YYNYNN",
     "NNYNYY",
     "NNNYNN",
     "NNNYNN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 1000, 3000);
  }
  {
    const char * friends_arr[] =
    {"NNYN",
     "NNNY",
     "YNNN",
     "NYNN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 584, -1);
  }
  {
    const char * friends_arr[] =
    {"NYNYYYN",
     "YNNYYYN",
     "NNNNYNN",
     "YYNNYYN",
     "YYYYNNN",
     "YYNYNNY",
     "NNNNNYN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 5, 20);
  }
  {
    const char * friends_arr[] =
    {"NYYNNNNYYYYNNNN",
     "YNNNYNNNNNNYYNN",
     "YNNYNYNNNNYNNNN",
     "NNYNNYNNNNNNNNN",
     "NYNNNNYNNYNNNNN",
     "NNYYNNYNNYNNNYN",
     "NNNNYYNNYNNNNNN",
     "YNNNNNNNNNYNNNN",
     "YNNNNNYNNNNNYNN",
     "YNNNYYNNNNNNNNY",
     "YNYNNNNYNNNNNNN",
     "NYNNNNNNNNNNNNY",
     "NYNNNNNNYNNNNYN",
     "NNNNNYNNNNNNYNN",
     "NNNNNNNNNYNYNNN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 747, 2988);
  }
  {
    const char * friends_arr[] =
    {"NY",
     "YN"}
    ;
    vector<string> friends(friends_arr, friends_arr + ARR_SIZE(friends_arr));
    test.runTest(friends, 0, 0);
  }
}

