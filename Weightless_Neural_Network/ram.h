#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "look-up_table.h"
#include "definitions.h"

#include <QDebug>

using namespace std;

class RAM{

private:

    n_Tuple_size inputAmount;//number of inputs by RAM
    //input standart to each RAM, this will be allocated according number of input in each RAM*
    LookUp_Table valueThisRam;
    bool trigger;

public:
    RAM(n_Tuple_size inputBitsNumber);

    void insertValue_this_ram(bitStore, int);
    bool search_Pattern(bitStore);

    void setTrigger();
    void resetTrigger();
    bool getTrigger() const;

    unordered_map<bitStore, int> getMap();

    void print(){ //THIS FUNCTION HAS BEEN TO ERASE
        this->valueThisRam.print_hash();
    }
};

class RAM_RankWizard{

private:
    n_Tuple_size n;
    lookUpRankTable table;

public:

    RAM_RankWizard(n_Tuple_size size_tuple);

    void insertLookUpRankTable(uint key);

    bool search_key(uint key) const;

};
#endif // RAM_H
