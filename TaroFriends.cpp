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

class TaroFriends {

public:
  int getNumber(vector <int> coordinates, int X) {
    sort(coordinates.begin(), coordinates.end());
    int low = coordinates[0];;
    int high = coordinates[coordinates.size() - 1];
    int key = low + ((high - low) / 2);
#if DEBUG
    cout << "low is " << low << endl;
    cout << "high is " << high << endl;
    cout << "key is " << key << endl;
#endif

    int elem_before_midpoint, elem_after_midpoint;
    {
      int lo = 0, hi = coordinates.size() - 1, mid;
      while ((hi - lo) > 1) {
        mid = (lo + hi) / 2;
        if (coordinates[mid] < key) {
          lo = mid;
        }
        else if (coordinates[mid] > key) {
          hi = mid;
        }
        else {
          // we have to make a choice here..i think it doesn't matter which
          // one we go with
          lo = mid - 1;
          hi = mid;
          break;
        }
      }
      elem_before_midpoint = coordinates[lo];
      elem_after_midpoint = coordinates[hi];
    }
    
#if DEBUG
    cout << "elem before midpoint " << elem_before_midpoint << endl;
    cout << "elem after midpoint " << elem_after_midpoint << endl;
#endif

    int elem_leftmost = min(coordinates[0] + X, elem_after_midpoint - X),
        elem_rightmost = max(coordinates[coordinates.size() - 1] - X,
                             elem_before_midpoint + X);
#if DEBUG
    cout << "elem leftmost " << elem_leftmost << endl;
    cout << "elem rightmost " << elem_rightmost << endl;
#endif

    return (elem_rightmost - elem_leftmost);
  }

  bool runTest(vector <int> coordinates, int X, int solution) {
    int output = getNumber(coordinates, X);

    if (output != solution)
    {
      cerr << "Failed for " << X << endl;
      print_vector(coordinates);
      cerr << "Expected: " << solution << endl;
      cerr << "Found instead:" << output << endl;
    }
  }
};

int main(int argc, char* argv[]) {
  TaroFriends test;
  {
    int coordinates[] = {4, 7, -7};
    vector<int> coordinates_vec(coordinates,
                                coordinates + ARR_SIZE(coordinates));
    test.runTest(coordinates_vec, 5, 4);
  }
  {
    int coordinates[] = {-100000000, 100000000};
    vector<int> coordinates_vec(coordinates,
                                coordinates + ARR_SIZE(coordinates));
    test.runTest(coordinates_vec, 100000000, 0);
  }
  {
    int coordinates[] = {3, 7, 4, 6, -10, 7, 10, 9, -5};
    vector<int> coordinates_vec(coordinates,
                                coordinates + ARR_SIZE(coordinates));
    test.runTest(coordinates_vec, 7, 7);
  }
  {
    int coordinates[] = {-4, 0, 4, 0};
    vector<int> coordinates_vec(coordinates,
                                coordinates + ARR_SIZE(coordinates));
    test.runTest(coordinates_vec, 4, 4);
  }
  {
    int coordinates[] = {7};
    vector<int> coordinates_vec(coordinates,
                                coordinates + ARR_SIZE(coordinates));
    test.runTest(coordinates_vec, 0, 0);
  }
}

