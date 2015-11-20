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

class ColorfulChocolates {
  /*
   * For each letter, record the positions that it occurs in, into a set
   * For each such set, for each entry, see how many letters you can bring
   * in adjacent to that entry, without exceeding the number of swaps
   * For example, if 'B' occurs at positions {1, 2, 4, 6, 7}, and if in the
   * current iteration we are considering the entry for position 4, then
   * maintain a list of iterators encompassing how many positions we are spread
   * over, and a list of position indices representing the actual spread.
   * In this case, we start with iterators to [4, 4], and indices [4, 4]. When
   * we combine the letter at position 2, we update to [2, 4], indices [3, 4]
   * because we have now dealt with the letter at position 2, and brought it
   * over to position 3
   */

public:
  int maximumSpread(string chocolates, int maxSwaps) {
    int result = 0;
    unordered_map<char, set<int> > m;
    for (int i = 0; i < chocolates.size(); ++i) {
      m[chocolates[i]].insert(i); 
    }
    for (unordered_map<char, set<int> >::iterator it = m.begin();
         it != m.end();
         ++it) {
      //cout << it->first << endl;
      set<int>::iterator set_last = prev(it->second.end());
      for (set<int>::iterator it2 = it->second.begin();
           it2 != it->second.end();
           ++it2) {
        int swapsLeft = maxSwaps;
        int spread = 1;
        pair<set<int>::iterator, set<int>::iterator> endpts = make_pair(it2,
                                                                        it2);
        pair<int, int> endidx = make_pair(*it2, *it2);

        while (swapsLeft > 0 &&
!(endpts.first == it->second.begin() && endpts.second == set_last)) {
          int lb_diff = numeric_limits<int>::max();
          if (endpts.first != it->second.begin())
            lb_diff =  endidx.first - (*(prev(endpts.first)));

          int ub_diff = numeric_limits<int>::max();
          if (endpts.second != set_last)
            ub_diff = *(next(endpts.second)) - endidx.second;

          int diff;
          if (lb_diff <= ub_diff) {
            --endpts.first;
            --endidx.first;
            diff = lb_diff;
          }
          else {
            ++endpts.second;
            ++endidx.second;
            diff = ub_diff;
          }
          //cout << *endpts.first << ", " << *endpts.second << endl;
          //cout << endidx.first << ", " << endidx.second << endl;
          swapsLeft -= (diff - 1);
          if (swapsLeft >= 0)
            ++spread;
        }

        //cout << "spread " << spread << endl;
        result = max(result, spread);
      }
    }
    return result;
  }

  bool runTest(string chocolates, int maxSwaps, int solution) {
    int output = maximumSpread(chocolates, maxSwaps);

    if (output != solution)
    {
      cerr << "Failed for " << chocolates << ", " << maxSwaps << endl;
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
  ColorfulChocolates test;
  {
    test.runTest("ABCDCBC", 1, 2);
  }
  {
    test.runTest("ABCDCBC", 2, 3);
  }
  {
    test.runTest("ABBABABBA", 3, 4);
  }
  {
    test.runTest("ABBABABBA", 4, 5);
  }
  {
    test.runTest("QASOKZNHWNFODOQNHGQKGLIHTPJUVGKLHFZTGPDCEKSJYIWFOO", 77, 5);
  }
}

