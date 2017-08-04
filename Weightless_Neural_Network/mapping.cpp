#include "mapping.h"
#include<QDebug>
#include <QMessageBox>

mapping::mapping()
{
}


void mapping::insetIntoSet(const _int64 patterns, int numIter)
{
    this->setPatterns.insert({patterns,numIter});
}

void mapping::print_hash()
{
    qDebug()<<"HERE: "<<this->setPatterns.size();
    for(auto& r:this->setPatterns)
        qDebug()<<"Partterns: "<<QString::number(r.first);
    qDebug()<<"FINISH";
}

bool mapping::searchPatterns(const _int64 valueToSearch)
{
    return (this->setPatterns.find(valueToSearch) != this->setPatterns.end());
}

int mapping::getSetSize() const
{
    return this->setPatterns.size();
}

unordered_map<_int64, int> mapping::getSetPatterns() const
{
    return setPatterns;
}
