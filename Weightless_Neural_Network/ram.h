#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include <iterator>
#include "mapping.h"

using namespace std;

class RAM{

private:

    unsigned int inputAmount;//number of inputs by RAM
    //input standart to each RAM, this will be allocated according number of input in each RAM*
    mapping valueThisRam;
    bool trigger;

public:
    RAM(unsigned int inputBitsNumber);

    ~RAM();

    void insertValue_this_ram(int,string);

    void setTrigger();
    void resetTrigger();
    bool getTrigger() const;
};

#endif // RAM_H
