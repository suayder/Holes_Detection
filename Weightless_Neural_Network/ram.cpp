#include "ram.h"
#include <QDebug>


void RAM::setTrigger()
{
    this->trigger = true;
}

void RAM::resetTrigger()
{
    this->trigger = false;
}

bool RAM::getTrigger() const
{
    return trigger;
}

unordered_map<_int64, int> RAM::getMap()
{
    return this->valueThisRam.getSetPatterns();
}

RAM::RAM(_int64 inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
    this->trigger = false;
}

void RAM::insertValue_this_ram(_int64 inputstandart, int iter)
{
    //if(inputstandart.length()==this->inputAmount)
        this->valueThisRam.insetIntoSet(inputstandart, iter);
}

bool RAM::search_Pattern(_int64 valueToSearch)
{
    this->trigger = this->valueThisRam.searchPatterns(valueToSearch);
    return this->trigger;
}
