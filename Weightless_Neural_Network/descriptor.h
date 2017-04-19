#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>
#include <functional> //Library for hash

#include "ram.h"
#include "mapping.h"

using namespace std;

class Descriptor
{
    
public:
    Descriptor(unsigned int ramNumber, unsigned int ramNumberOfInputs);
    void setValuesOnEachRam(vector<char> &vector);
    void training();
    
private:
    
    vector<RAM> ramVector;
    unsigned int ramNumberOfInputs;
    unsigned int ramNumber;
    mapping mappingclass;
    bool status; // if is operation or training mode

};

#endif // DESCRIPTOR_H
