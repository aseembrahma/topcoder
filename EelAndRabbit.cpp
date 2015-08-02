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

class EelAndRabbit {

public:
  int getmax(vector<int> l, vector<int> t) {
    int solution = 0;

    {
      map<int, int> time_to_overlaps;
      int max_overlap = 0, max_overlap_time = 0;

      for (size_t i = 0; i < t.size(); ++i) {
        for (int j = t[i]; j <= t[i] + l[i]; ++j) {
          time_to_overlaps[j]++;
          if (time_to_overlaps[j] > max_overlap) {
            max_overlap = time_to_overlaps[j];
            max_overlap_time = j;
          }
        }
      }

      solution += max_overlap;

      for (size_t i = 0; i < t.size(); ++i) {
        if (t[i] <= max_overlap_time && t[i] + l[i] >= max_overlap_time) {
          l.erase(l.begin() + i);
          t.erase(t.begin() + i);
        }
      }
    }

    {
      map<int, int> time_to_overlaps;
      int max_overlap = 0, max_overlap_time = 0;

      for (size_t i = 0; i < t.size(); ++i) {
        for (int j = t[i]; j <= t[i] + l[i]; ++j) {
          time_to_overlaps[j]++;
          if (time_to_overlaps[j] > max_overlap) {
            max_overlap = time_to_overlaps[j];
            max_overlap_time = j;
          }
        }
      }

      solution += max_overlap;
    }
    return solution;
  }

  bool runTest(vector<int> l, vector<int> t, int solution) {
    int output = getmax(l, t);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(l);
      print_vector(t);
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
  EelAndRabbit test;
  {
    int l_arr[] = {2, 4, 3, 2, 2, 1, 10};
    int t_arr[] = {2, 6, 3, 7, 0, 2, 0};
    vector<int> l(l_arr, l_arr + ARR_SIZE(l_arr));
    vector<int> t(t_arr, t_arr + ARR_SIZE(t_arr));
    test.runTest(l, t, 6);
  }
  {
    int l_arr[] = {1, 1, 1};
    int t_arr[] = {2, 0, 4};
    vector<int> l(l_arr, l_arr + ARR_SIZE(l_arr));
    vector<int> t(t_arr, t_arr + ARR_SIZE(t_arr));
    test.runTest(l, t, 2);
  }
  {
    int l_arr[] = {1};
    int t_arr[] = {1};
    vector<int> l(l_arr, l_arr + ARR_SIZE(l_arr));
    vector<int> t(t_arr, t_arr + ARR_SIZE(t_arr));
    test.runTest(l, t, 1);
  }
  {
    int l_arr[] = {8, 2, 1, 10, 8, 6, 3, 1, 2, 5};
    int t_arr[] = {17, 27, 26, 11, 1, 27, 23, 12, 11, 13};
    vector<int> l(l_arr, l_arr + ARR_SIZE(l_arr));
    vector<int> t(t_arr, t_arr + ARR_SIZE(t_arr));
    test.runTest(l, t, 7);
  }
}

