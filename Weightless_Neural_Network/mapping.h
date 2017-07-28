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

class mapping
{
public:
    mapping();

    void insetIntoSet(const string patterns, int numIter);

    void print_hash(); //Only for test

    bool searchPatterns(const string valueToSearch);

    int getSetSize() const;

    unordered_multimap<string, int> getSetPatterns() const;

private:

    string patterns;
    unordered_multimap<string,int> setPatterns;

};

#endif // MAPPING_H
