/**********************************************
 * OBS: First i have to set patters and after i'll
 * call insertInto.
***********************************************/
#ifndef MAPPING_H
#define MAPPING_H

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef unsigned long long int _int64;

class mapping
{
public:
    mapping();

    void insetIntoSet(const _int64 patterns, int numIter);

    void print_hash(); //Only for test

    bool searchPatterns(const _int64 valueToSearch);

    int getSetSize() const;

    unordered_map<_int64, int> getSetPatterns() const;

private:

    unsigned int patterns;
    unordered_map<_int64,int> setPatterns;

};

#endif // MAPPING_H
