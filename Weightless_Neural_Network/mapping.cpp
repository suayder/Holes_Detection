#include "mapping.h"

mapping::mapping()
{

}

void mapping::insetIntoSet(vector<char> patterns)
{
    this->setPatterns.insert(patterns);
}

bool mapping::searchPatterns(vector<char> bitsToFind)
{
    return !(this->setPatterns.find(bitsToFind) == this->setPatterns.end());
}
/*
vector<char> mapping::getPatterns() const
{
    return patterns;
}

void mapping::setpatterns(vector<char> bitsPatterns)
{
    this->patterns = bitsPatterns;
}*/
