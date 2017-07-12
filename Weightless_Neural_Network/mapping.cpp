#include "mapping.h"

#include<QDebug>
#include <QMessageBox>

mapping::mapping()
{
    this->setSize = 0;

}

void mapping::insetIntoSet(const vector<char> patterns)
{
    //if(patterns.size()==this->setSize){
    this->setPatterns.insert(patterns); //The set function doesn't instert repetead by itself
    //qDebug() << patterns;
    //}
}

void mapping::print_hash()
{
    for(auto r:this->setPatterns)
        qDebug()<<r;
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
        if(c.size()<7) return true;
    }
    return false;
}

void mapping::writeHash(string filePath, int sizeVector, int numiter)
{
    ofstream output;
    output.open(filePath);
    output << sizeVector<<endl;
    output<<numiter;
    for(auto& vectorInHash:this->setPatterns){
        output<<"\n";
        for(auto& values: vectorInHash){
            output << values;
        }
    }
    output.close();
}

void mapping::readHash(string filePath, int& numiter)
{
    ifstream input;
    char auxiliary;
    string sizeOfVector;
    int i;
    input.open(filePath);
    getline(input, sizeOfVector);
    i = stoi(sizeOfVector);
    getline(input, sizeOfVector);
    numiter = stoi(sizeOfVector);
    if(input.is_open()){
        this->setPatterns.clear();
        while(input >> auxiliary){
            this->patterns.push_back(auxiliary);
            if(this->patterns.size()==i){
                this->setPatterns.insert(this->patterns);
                this->patterns.clear();
            }
        }
    }
    else{
        cout<<"ERROR: Cannot open file"<<endl;
    }
    input.close();
}
