#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>
#include <string>
#include <thread>

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

    vector<pair<Point, int>> recognize(Point);

    void fillRamVector();
    
    void setSizeOfRect(const int, const int, const int, const int);

    int FunctionOfEachRect(Point);

    void setRamNumberOfInputs(unsigned int value);

    cv::Size getSizeOfRect() const;

    void saveNetwork();

    void read_a_map();

    void p(){ //ERASE THIS FUNCTION
        RAM r = this->ramVector.at(0);
        r.print();
    }

private:

    vector<RAM> ramVector; //Vector with all rams

    unsigned int ramNumberOfInputs; //Number of bits sequence in each ram

    unsigned int ramNumber; //number of Rams

    originImageManipulation **image;

    bool status; // if is operation or training mode

    cv::Size sizeOfRect; //Standard size

    int numOfIter; //This is couting number of rects trained

};

#endif // DESCRIPTOR_H
