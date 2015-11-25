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

class AntsMeet {
  /*
   */

public:
  int countAnts(vector<int> x, vector<int> y, string direction) {
    int n = x.size();
    vector<vector<int> > points(n, vector<int>(2, 0));
    vector<int> dir(n, 0);
    typedef pair<int, pii> piii;
    priority_queue<piii, vector<piii>, greater<piii> > pq;
    unordered_map<char, int> m;

    m['N'] = 1;
    m['S'] = -1;
    m['E'] = 2;
    m['W'] = -2;

    for (int i = 0; i < n; ++i) {
      points[i][0] = x[i];
      points[i][1] = y[i];
      dir[i] = m[direction[i]];
    }

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        // points travelling in the same direction cannot meet
        if (dir[i] == dir[j]) {
          continue;
        }

        if (abs(dir[i]) == abs(dir[j])) {
          int abs_dir = abs(dir[i]);
          if (points[i][abs_dir - 1] != points[j][abs_dir - 1]) {
            continue;
          }

          if ((points[i][abs_dir % 2] * dir[i]) +
              (points[j][abs_dir % 2] * dir[j]) < 0) {
            pq.push(
              make_pair(
                abs(points[i][abs_dir % 2] - points[j][abs_dir % 2]),
                make_pair(i, j)));
          }
        }
        else {
          // travelling horizontally, vertically
          int h = i, v = j;

          if (1 == abs(dir[i]))
            swap(h, v);

          int h_dist = points[v][0] - points[h][0];
          int v_dist = points[h][1] - points[v][1];

          // the horizontal
          if (abs(h_dist) == abs(v_dist) &&
              (h_dist * dir[h]) > 0 &&
              (v_dist * dir[v]) > 0) {
            pq.push(make_pair(abs(h_dist) * 2, make_pair(h, v)));
          }
        }
      }
    }

    unordered_set<int> s;
    for (int i = 0; i < n; ++i)
      s.insert(i);

    while (!pq.empty()) {
      pair<int, pii> t = pq.top();
      pq.pop();

      if (s.find(t.second.first) != s.end() &&
          s.find(t.second.second) != s.end()) {

        unordered_set<int> s_temp;

        /*
        cout << "removing" << endl;
        print_vector(points[t.second.first]);
        print_vector(points[t.second.second]);
        */

        s_temp.insert(t.second.first);
        s_temp.insert(t.second.second);
        while (!pq.empty()) {
          pair<int, pii> p = pq.top();
          if (p.first != t.first) {
            break;
          }
          else {
            pq.pop();
            if (s.find(p.second.first) != s.end() &&
                s.find(p.second.second) != s.end()) {
              /*
              cout << "removing2" << endl;
              print_vector(points[p.second.first]);
              print_vector(points[p.second.second]);
              */

              s_temp.insert(p.second.first);
              s_temp.insert(p.second.second);
            }
          }
        }

        for (unordered_set<int>::iterator it = s_temp.begin();
             it != s_temp.end();
             ++it)
          s.erase(*it);
      }
    }
    return s.size();
  }

  bool runTest(vector<int> x, vector<int> y, string direction, int solution) {
    int output = countAnts(x, y, direction);

    if (output != solution)
    {
      cerr << "Failed for " << endl;
      print_vector(x);
      print_vector(y);
      cout << direction << endl;
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
  AntsMeet test;
  {
    test.runTest({0,10,20,30}, {0,10,20,30}, "NWNE", 2);
    test.runTest({-10,0,0,10}, {0,-10,10,0}, "NEWS", 0);
    test.runTest({-1,-1,-1,0,0,0,1,1,1}, {-1,0,1,-1,0,1,-1,0,1}, "ESEWNNEWW", 4);
    test.runTest({4,7,6,2,6,5,7,7,8,4,7,8,8,8,5,4,8,9,1,5,9,3,4,0,0,1,0,7,2,6,9,6,3,0,5,5,1,2,0,4,9,7,7,1,8,1,9,2,7,3}, {2,3,0,6,8,4,9,0,5,0,2,4,3,8,1,5,0,7,3,7,0,9,8,1,9,4,7,8,1,1,6,6,6,2,8,5,1,9,0,1,1,1,7,0,2,5,4,7,5,3}, "SSNWSWSENSWSESWEWSWSENWNNNESWSWSWWSSWEEWWNWWWNWENN", 25);
    test.runTest({478,-664,759,434,-405,513,565,-396,311,-174,56,993,251,-341,993,-112,242,129,383,513,-78,-341,-148,129,423
    ,493,434,-405,478,-148,929,251,56,242,929,-78,423,-664,802,251,759,383,-112,-591,-591,-248,660,660,735,493}, {-186,98,948,795,289,-678,948,-170,-195,290,-354,-424,289,-157,-166,150,706,-678,684,-294,-234,36,36,-294,-216
    ,-234,427,945,265,-157,265,715,275,715,-186,337,798,-170,427,706,754,961,286,-216,798,286,961,684,-424,337}, "WNSNNSSWWWEENWESNSWSWSEWWEWEWWWNWESNSSNNSNNWWWNESE", 44);
  }
}

