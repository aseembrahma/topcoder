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

class LittleElephantAndString {

public:
  int getNumber(string A, string B) {
    string a = A, b = B;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b)
      return -1;
    if (A == B)
      return 0;

    int solution = 0;
//BACA

//ABAC
//ABCA
    for (int i = A.size() - 1, j = B.size() - 1; i >= 0 && j >= 0; --i) {
      if (A[i] != B[j]) {
        solution++;
      }
      else {
        --j;
      }
    }
    return solution;
  }

  bool runTest(string A, string B, int solution) {
    int output = getNumber(A, B);

    if (output != solution)
    {
      cerr << "Failed for " << A << ", " << B << endl;
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
  LittleElephantAndString test;
  test.runTest("ABC", "CBA", 2);
  test.runTest("A", "B", -1);
  test.runTest("AAABBB", "BBBAAA", 3);
  test.runTest("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ZYXWVUTSRQPONMLKJIHGFEDCBA", 25);
  test.runTest("A", "A", 0);
  test.runTest("DCABA", "DACBA", 2);
}

