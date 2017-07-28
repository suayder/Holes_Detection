#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>
#include <string>
#include <thread>
#include <string>
#include <fstream>
#include <ctime>
#include "ram.h"
#include "mapping.h"
#include "originimagemanipulation.h"

using namespace std;

class Descriptor
{
    
public:

    Descriptor( unsigned int ramNumberOfInputs, originImageManipulation **image);
    Descriptor(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image);
    Descriptor();

    void setValuesOnEachRam(vector<char> &vector);

    void training();

    vector<pair<Point, int>> recognize(Point);

    void fillRamVector();
    
    void setSizeOfRect(const int, const int, const int, const int);

    int FunctionOfEachRect(Point);

    void setRamNumberOfInputs(unsigned int value);

    cv::Size getSizeOfRect() const;

    void saveNetwork();

    void load_a_map();

    void p(){ //ERASE THIS FUNCTION
        vector<RAM>::iterator r = this->ramVector.begin();
        r->print();
    }

    void set_retine();

    unsigned int getRamNumber() const;

private:

    vector<RAM> ramVector; //Vector with all rams

    unsigned int ramNumberOfInputs; //Number of bits sequence in each ram

    unsigned int ramNumber; //number of Rams

    originImageManipulation **image;

    bool status; // if is operation or training mode

    cv::Size sizeOfRect; //Standard size

    int numOfIter; //This is couting number of rects trained

    vector<unsigned int> retinalOrdering; //ordering of the retine

    char *test;

};

#endif // DESCRIPTOR_H
