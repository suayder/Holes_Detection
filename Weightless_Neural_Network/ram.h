#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "mapping.h"
#include <QDebug>
using namespace std;

typedef unsigned long long int _int64;

class RAM{

private:

    _int64 inputAmount;//number of inputs by RAM
    //input standart to each RAM, this will be allocated according number of input in each RAM*
    mapping valueThisRam;
    bool trigger;

public:
    RAM(_int64 inputBitsNumber);

    void insertValue_this_ram(_int64, int);
    bool search_Pattern(_int64);

    void setTrigger();
    void resetTrigger();
    bool getTrigger() const;

    unordered_map<_int64, int> getMap();

    void print(){ //THIS FUNCTION HAS BEEN TO ERASE
        this->valueThisRam.print_hash();
    }
};

#endif // RAM_H
