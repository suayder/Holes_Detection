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

unordered_multimap<string, int> RAM::getMap()
{
    return this->valueThisRam.getSetPatterns();
}

RAM::RAM(unsigned int inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
    this->trigger = false;
}

void RAM::insertValue_this_ram(string inputstandart, int iter)
{
    if(inputstandart.length()==this->inputAmount)
        this->valueThisRam.insetIntoSet(inputstandart, iter);
}

bool RAM::search_Pattern(string valueToSearch)
{
    this->trigger = this->valueThisRam.searchPatterns(valueToSearch);
    return this->trigger;
}
