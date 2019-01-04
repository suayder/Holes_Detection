#include "look-up_table.h"
#include<QDebug>
#include <QMessageBox>

LookUp_Table::LookUp_Table()
{
}


void LookUp_Table::insetIntoSet(bitStore patterns, int numIter)
{
    this->setPatterns.insert({patterns,numIter});
}

void LookUp_Table::print_hash()
{
    qDebug()<<"Mapping class: "<<this->setPatterns.size();
    for(auto& r:this->setPatterns)
        qDebug()<<"Partterns: "<<QString::fromStdString(r.first);
    qDebug()<<"FINISH";
}

bool LookUp_Table::searchPatterns(const bitStore valueToSearch)
{
    return (this->setPatterns.find(valueToSearch) != this->setPatterns.end());
}

int LookUp_Table::getSetSize() const
{
    return this->setPatterns.size();
}

unordered_map<bitStore, int> LookUp_Table::getSetPatterns() const
{
    return setPatterns;
}
