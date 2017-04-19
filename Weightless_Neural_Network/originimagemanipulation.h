#ifndef ORIGINIMAGEMANIPULATION_H
#define ORIGINIMAGEMANIPULATION_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

class originImageManipulation
{
public:
    originImageManipulation();
    void imageRead(String directory);
    void thresholding();


private:

    Mat image;
};

#endif // ORIGINIMAGEMANIPULATION_H
