#ifndef DEFINITION_H
#define DEFINITION_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <ctime>
#include <unordered_map>
#include <map>
#define THRESHOLD_TRIGGER_WIZARD 0.8

using namespace std;

typedef string bitStore; //Used in look up table, to store bits in a ram
typedef int coordinates; //Used in mainwindow
typedef pair<uint, uint> pi;
//mapped

//used in RAM class
const static size_t SIZE_TUPLE = 5;
typedef size_t n_Tuple_size;
typedef unordered_set<uint> lookUpRankTable;

//Just obs for me (opencv): COLS = 4000 = X = WIDTH
//                          ROWS = 3000 = Y = HEIGHT

#endif // DEFINITION_H
