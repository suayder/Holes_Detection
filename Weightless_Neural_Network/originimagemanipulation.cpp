#include "originimagemanipulation.h"

originImageManipulation::originImageManipulation()
{

}

void originImageManipulation::imageRead(String directory)
{
    this->image = imread(directory, CV_LOAD_IMAGE_GRAYSCALE);
}

void originImageManipulation::thresholding()
{

 threshold(this->image, this->image, 127, 255, THRESH_BINARY);

}

