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

class UndoHistory {

public:
  int minPresses(vector<string> lines) {
    int solution = 0;
    const int undo_hist_cost = 2;
    const int char_key_cost = 1;
    const int enter_key_cost = 1;

    set<string> undo_set;
    string text_buffer;

    for (size_t i = 0; i < lines.size(); ++i) {
      size_t j = lines[i].size();
      size_t tb_size = text_buffer.size();

      if (tb_size > 0 &&
          tb_size <= j &&
          lines[i].substr(0, tb_size) == text_buffer) {
        j = tb_size;
      }
      else {
        for (;
             j >= 1 && undo_set.find(lines[i].substr(0, j)) == undo_set.end();
             --j);
        if (0 != j) {
          text_buffer = lines[i].substr(0, j);
        }
        if (i > 0)
          solution += undo_hist_cost;
      }

      for (j++; j <= lines[i].size(); ++j) {
        undo_set.insert(lines[i].substr(0, j));
        solution += char_key_cost;
      }

      solution += enter_key_cost;
      text_buffer = lines[i];
    }
    return solution;
  }

  bool runTest(vector<string> lines, int solution) {
    int output = minPresses(lines);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(lines);
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
  UndoHistory test;
  {
    const char * lines_arr[] = {"tomorrow", "topcoder"};
    vector<string> lines(lines_arr, lines_arr + ARR_SIZE(lines_arr));
    test.runTest(lines, 18);
  }
  {
    const char * lines_arr[] = {"a","b"};
    vector<string> lines(lines_arr, lines_arr + ARR_SIZE(lines_arr));
    test.runTest(lines, 6);
  }
  {
    const char * lines_arr[] = {"a", "ab", "abac", "abacus"};
    vector<string> lines(lines_arr, lines_arr + ARR_SIZE(lines_arr));
    test.runTest(lines, 10);
  }
  {
    const char * lines_arr[] = {"pyramid", "sphinx", "sphere", "python",
                                "serpent"};
    vector<string> lines(lines_arr, lines_arr + ARR_SIZE(lines_arr));
    test.runTest(lines, 39);
  }
  {
    const char * lines_arr[] = {"ba","a","a","b","ba"};
    vector<string> lines(lines_arr, lines_arr + ARR_SIZE(lines_arr));
    test.runTest(lines, 13);
  }
}

