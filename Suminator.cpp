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

class Suminator {
  /*
    Rather than trying to replace -1 with some number and summing, keep track
    of the indices that would get summed up if the -1 were replace by 0, and if
    it were replaced by some positive number
  */

public:
  int findMissing(vector<int> program, int wantedResult) {
    vector<int> empty;
    {
      // If -1 were replaced by 0
      stack<vector<int> > s;
      for (int i = 0; i < program.size(); ++i) {
        if (0 == program[i] || -1 == program[i]) {
          vector<int> u(empty);
          if (!s.empty()) {
            u = s.top();
            s.pop();
          }

          vector<int> v(empty);
          if (!s.empty()) {
            v = s.top();
            s.pop();
          }

          vector<int> w(u.begin(), u.end());
          w.insert(w.end(), v.begin(), v.end());
          //print_vector(w);
          if (!w.empty())
            s.push(w);
        }
        else {
          vector<int> u(1, i);
          //print_vector(u);
          s.push(u);
        }
      }

      int sum = 0;
      vector<int> u(empty);
      if (!s.empty()) {
        u = s.top();
      }
      //print_vector(u);
      for (int i = 0; i < u.size(); ++i) {
        if (program[u[i]] != -1) {
          int new_sum = sum + program[u[i]];
          if (new_sum < sum)
            return -1;
          else
            sum = new_sum;
        }
      }

      if (sum == wantedResult)
        return 0;
    }
    {
      // if -1 were replaced by a positive number
      int idx = 0;
      stack<vector<int> > s;
      for (int i = 0; i < program.size(); ++i) {
        if (0 == program[i]) {
          vector<int> u(empty);
          if (!s.empty()) {
            u = s.top();
            s.pop();
          }

          vector<int> v(empty);
          if (!s.empty()) {
            v = s.top();
            s.pop();
          }

          vector<int> w(u.begin(), u.end());
          w.insert(w.end(), v.begin(), v.end());
          if (!w.empty())
            s.push(w);
        }
        else {
          if (-1 == program[i])
            idx = i;

          vector<int> u(1, i);
          s.push(u);
        }
      }

      int sum = 0;
      vector<int> u(empty);
      if (!s.empty()) {
        u = s.top();
      }
      if (find(u.begin(), u.end(), idx) == u.end())
        return -1;

      for (int i = 0; i < u.size(); ++i) {
        if (program[u[i]] != -1) {
          int new_sum = sum + program[u[i]];
          if (new_sum < sum)
            return -1;
          else
            sum = new_sum;
        }
      }

      if (wantedResult > sum)
        return (wantedResult - sum);
      else
        return -1;
    }
    return -1;
  }

  bool runTest(vector<int> program, int wantedResult, int solution) {
    int output = findMissing(program, wantedResult);

    if (output != solution)
    {
      cerr << "Failed for " << wantedResult << endl;
      print_vector(program);
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
  Suminator test;
  {
    test.runTest({7,-1,0}, 10, 3);
  }
  {
    test.runTest({100, 200, 300, 0, 100, -1}, 600, 0);
  }
  {
    test.runTest({-1, 7, 3, 0, 1, 2, 0, 0}, 13, 0);
  }
  {
    test.runTest({-1, 8, 4, 0, 1, 2, 0, 0}, 16, -1);
  }
  {
    test.runTest({1000000000, 1000000000, 1000000000,  1000000000, -1, 0, 0, 0, 0}, 1000000000, -1);
  }
}

