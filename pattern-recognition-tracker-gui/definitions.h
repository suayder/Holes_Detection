#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <utility>

#define THRESHOLD_WISARD 0.7

using namespace std;

typedef string _bitStore; //Used in look up table to store bits in a ram
typedef int _coordinates;
typedef pair<uint,uint> _pi;

//Used in RAM class
const static size_t SIZE_TUPLE = 5;
typedef size_t _tupleSize;
typedef unordered_set<uint> _lookUpRankTable;

//Just obs for me (opencv): COLS = 4000 = X = WIDTH
//                          ROWS = 3000 = y = HEIGHT
#endif // DEFINITIONS_H
