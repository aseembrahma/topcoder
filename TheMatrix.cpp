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

class TheMatrix {


  #define MAX_DIMENSION 100
  int table[MAX_DIMENSION][MAX_DIMENSION];
  int max_height[MAX_DIMENSION][MAX_DIMENSION];
  int max_width[MAX_DIMENSION][MAX_DIMENSION];

public:
  int MaxArea(vector <string> board) {

    int solution = 0;

    for (size_t i = 0; i < board.size(); ++i) {
      for (size_t j = 0; j < board[0].size(); ++j) {
        table[i][j] = board[i][j] - '0';

        if (j > 0 && table[i][j] == 1 - table[i][j - 1]) {
          max_width[i][j] = max_width[i][j - 1] + 1;
        }
        else {
          max_width[i][j] = 1;
        }

        if (i > 0 && table[i][j] == 1 - table[i - 1][j]) {
          max_height[i][j] = max_height[i - 1][j] + 1;
        }
        else {
          max_height[i][j] = 1;
        }


        for (int k  = 1, min_width = max_width[i][j];
             k <= max_height[i][j];
             ++k) {
          min_width = min(min_width, max_width[i - (k - 1)][j]);
          solution = max(solution, k * min_width);
        }
        //solution = max(solution, max_width[i][j] * max_height[i][j]);
      }
    }

    return solution;
  }

  bool runTest(vector <string> board, int solution) {
    int output = MaxArea(board);

    if (output != solution)
    {
      cerr << "Failed for board " << endl;
      print_vector(board);
      cerr << "Expected: " << solution << endl;
      cerr << "Found instead:" << output << endl;
    }
  }
};

int main(int argc, char* argv[]) {
  TheMatrix test;
  {
    const char * board_arr[] = {"1", "0"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 2);
  }
  {
    const char * board_arr[] = {"0000"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 1);
  }
  {
    const char * board_arr[] = {"01"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 2);
  }
  {
    const char * board_arr[] = {"001",
                                "000",
                                "100"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 2);
  }
  {
    const char * board_arr[] = {"0"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 1);
  }
  {
    const char * board_arr[] = {"101",
                                "010"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 6);
  }
  {
    const char * board_arr[] = {"101", 
                                "011", 
                                "101", 
                                "010"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 8);
  }
  {
    const char * board_arr[] =
    {"11001110011000110001111001001110110011010110001011",
     "10100100010111111011111001011110101111010011100001",
     "11101111001110100110010101101100011100101000010001",
     "01000010001010101100010011111000100100110111111000",
     "10110100000101100000111000100001011101111101010010",
     "00111010000011100001110110010011010110010011100100",
     "01100001111101001101001101100001111000111001101010",
     "11010000000011011010100010000000111011001001100101",
     "10100000000100010100100011010100110110110001000001",
     "01101010101100001100000110100110100000010100100010",
     "11010000001110111111011010011110001101100011100010",
     "11101111000000011010011100100001100011111111110111",
     "11000001101100100011000110111010011001010100000001",
     "00100001111001010000101101100010000001100100001000",
     "01001110110111101011010000111111101011000110010111",
     "01001010000111111001100000100010101100100101010100",
     "11111101001101110011011011011000111001101100011011",
     "10000100110111000001110110010000000000111100101101",
     "01010011101101101110000011000110011111001111011100",
     "01101010011111010000011001111101011010011100001101",
     "11011000011000110010101111100000101011011111101100",
     "11100001001000110010100011001010101101001010001100",
     "11011011001100111101001100111100000101011101101011",
     "11110111100100101011100101111101000111001111110111",
     "00011001100110111100111100001100101001111100001111",
     "10001111100101110111001111100000000011110000100111",
     "10101010110110100110010001001010000111100110100011",
     "01100110100000001110101001101011001010001101110101",
     "10110101110100110110101001100111110000101111100110",
     "01011000001001101110100001101001110011001001110001",
     "00100101010001100110110101001010010100001011000011",
     "00011101100100001010100000000011000010100110011100",
     "11001001011000000101111111000000110010001101101110",
     "10101010110110010000010011001100110101110100111011",
     "01101001010111010001101000100011101001110101000110",
     "00110101101110110001110101110010100100110000101101",
     "11010101000111010011110011000001101111010011110011",
     "10010000010001110011011101001110110010001100011100",
     "00111101110001001100101001110100110010100110110000",
     "00010011011000101000100001101110111100100000010100",
     "01101110001101000001001000001011101010011101011110",
     "00000100110011001011101011110011011101100001110111",
     "00110011110000011001011100001110101010100110010110",
     "00111001010011011111010100000100100000101101110001",
     "10101101101110111110000011111011001011100011110001",
     "00101110010101111000001010110100001110111011100011",
     "01111110010100111010110001111000111101110100111011"};
    vector<string> board(board_arr, board_arr + ARR_SIZE(board_arr));
    test.runTest(board, 12);
  }

}

