#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class RAM{

private:

    unsigned int inputAmount;//number of inputs by RAM
    vector<char> inputstandart; //input standart to each RAM, this will be allocated according number of input in each RAM

public:
    RAM(unsigned int inputBitsNumber);
    ~RAM();
    void setInputstandart(char value);

    void deleteVector();

    vector<char> getInputstandart() const;
};

#endif // RAM_H
