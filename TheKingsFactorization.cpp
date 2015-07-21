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

#define DEBUG 1
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

class TheKingsFactorization {

public:
  vector<long long> getVector(long long N, vector<long long> primes) {
    vector<long long> output;
    long long N_orig = N;

    for (size_t i = 0; i < primes.size(); ++i) {
      while (N % primes[i] == 0) {
        output.push_back(primes[i]);
        N /= primes[i];
      }
    }

    if (1 != N) {
      primes.push_back(N_orig / primes[0]);
      for (size_t i = 0; i < primes.size() - 1; ++i) {
        for (long long j = primes[i] + 1; j < primes[i + 1]; ++j) {
          while (N % j == 0) {
            output.push_back(j);
            N /= j;
          }
        }
      }
    }
    sort(output.begin(), output.end());
    return output;
  }

  bool runTest(long long number,
               long long hints[], size_t hints_size,
               long long solution[], size_t solution_size) {
    vector<long long> hints_vec(hints, hints + hints_size);
    vector<long long> solution_vec(solution, solution + solution_size);

    vector<long long> output = getVector(number, hints_vec);

    if (output.size() != solution_vec.size() ||
        !equal(output.begin(), output.end(), solution_vec.begin()))
    {
      cerr << "Failed for " << number << ". Expected:" << endl;
      print_vector(solution_vec);
      cerr << "Found instead:" << endl;
      print_vector(output);
    }
  }
};

int main(int argc, char* argv[]) {
  TheKingsFactorization test;
  {
    long long hints[] = {2, 3};
    long long solution[] = {2, 2, 3};
    test.runTest(12, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
  {
    long long hints[] = {7};
    long long solution[] = {7};
    test.runTest(7, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
  {
    long long hints[] = {2, 3, 7};
    long long solution[] = {2, 2, 3, 3, 7, 7};
    test.runTest(1764, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
  {
    long long hints[] = {7};
    long long solution[] = {7, 7};
    test.runTest(49, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
  {
    long long hints[] = {2, 5};
    long long solution[] = {2, 3, 5, 7};
    test.runTest(210, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
  {
    long long hints[] = {2, 2, 2, 5, 5};
    long long solution[] = {2, 2, 2, 2, 2, 5, 5, 5, 5, 5};
    test.runTest(100000, hints, ARR_SIZE(hints), solution, ARR_SIZE(solution));
  }
}

