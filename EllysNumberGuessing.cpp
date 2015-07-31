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

class EllysNumberGuessing {

public:
  int getNumber(vector<int> guesses, vector<int> answers) {

    int solution = 0;
    const int lower_bound = 1;
    const int upper_bound = 1000000000;
    set<int> solution_set;

    for (size_t i = 0; i < guesses.size(); ++i) {
      set<int> potential_solutions;
      if (guesses[i] <= upper_bound - answers[i]) {
        potential_solutions.insert(guesses[i] + answers[i]);
      }
      if (guesses[i] >= lower_bound + answers[i]) {
        potential_solutions.insert(guesses[i] - answers[i]);
      }

      if (i > 0) {
        set<int> new_solution_set;

        for (set<int>::iterator it = potential_solutions.begin();
             it != potential_solutions.end();
             ++it) {
          if (solution_set.find(*it) != solution_set.end()) {
            new_solution_set.insert(*it);
          }
        }

        solution_set = new_solution_set;
      }
      else {
        for (set<int>::iterator it = potential_solutions.begin();
             it != potential_solutions.end();
             ++it) {
          solution_set.insert(*it);
        }
      }

      if (solution_set.size() == 0) {
        solution = -2;
        break;
      }
    }

    if (0 == solution) {
      if (1 == solution_set.size())
        solution = *(solution_set.begin());
      else
        solution = -1;
    }

    return solution;
  }

  bool runTest(vector<int> guesses, vector<int> answers, int solution) {
    int output = getNumber(guesses, answers);

    if (output != solution)
    {
      cerr << "Failed for guesses " << endl;
      print_vector(guesses);
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
  EllysNumberGuessing test;
  {
    const int guesses_arr[] = {600, 594};
    const int answers_arr[] = {6, 12};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, 606);
  }
  {
    const int guesses_arr[] = {100, 50, 34, 40};
    const int answers_arr[] = {58, 8, 8, 2};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, 42);
  }
  {
    const int guesses_arr[] = {500000, 600000, 700000};
    const int answers_arr[] = {120013, 220013, 79987};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, -2);
  }
  {
    const int guesses_arr[] = {500000000};
    const int answers_arr[] = {133742666};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, -1);
  }
  {
    const int guesses_arr[] = {76938260, 523164588, 14196746, 296286419,
                              535893832, 41243148, 364561227, 270003278,
                              472017422, 367932361, 395758413, 301278456,
                              186276934, 316343129, 336557549, 52536121,
                              98343562, 356769915, 89249181, 335191879};
    const int answers_arr[] = {466274085, 20047757, 529015599, 246925926,
                              7318513, 501969197, 178651118, 273209067,
                              71194923, 175279984, 147453932, 241933889,
                              356935411, 226869216, 206654796, 490676224,
                              444868783, 186442430, 453963164, 208020466};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, 543212345);
  }
  {
    const int guesses_arr[] = {42};
    const int answers_arr[] = {42};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, 84);
  }
  {
    const int guesses_arr[] = {999900000};
    const int answers_arr[] = {100001};
    vector<int> guesses(guesses_arr, guesses_arr + ARR_SIZE(guesses_arr));
    vector<int> answers(answers_arr, answers_arr + ARR_SIZE(answers_arr));
    test.runTest(guesses, answers, 999799999);
  }
}

