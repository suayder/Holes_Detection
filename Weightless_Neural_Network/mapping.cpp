#include "mapping.h"

#include<QDebug>
#include <QMessageBox>

mapping::mapping()
{
}

mapping::~mapping()
{
    this->patterns.clear();
}

void mapping::insetIntoSet(const string patterns, int numIter)
{
    this->setPatterns.insert({numIter, patterns});
}

void mapping::print_hash()
{
    for(auto r:this->setPatterns)
        qDebug()<<"Partterns: "<<r.first;
}

bool mapping::searchPatterns(const int iteratorInRam)
{
    return (this->setPatterns.find(iteratorInRam) != this->setPatterns.end());
}

int mapping::getSetSize() const
{
    return this->setPatterns.size();
}

void mapping::writeHash(string filePath, int sizeVector, int numiter)
{
    ofstream output;
    output.open(filePath);
    output << sizeVector<<endl;
    output<<numiter;
    /*for(auto& vectorInHash:this->setPatterns){
        output<<"\n";
        for(auto& values: vectorInHash){
            output << values;
        }
    }*/
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
    /*if(input.is_open()){
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
    }*/
    input.close();
}
