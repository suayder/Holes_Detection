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

    bool output;

public:
    RAM(unsigned int inputBitsNumber); //OBS:Tenho que alocar mais uma ram se por acaso der numero quebrado
    void setInputstandart(vector<char> &value);
    vector<char> getInputstandart();

};

#endif // RAM_H
