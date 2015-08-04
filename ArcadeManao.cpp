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

class ArcadeManao {

public:
  int shortestLadder(vector<string> level, int coinRow, int coinColumn) {
    int solution = 0;

    if (coinRow == level.size())
      return solution;

    coinRow--;
    coinColumn--;

    typedef pair<size_t, size_t> point_t;
    typedef pair<point_t, point_t> edge_t;

    set<point_t> vertices;
    map<edge_t, int> edgeweights;
    map<point_t, vector<point_t> > edges;
    map<int, vector<edge_t> > weight_to_edges;
    priority_queue<int> pQ;

    for (size_t i = 0; i < level.size(); ++i) {
      for (size_t j = 0; j < level[i].size(); ++j) {
        if (level[i][j] == 'X') {
          point_t u = make_pair(i, j);
          vertices.insert(u); 

          if (j > 0 && level[i][j - 1] == 'X') {
            point_t v = make_pair(i, j - 1);
            edge_t edge1 = make_pair(u, v), edge2 = make_pair(v, u);
            int weight = 0;

            edgeweights[edge1] = edgeweights[edge2] = weight;
            edges[u].push_back(v); edges[v].push_back(u);

            weight_to_edges[weight].push_back(edge1);
            weight_to_edges[weight].push_back(edge2);
          }
        }
      }
    }

    for (size_t j = 0; j < level[0].size(); ++j) {
      for (size_t i = 0; i < level.size(); ++i) {
        for (size_t k = i + 1; k < level.size(); ++k) {
          if (level[i][j] == 'X' && level[k][j] == 'X') {
            point_t u = make_pair(i, j), v = make_pair(k, j);
            edge_t edge1 = make_pair(u, v), edge2 = make_pair(v, u);
            int weight = k - i;

            edgeweights[edge1] = edgeweights[edge2] = weight;
            edges[u].push_back(v); edges[v].push_back(u);

            weight_to_edges[weight].push_back(edge1);
            weight_to_edges[weight].push_back(edge2);
          }
        }
      }
    }

    size_t src_row = level.size(), src_col = 0;
    point_t coin = make_pair(coinRow, coinColumn);
    point_t src = make_pair(src_row, src_col);
    vertices.insert(src);

    for (size_t j = 0; j < level[0].size(); ++j) {
      point_t u = make_pair(level.size() - 1, j);
      edge_t edge1 = make_pair(u, src), edge2 = make_pair(src, u);
      int weight = 0;

      edgeweights[edge1] = edgeweights[edge2] = weight;
      edges[u].push_back(src); edges[src].push_back(u);

      weight_to_edges[weight].push_back(edge1);
      weight_to_edges[weight].push_back(edge2);
    }

    for (map<int, vector<edge_t> >::iterator it = weight_to_edges.begin();
         it != weight_to_edges.end();
         ++it) {
      pQ.push(it->first);
    }

    bool connected;
    int weight;
    do {
      weight = pQ.top();
      pQ.pop();
#if DEBUG
      cout << "weight: " << weight << endl;
#endif

      vector<edge_t> edges_to_remove = weight_to_edges[weight];
      for (size_t i = 0; i < edges_to_remove.size(); ++i) {
        edge_t edge = edges_to_remove[i];
#if DEBUG
        cout << "Removing (" << edge.first.first  << "," << edge.first.second  << ") "
                      << "(" << edge.second.first << "," << edge.second.second << ") " <<  endl;
#endif

        edges[edge.first].erase(find(edges[edge.first].begin(),
                                     edges[edge.first].end(),
                                     edge.second));
      }

      queue<point_t> Q;
      set<point_t> visited;

      visited.insert(src);
      Q.push(src);

      connected = false;

      while (!Q.empty()) {
        point_t u = Q.front();
        Q.pop();

        if (u == coin) {
          connected = true;
          break;
        }

        vector<point_t> neighbours = edges[u];
        for (size_t i = 0; i < neighbours.size(); ++i) {
          point_t v = neighbours[i];
          if (visited.find(v) == visited.end()) {
            visited.insert(v);
            Q.push(v);
          }
        }
      }
    } while (connected);

    return weight;
  }

  bool runTest(vector<string> level, int coinRow, int coinColumn, int solution) {
    int output = shortestLadder(level, coinRow, coinColumn);

    if (output != solution)
    {
      cerr << "Failed for " << coinRow << ", " << coinColumn << endl;
      print_vector(level);
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
  ArcadeManao test;
  {
    const char * level_arr[] =
    {"XXXX....",
     "...X.XXX",
     "XXX..X..",
     "......X.",
     "XXXXXXXX"};
    vector<string> level(level_arr, level_arr + ARR_SIZE(level_arr));
    test.runTest(level, 2, 4, 2);
  }
  {
    const char * level_arr[] =
    {"XXXX",
     "...X",
     "XXXX"};
    vector<string> level(level_arr, level_arr + ARR_SIZE(level_arr));
    test.runTest(level, 1, 1, 1);
  }
  {
    const char * level_arr[] =
    {"..X..",
     ".X.X.",
     "X...X",
     ".X.X.",
     "..X..",
     "XXXXX"};
    vector<string> level(level_arr, level_arr + ARR_SIZE(level_arr));
    test.runTest(level, 1, 3, 4);
  }
  {
    const char * level_arr[] =
    {"X"};
    vector<string> level(level_arr, level_arr + ARR_SIZE(level_arr));
    test.runTest(level, 1, 1, 0);
  }
  {
    const char * level_arr[] =
    {"XXXXXXXXXX",
     "...X......",
     "XXX.......",
     "X.....XXXX",
     "..XXXXX..X",
     ".........X",
     ".........X",
     "XXXXXXXXXX"};
    vector<string> level(level_arr, level_arr + ARR_SIZE(level_arr));
    test.runTest(level, 1, 1, 2);
  }
}

