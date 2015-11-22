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

class StrIIRec {
  /*
   * When looking at the ith tree the max diff should atleast be i, so as to be
   * able to support an ordering like x, x+1, x+2, ...
   */

public:
  string recovstr(int n, int minInv, string minStr) {
    string result(minStr);

    // add any missing letters
    for (int i = 0; i < n; ++i)
      if (result.find('a' + i) == string::npos)
        result += ('a' + i);

    // convert to numbers, for easier representation
    vector<int> v;
    for (int i = 0; i < result.size(); ++i)
      v.push_back(result[i] - 'a');

    // count the number of inversions
    vector<int> inv(v.size());
    int total_inv = 0;
    for (int i = 0; i < v.size() - 1; ++i) {
      if (i == 0)
        inv[i] = 0;
      else
        inv[i] = inv[i - 1];

      for (int j = i + 1; j < v.size(); ++j) {
        if (v[j] < v[i]) {
          ++inv[i];
          ++total_inv;
        }
      }
    }

    if (total_inv < minInv) {
      // find out how many letters from the end we need to reverse
      int i, prev_total_inv = inv.back();
      for (i = 2; i <= n; ++i) {
        total_inv = (i < n) ? inv[v.size() - i - 1] : 0;
        total_inv += ((i * (i - 1)) / 2);

        if (total_inv >= minInv) {
          if (total_inv > minInv) {
            --i;
            total_inv = prev_total_inv;
          }
          break;
        }
        prev_total_inv = total_inv;
      }

      //cout << i << ", " << total_inv << endl;
      sort(v.begin() + (v.size() - i), v.end(), greater<int>());
      --i;

      while (total_inv < minInv) {
        //print_vector(v);

        int j;
        for (j = v.size() - 2; j >= 0 && v[j] > v[j + 1]; --j);
        for (int k = v.size() - 1; k > j; --k) {
          if (v[k] > v[j]) {
            swap(v[j], v[k]);
            break;
          }
        }
        reverse(v.begin() + j + 1, v.end());

        total_inv = 0;
        for (int k = 0; k < v.size() - 1; ++k)
          for (int l = k + 1; l < v.size(); ++l)
            if (v[l] < v[k])
              ++total_inv;
      }
    }

    for (int i = 0; i < v.size(); ++i)
      result[i] = ('a' + v[i]);

    return result;
  }

  bool runTest(int n, int minInv, string minStr, string solution) {
    string output = recovstr(n, minInv, minStr);

    if (output != solution)
    {
      cerr << "Failed for " << n << ", " << minInv << ", " << minStr << endl;
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
  StrIIRec test;
  {
    test.runTest(2, 1, "ab", "ba");
    test.runTest(9, 1, "efcdgab", "efcdgabhi");
    test.runTest(11, 55, "debgikjfc", "kjihgfedcba");
    test.runTest(15, 0, "e", "eabcdfghijklmno");
    test.runTest(9, 20, "fcdebiha", "fcdehigba");
  }
}

