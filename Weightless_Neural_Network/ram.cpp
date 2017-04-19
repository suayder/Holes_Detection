#include "ram.h"

void RAM::setInputstandart(vector<char> &value)
{
    this->inputstandart = value;
};

vector<char> RAM::getInputstandart()
{
    return inputstandart;
};

RAM::RAM(unsigned inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
};
