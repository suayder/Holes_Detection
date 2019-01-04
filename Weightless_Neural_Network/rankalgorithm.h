#ifndef RANKALGORITHM_H
#define RANKALGORITHM_H

#include "definitions.h"

class RankAlgorithm{

private:
    //unordered_map<uint, char> mappedValue;
    unsigned int shortestElement;
    unordered_map<string, unsigned int> rankTable;
    n_Tuple_size n;

public:
    RankAlgorithm();
    int encode(multimap<u_char, u_char> &tupple);
    int decode(multimap<u_char, u_char>& tupple);
    void setN(const n_Tuple_size &value);
};

#endif // RANKALGORITHM_H
