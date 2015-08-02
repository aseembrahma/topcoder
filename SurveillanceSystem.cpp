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

class SurveillanceSystem {

#if DEBUG
  static const size_t MAX_N = 50;
  size_t NChooseK[MAX_N + 1][MAX_N + 1];
#endif

public:
  string getContainerInfo(string containers, vector<int> reports, int L) {
    string solution = containers;
    map<size_t, vector<size_t> > num_containers_to_start_pos;

#if DEBUG
    static bool init = false;
    if (false == init) {
      for (size_t i = 0; i < MAX_N + 1; ++i) {
        for (size_t j = 0; j <= i; ++j) {
          if (0 == j || j == i)
            NChooseK[i][j] = 1;
          else
            NChooseK[i][j] = NChooseK[i - 1][j - 1] + NChooseK[i - 1][j];
        }
      }
      init = true;
    }
#endif

    for (size_t i = 0, num_containers = 0;
         i < (containers.size() - L + 1);
         ++i) {
      if (0 == i) {
        for (size_t j = 0; j < L; ++j)
          if (containers[j] == 'X')
            num_containers++;
      }
      else {
        if (containers[i - 1] == 'X')
          num_containers--;
        if (containers[i + L - 1] == 'X')
          num_containers++;
      }
      num_containers_to_start_pos[num_containers].push_back(i);
    }

#if DEBUG
    for (map<size_t, vector<size_t> >::iterator it =
                                          num_containers_to_start_pos.begin();
         it != num_containers_to_start_pos.end();
         ++it) {
      cout << "[" << it->first << "]: ";
      print_vector(it->second);
    }
#endif

    for (size_t i = 0; i < solution.size(); ++i)
      solution[i] = '-';

    map<int, size_t> unique_reports;
    for (size_t i = 0; i < reports.size(); ++i)
      unique_reports[reports[i]]++;

    for (map<int, size_t>::iterator it = unique_reports.begin();
         it != unique_reports.end();
         ++it) {

      vector<size_t> temp(containers.size());
      vector<size_t> start_positions = num_containers_to_start_pos[it->first];

      for (size_t i = 0; i < start_positions.size(); ++i) {
        for (size_t j = 0; j < L; ++j) {
          temp[j + start_positions[i]]++;
        }
      }

      for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] > 0 && solution[i] != '+') {
          size_t n = start_positions.size() - temp[i];
          size_t k = it->second;
#if DEBUG
          cout << temp[i] << ", " << n << ", " << k << ", " << it->first << endl;
#endif
          if (n < k /*|| (n - k) <= 1 || k == n - 1*/) {
            solution[i] = '+';
          }
          else {
            if (solution[i] == '-') {
              solution[i] = '?';
            }
          }
        }
      }
    }
    return solution;
  }

  bool runTest(string containers, vector<int> reports, int L, string solution) {
    string output = getContainerInfo(containers, reports, L);

    if (output != solution)
    {
      cerr << "Failed for " << containers << endl;
      print_vector(reports);
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
  SurveillanceSystem test;
  {
    int reports_arr[] = {1, 2};
    vector<int> reports(reports_arr, reports_arr + ARR_SIZE(reports_arr));
    test.runTest("-X--XX", reports, 3, "??++++");
  }
  {
    int reports_arr[] = {2};
    vector<int> reports(reports_arr, reports_arr + ARR_SIZE(reports_arr));
    test.runTest("-XXXXX-", reports, 3, "?\?\?-???");
  }
  {
    int reports_arr[] = {3, 0, 2, 0};
    vector<int> reports(reports_arr, reports_arr + ARR_SIZE(reports_arr));
    test.runTest("------X-XX-", reports, 5, "++++++++++?");
  }
  {
    int reports_arr[] = {2, 1, 0, 1};
    vector<int> reports(reports_arr, reports_arr + ARR_SIZE(reports_arr));
    test.runTest("-XXXXX---X--", reports, 3, "?\?\?-??++++??");
  }
  {
    int reports_arr[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    vector<int> reports(reports_arr, reports_arr + ARR_SIZE(reports_arr));
    test.runTest("-XX--X-XX-X-X--X---XX-X---XXXX-----X",
                 reports,
                 7,
                 "???++++?++++++++++++++++++++????\?\?--");
  }
}

