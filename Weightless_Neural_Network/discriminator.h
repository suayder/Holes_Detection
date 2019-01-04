#ifndef DISCRIMINATOR_H
#define DISCRIMINATOR_H

#include <vector>
#include <string>
#include <thread>
#include <string>
#include <fstream>

#include "ram.h"
#include "look-up_table.h"
#include "originimagemanipulation.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

class Discriminator
{
    
public:

    Discriminator( unsigned int ramNumberOfInputs, originImageManipulation **image);
    Discriminator(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image);
    Discriminator();

    void setValuesOnEachRam(vector<char> &vector);

    void training(); //Training used in user interface

    void training(Mat& im); //Training with selective searh algorithm

    void recognize(Mat &image, const vector<Rect>& rects, const std::string& path_to_save, double thereshold); //Recognize with selective search algorithm

    void scrollThroughY(Point _p, const vector<int> &vrandom, int dx, int dy); //NO MORE USED

    void scrollThroughX(Point _p, const vector<int> &vrandom, int _dx, int _dy); //NO MORE USED

    void fillRamVector(); //Alloc RAM
    
    void setSizeOfRect(const int, const int, const int, const int);

    void setSizeOfRect(int width, int heidth);

    uint FunctionOfEachRect(Point);

    void FunctionOfEachRect(Point _P, int *i);

    void setRamNumberOfInputs(unsigned int value);

    cv::Size getSizeOfRect() const;

    void saveNetwork(); //get out of here

    void load_a_map(); // get out of here

    void set_retine();

    void set_retine(vector<unsigned int>&);

    unsigned int getRamNumber() const;

    unsigned int getRamNumberOfInputs() const;

    vector<unsigned int> getRetinalOrdering() const;

    void setImage(const Mat &value);

    void p(){ //ERASE THIS FUNCTION
        vector<RAM>::iterator r = this->ramVector.begin();
        r->print();
    }

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

    Mat imageData;
    Mat imageToDrawResult;

};

#endif // DESCRIPTOR_H
