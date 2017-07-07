#include "ram.h"
#include <QDebug>

RAM::RAM(unsigned int inputBitsNumber)
{
    this->inputAmount = inputBitsNumber;
}

RAM::~RAM()
{
    this->inputstandart.clear();
}

vector<char> RAM::getInputstandart() const
{
    return inputstandart;
}

void RAM::setInputstandart(char value)
{
    try{
        this->inputstandart.push_back(value);
        //qDebug()<< value;
    }
    catch(...){
        qDebug() << "ERROR";
    }
}

void RAM::deleteVector()
{
    this->inputstandart.clear();
}
