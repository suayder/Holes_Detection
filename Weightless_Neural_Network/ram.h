#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "mapping.h"
#include <QDebug>
using namespace std;

class RAM{

private:

    unsigned int inputAmount;//number of inputs by RAM
    //input standart to each RAM, this will be allocated according number of input in each RAM*
    mapping valueThisRam;
    bool trigger;

public:
    RAM(unsigned int inputBitsNumber);

    void insertValue_this_ram(string, int);
    bool search_Pattern(string);

    void setTrigger();
    void resetTrigger();
    bool getTrigger() const;

    unordered_multimap<string, int> getMap();

    void print(){ //THIS FUNCTION HAS BEEN TO ERASE
        this->valueThisRam.print_hash();
    }
};

#endif // RAM_H
