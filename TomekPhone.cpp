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

class TomekPhone {

public:
  int minKeystrokes(vector<int> frequencies, vector<int> keySizes) {
    if (accumulate(keySizes.begin(), keySizes.end(), 0) < frequencies.size())
      return -1;

    // keyPresses stores how many letters can be accommodated on a  single
    // key press, on 2 key presses, ...
    vector<int> keyPresses(*max_element(keySizes.begin(), keySizes.end()));
    for (int i = 0; i < keySizes.size(); ++i) {
      for (int j = 0; j < keySizes[i]; ++j) {
        ++keyPresses[j];
      }
    }
    sort(frequencies.begin(), frequencies.end(), greater<int>());

    int solution = 0;
    for (int i = 0, j = 0;
         i < frequencies.size() && j < keyPresses.size();
         ++i) {
      solution += ((j + 1) * frequencies[i]);
      --keyPresses[j];
      if (0 == keyPresses[j])
        ++j;
    }

    return solution;
  }

  bool runTest(vector<int> freqs, vector<int> keysizes, int solution) {
    int output = minKeystrokes(freqs, keysizes);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(freqs);
      print_vector(keysizes);
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
  TomekPhone test;
  {
    int freq_arr[] = {7, 3, 4, 1};
    vector<int> freqs(freq_arr, freq_arr + ARR_SIZE(freq_arr));
    int keysizes_arr[] = {2, 2};
    vector<int> keysizes(keysizes_arr, keysizes_arr + ARR_SIZE(keysizes_arr));

    test.runTest(freqs, keysizes, 19);
  }
  {
    int freq_arr[] = {13, 7, 4, 20};
    vector<int> freqs(freq_arr, freq_arr + ARR_SIZE(freq_arr));
    int keysizes_arr[] = {2, 1};
    vector<int> keysizes(keysizes_arr, keysizes_arr + ARR_SIZE(keysizes_arr));

    test.runTest(freqs, keysizes, -1);
  }
  {
    int freq_arr[] = {11,23,4,50,1000,7,18};
    vector<int> freqs(freq_arr, freq_arr + ARR_SIZE(freq_arr));
    int keysizes_arr[] = {3,1,4};
    vector<int> keysizes(keysizes_arr, keysizes_arr + ARR_SIZE(keysizes_arr));

    test.runTest(freqs, keysizes, 1164);
  }
  {
    int freq_arr[] = {100,1000,1,10};
    vector<int> freqs(freq_arr, freq_arr + ARR_SIZE(freq_arr));
    int keysizes_arr[] = {50};
    vector<int> keysizes(keysizes_arr, keysizes_arr + ARR_SIZE(keysizes_arr));

    test.runTest(freqs, keysizes, 1234);
  }
  {
    int freq_arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
    vector<int> freqs(freq_arr, freq_arr + ARR_SIZE(freq_arr));
    int keysizes_arr[] = {10,10,10,10,10,10,10,10};
    vector<int> keysizes(keysizes_arr, keysizes_arr + ARR_SIZE(keysizes_arr));

    test.runTest(freqs, keysizes, 3353);
  }
}

