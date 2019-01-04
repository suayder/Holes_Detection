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

unordered_map<bitStore, int> RAM::getMap()
{
    return this->valueThisRam.getSetPatterns();
}

RAM::RAM(n_Tuple_size inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
    this->trigger = false;
}

void RAM::insertValue_this_ram(bitStore inputstandart, int iter)
{
    this->valueThisRam.insetIntoSet(inputstandart, iter);
}

bool RAM::search_Pattern(bitStore valueToSearch)
{
    this->trigger = this->valueThisRam.searchPatterns(valueToSearch);
    return this->trigger;
}

/*******************************************************************************/

RAM_RankWizard::RAM_RankWizard(n_Tuple_size size_tuple = SIZE_TUPLE)
{
    this->n = size_tuple;
}

void RAM_RankWizard::insertLookUpRankTable(uint key)
{
    this->table.insert(key);
}

bool RAM_RankWizard::search_key(uint key) const
{
    return (this->table.find(key)!=this->table.end());
}
