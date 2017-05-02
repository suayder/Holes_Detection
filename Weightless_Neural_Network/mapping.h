/**********************************************
 * OBS: First i have to set patters and after i'll
 * call insertInto.
***********************************************/
#ifndef MAPPING_H
#define MAPPING_H

#include <vector>
#include <iostream>
#include <set>

using namespace std;

class mapping
{
public:
    mapping();

    void insetIntoSet(vector<char> patterns);

    void print_hash(); //Only for test

    bool searchPatterns(vector<char> bitsToFind);


private:

    vector<char> patterns;
    set<vector<char>> setPatterns;

};

#endif // MAPPING_H
