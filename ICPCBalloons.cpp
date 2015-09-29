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

/*
// Balloon count and size
typedef struct {
  int count, size, color;
} bc;

struct bcCompare {
  bool operator() (bc lhs, bc rhs) {
    return (lhs.count > rhs.count);
  }
};
*/

class ICPCBalloons {

public:
  int repaintHelper(vector<int> &accepted, vector<int> balloonCount) {

    int solution = 0;
    for (int i = 0; i < accepted.size(); ++i) {
      if (i < balloonCount.size()) {
        if (balloonCount[i] < accepted[i]) {
          solution += (accepted[i] - balloonCount[i]);
        }
      }
      else {
        solution += accepted[i];
      }
    }
    return solution;
  }

  int minRepaintings(vector<int> balloonCount,
                     string balloonSize,
                     vector<int> maxAccepted) {
    if (accumulate(balloonCount.begin(), balloonCount.end(), 0) <
        accumulate(maxAccepted.begin(), maxAccepted.end(), 0)) {
      return -1;
    }

    vector<int> med_bs, large_bs;
    int num_med_bs = 0, num_large_bs = 0;
    for (int i = 0; i < balloonCount.size(); ++i) {
      if ('L' == balloonSize[i]) {
        large_bs.push_back(balloonCount[i]);
        num_large_bs += balloonCount[i];
      }
      else {
        med_bs.push_back(balloonCount[i]);
        num_med_bs += balloonCount[i];
      }
    }

    int solution = numeric_limits<int>::max();

    sort(large_bs.begin(), large_bs.end(), greater<int>());
    sort(med_bs.begin(), med_bs.end(), greater<int>());

    if (0 == num_med_bs || 0 == num_large_bs) {
      sort(maxAccepted.begin(), maxAccepted.end(), greater<int>());
      sort(balloonCount.begin(), balloonCount.end(), greater<int>());
      solution = repaintHelper(maxAccepted, balloonCount);
    }
    else {
      // enumerate all sets
      for (int i = 0; i < (1 << maxAccepted.size()); ++i) {
        // let's say 0 === medium, 1 === large
        vector<int> med;
        vector<int> large;
        int num_med = 0, num_large = 0;

        int i_copy = i;

        // Examine each of the j bits of i
        for (int j = 0; j < maxAccepted.size(); ++j) {
          if (0 == (i_copy & 1)) {
            num_med += maxAccepted[j];
            med.push_back(maxAccepted[j]);
          }
          else {
            num_large += maxAccepted[j];
            large.push_back(maxAccepted[j]);
          }
          i_copy = (i_copy >> 1);
        }

        if (num_med <= num_med_bs && num_large <= num_large_bs) {
          // calculate the min
          sort(large.begin(), large.end(), greater<int>());
          sort(med.begin(), med.end(), greater<int>());
          int temp_soln = repaintHelper(med, med_bs) +
                          repaintHelper(large, large_bs);
    
          solution = min(solution, temp_soln);
        }
      }
    }

    if (numeric_limits<int>::max() == solution)
      solution = -1;

    return solution;
  }

  bool runTest(vector<int> bCount,
               string bSize,
               vector<int> maxA,
               int solution) {
    int output = minRepaintings(bCount, bSize, maxA);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(bCount);
      print_vector(maxA);
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
  ICPCBalloons test;
  {
    int balloonCount_arr[] = {100};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {1, 2, 3, 4, 5};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("L");

    test.runTest(balloonCount, balloonSize, maxAccepted, 10);
  }
  {
    int balloonCount_arr[] = {100};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {10, 20, 30, 40, 50};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("M");

    test.runTest(balloonCount, balloonSize, maxAccepted, -1);
  }
  {
    int balloonCount_arr[] = {5,6,1,5,6,1,5,6,1};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {7,7,4,4,7,7};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("MLMMLMMLM");

    test.runTest(balloonCount, balloonSize, maxAccepted, 6);
  }
  {
    int balloonCount_arr[] = {100, 100};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {50, 51, 51};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("ML");

    test.runTest(balloonCount, balloonSize, maxAccepted, -1);
  }
  {
    int balloonCount_arr[] = {8,5,1,4,1,1,3,1,3,3,5,4,5,6,9};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {3,5,3,3,5,6,4,6,4,2,3,7,1,5,2};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("MMMLLLMMLLMLMLM");

    test.runTest(balloonCount, balloonSize, maxAccepted, 5);
  }
  {
    int balloonCount_arr[] = {1,18,4,7,19,7,7,1,4,8,10,5,14,13,8,22,6,3,13,5,3,4,2,1,3,15,19,4,5,9,4,11,2,7,12,20,11,26,22,7,2,10,9,20,13,20,2,9,11,9};
    vector<int> balloonCount(balloonCount_arr,
                             balloonCount_arr + ARR_SIZE(balloonCount_arr));
    int maxAccepted_arr[] = {44,59,29,53,16,23,13,14,29,42,13,15,66,4,47};
    vector<int> maxAccepted(maxAccepted_arr,
                            maxAccepted_arr + ARR_SIZE(maxAccepted_arr));
    string balloonSize("LLMLLLLMLLLLLLLLLLLLMLLLLLLLLLLMMLMLLLMLLLLLLLLMLL");

    test.runTest(balloonCount, balloonSize, maxAccepted, 210);
  }
}

