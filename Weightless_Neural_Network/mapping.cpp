#include "mapping.h"

#include<QDebug>
#include <QMessageBox>

mapping::mapping()
{
    this->setSize = 0;

}

void mapping::insetIntoSet(const vector<char> patterns)
{
    //if(this->searchPatterns(patterns) == false){
    this->setPatterns.insert(patterns); //The set function doesn't instert repetead by itself
    //this->setSize++;
        //qDebug() << patterns;
    //}
}

bool mapping::searchPatterns(const vector<char> bitsToFind)
{
    return (this->setPatterns.find(bitsToFind) != this->setPatterns.end());
}

int mapping::getSetSize() const
{
    return this->setPatterns.size();
}

bool mapping::test()
{
    foreach(auto c, this->setPatterns){
        qDebug() << c;
        if(c.size()<7) return true;
    }
    return false;
}
