#ifndef RAM_H
#define RAM_H


#include <iostream>
#include <vector>
#include <unordered_map>
//#include "look-up_table.h"
#include "definitions.h"

// Fazer ram genérica, pode ter a look up table tanto quanto a rank wisard quanto a binária
class Ram
{
public:
    Ram(unsigned int bitsin);

    void train();

    bool search_pattern();

private:
    unsigned int size_in;
};

#endif // RAM_H
