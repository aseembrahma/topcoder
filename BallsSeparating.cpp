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

class BallsSeparating {

public:
  int minOperations(vector<int> red, vector<int> green, vector<int> blue) {
    int solution = 0;
    vector<int> redCost, greenCost, blueCost;

    if (red.size() < 3)
      return -1;

    for (size_t i = 0; i < red.size(); ++i) {
      redCost[i] = green[i] + blue[i];
      greenCost[i] = red[i] + blue[i];
      blueCost[i] = red[i] + green[i];
    }

    for (size_t i = 0; i < red.size(); ++i) {
      if (red.size() - i == 2) {

      }
      else {
        int red_top = redQ.top(),
            green_top = greenQ.top(),
            blue_top = blueQ.top();;

        if (red_top <= green_top && red_top <= blue_top) {
          solution += 0;
        }
      }
    }
    return solution;
  }

  bool runTest(vector<int> red, vector<int> green, vector<int> blue, int solution) {
    int output = minOperations(red, green, blue);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(red);
      print_vector(green);
      print_vector(blue);
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
  BallsSeparating test;
  {
    int red_arr[] = {1, 1, 1};
    int green_arr[] = {1, 1, 1};
    int blue_arr[] = {1, 1, 1};
    vector<int> red(red_arr, red_arr + ARR_SIZE(red_arr));
    vector<int> green(green_arr, green_arr + ARR_SIZE(green_arr));
    vector<int> blue(blue_arr, blue_arr + ARR_SIZE(blue_arr));
    test.runTest(red, green, blue, 6);
  }
  {
    int red_arr[] = {5};
    int green_arr[] = {6};
    int blue_arr[] = {8};
    vector<int> red(red_arr, red_arr + ARR_SIZE(red_arr));
    vector<int> green(green_arr, green_arr + ARR_SIZE(green_arr));
    vector<int> blue(blue_arr, blue_arr + ARR_SIZE(blue_arr));
    test.runTest(red, green, blue, -1);
  }
  {
    int red_arr[] = {4, 6, 5, 7};
    int green_arr[] = {7, 4, 6, 3};
    int blue_arr[] = {6, 5, 3, 8};
    vector<int> red(red_arr, red_arr + ARR_SIZE(red_arr));
    vector<int> green(green_arr, green_arr + ARR_SIZE(green_arr));
    vector<int> blue(blue_arr, blue_arr + ARR_SIZE(blue_arr));
    test.runTest(red, green, blue, 37);
  }
  {
    int red_arr[] = {7, 12, 9, 9, 7};
    int green_arr[] = {7, 10, 8, 8, 9};
    int blue_arr[] = {8, 9, 5, 6, 13};
    vector<int> red(red_arr, red_arr + ARR_SIZE(red_arr));
    vector<int> green(green_arr, green_arr + ARR_SIZE(green_arr));
    vector<int> blue(blue_arr, blue_arr + ARR_SIZE(blue_arr));
    test.runTest(red, green, blue, 77);
  }
  {
    int red_arr[] = {842398, 491273, 958925, 849859, 771363, 67803, 184892, 391907, 256150, 75799};
    int green_arr[] = {268944, 342402, 894352, 228640, 903885, 908656, 414271, 292588, 852057, 889141};
    int blue_arr[] = {662939, 340220, 600081, 390298, 376707, 372199, 435097, 40266, 145590, 505103};
    vector<int> red(red_arr, red_arr + ARR_SIZE(red_arr));
    vector<int> green(green_arr, green_arr + ARR_SIZE(green_arr));
    vector<int> blue(blue_arr, blue_arr + ARR_SIZE(blue_arr));
    test.runTest(red, green, blue, 7230607);
  }
}

