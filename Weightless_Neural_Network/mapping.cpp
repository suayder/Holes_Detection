#include "mapping.h"
#include<QDebug>
#include <QMessageBox>

mapping::mapping()
{
}


void mapping::insetIntoSet(const string patterns, int numIter)
{
    this->setPatterns.insert({patterns,numIter});
}

void mapping::print_hash()
{
    qDebug()<<"HERE: "<<this->setPatterns.size();
    for(auto& r:this->setPatterns)
        qDebug()<<"Partterns: "<<QString::fromStdString(r.first);
    qDebug()<<"FINISH";
}

bool mapping::searchPatterns(const string valueToSearch)
{
    return (this->setPatterns.find(valueToSearch) != this->setPatterns.end());
}

int mapping::getSetSize() const
{
    return this->setPatterns.size();
}

unordered_multimap<string, int> mapping::getSetPatterns() const
{
    return setPatterns;
}
