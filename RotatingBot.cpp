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

class RotatingBot {
  /*
   * 
   */

public:
  int minArea(vector<int> moves) {
    int result = 0;
    typedef enum {
      EAST, NORTH, WEST, SOUTH, MAX_DIR
    } dir_t;
    vector<pair<int, bool> > bounds(4, make_pair(0, false));
    dir_t d = EAST;

    pii p(0, 0);
    set<pii> past;
    past.insert(p);

    for (int i = 0; i < moves.size(); ++i) {
      for (int j = 0; j < moves[i]; ++j) {
        if (EAST == d)
          ++p.first;
        else if (NORTH == d)
          ++p.second;
        else if (WEST == d)
          --p.first;
        else if (SOUTH == d)
          --p.second;

        //cout << p.first << ", " << p.second << endl;
        if (past.find(p) != past.end()) {
          return -1;
        }
        else {
          past.insert(p);
        }
      }

      // if this is not the last move then it must be that we stopped either 
      // because the next spot would have been a repeat or because we hit a
      // boundary
      if (i != moves.size() - 1) {
        pii q(p);
        if (EAST == d)
          ++q.first;
        else if (NORTH == d)
          ++q.second;
        else if (WEST == d)
          --q.first;
        else if (SOUTH == d)
          --q.second;

        // if the next spot was seen before then nothing to do
        if (past.find(q) == past.end()) {
          // if the next spot was not seen before then - either it hit a bound
          // in which case, nothing more to do...Or...we didn't have a bound
          // earlier but now have one...Or...we have a bound and it didn't hit
          // in which case we should flag an error
          if (bounds[d].second == true) {
            int spot_val = p.first;
            if (d % 2 == 1) {
              spot_val = p.second;
            }

            if (spot_val < bounds[d].first) {
              return -1;
            }
          }
          else {
            int bound_val = p.first;
            if (d % 2 == 1) {
              bound_val = p.second;
            }

            // there is no bound set
            if (((EAST == d || NORTH == d) && bound_val < 0) ||
                ((WEST == d || SOUTH == d) && bound_val > 0)) {
              return -1;
            }

            bounds[d] = make_pair(bound_val, true);
          }
        }
      }
      else {
        if (bounds[d].second == false) {
          int bound_val = p.first;
          if (d % 2 == 1) {
            bound_val = p.second;
          }

          // there is no bound set
          if (((EAST == d || NORTH == d) && bound_val < 0) ||
              ((WEST == d || SOUTH == d) && bound_val > 0)) {
            // Invalid bound, don't set
          }
          else {
            bounds[d] = make_pair(bound_val, true);
          }
        }
      }

      d = dir_t((d + 1) % MAX_DIR);
    }
    
    /*
    for (int i = 0; i < bounds.size(); ++i)
      cout << int(bounds[i].first) << ", ";
    cout << endl;
    */

    result = (bounds[EAST].first - bounds[WEST].first + 1) *
             (bounds[NORTH].first - bounds[SOUTH].first + 1);
    return result;
  }

  bool runTest(vector<int> v, int solution) {
    int output = minArea(v);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(v);
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
  RotatingBot test;
  {
    test.runTest({15}, 16);
  }
  {
    test.runTest({3,10}, 44);
  }
  {
    test.runTest({1,1,1,1}, -1);
  }
  {
    test.runTest({9,5,11,10,11,4,10}, 132);
  }
  {
    test.runTest({12,1,27,14,27,12,26,11,25,10,24,9,23,8,22,7,21,6,20,5,19,4,18,3,17,2,16,1,15}, 420);
  }
  {
    test.runTest({8,6,6,1}, -1);
  }
  {
    test.runTest({8,6,6}, 63);
  }
  {
    test.runTest({5,4,5,3,3}, 30);
  }
}

