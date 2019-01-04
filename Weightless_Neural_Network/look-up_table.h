/**********************************************
 * OBS: First i have to set patters and after i'll
 * call insertInto.
***********************************************/
#ifndef MAPPING_H
#define MAPPING_H

#include <unordered_map>
#include "definitions.h"

class LookUp_Table
{

private:

    unordered_map<bitStore,int> setPatterns;

public:
    LookUp_Table();

    void insetIntoSet(bitStore patterns, int numIter);

    void print_hash(); //Only for test

    bool searchPatterns(const bitStore valueToSearch);

    int getSetSize() const;

    unordered_map<bitStore, int> getSetPatterns() const;

};

#endif // MAPPING_H
