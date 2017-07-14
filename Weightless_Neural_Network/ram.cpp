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

RAM::RAM(unsigned int inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
    this->trigger = false;
}

RAM::~RAM()
{
}

void RAM::insertValue_this_ram(int iter, string inputstandart)
{
    if(inputstandart.length()==this->inputAmount)
        this->valueThisRam.insetIntoSet(inputstandart, iter);
}
