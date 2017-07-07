#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>
#include <functional> //Library for hash

#include "ram.h"
#include "mapping.h"
#include "originimagemanipulation.h"

using namespace std;

class Descriptor
{
    
public:

    Descriptor( unsigned int ramNumberOfInputs, originImageManipulation **image);
    Descriptor(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image);

    void setValuesOnEachRam(vector<char> &vector);

    void training();

    int recognize();

    void fillRamVector(vector<RAM>&, unsigned int, unsigned int);

    int getHashSize();

    void deleteAllVector();
    
    void setSizeOfRect(const int, const int, const int, const int);

    int FunctionOfEachRect();

    void setRamNumberOfInputs(unsigned int value);

private:

    vector<RAM> ramVector; //Vector with all rams

    unsigned int ramNumberOfInputs; //Number of bits sequence in each ram

    unsigned int ramNumber; //number of Rams

    mapping mappingclass;

    originImageManipulation **image;

    bool status; // if is operation or training mode

    cv::Size sizeOfRect;

};

#endif // DESCRIPTOR_H
