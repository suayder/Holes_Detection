/**********************************************
 * OBS: First i have to set patters and after i'll
 * call insertInto.
***********************************************/
#ifndef MAPPING_H
#define MAPPING_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

class mapping
{
public:
    mapping();
    ~mapping();

    void insetIntoSet(const string patterns, int numIter);

    void print_hash(); //Only for test

    bool searchPatterns(const int iteratorInRam);

    int getSetSize() const;

    void writeHash(string filePath, int sizeVector, int numiter);

    void readHash(string filePath, int& numiter);

private:

    string patterns;
    unordered_map<int, string> setPatterns;

};

#endif // MAPPING_H
