/************************************************************************************
 *                                                                                  *
 *  Project created by QtCreator 2017-03-17T17:57:23                                *
 *  Author: Suayder Milhomem Costa                                                  *
 *  Compile information: This aplication use c++11 version to compile               *
 *                                                                                  *
 *  This class contains all the image manipulation functions                        *
 *                                                                                  *
 ************************************************************************************/


#ifndef ORIGINIMAGEMANIPULATION_H
#define ORIGINIMAGEMANIPULATION_H


#define ABSOLUTEVALUE(a)a<0?a*(-1):a


#include <opencv2/opencv.hpp>
#include <string>
#include <mapping.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace cv;

class originImageManipulation
{
public:
    originImageManipulation();

    void imageRead(String directory);
    void thresholding();

    void setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height); //return corresponding point with another scaled image

    void drawRect(Point topLeft, Point ButtonRiht); //Only to see rect selected in original image

    int rectangleSize();

    void getRandomPoint();

    int imageSize();


private:

    Mat image;
    Point topLeft, buttonRight;
    bool **auxRandom;

    void deleteAuxRandom(int i);
    void allocateAuxMatrix(int i, int j);
};

#endif // ORIGINIMAGEMANIPULATION_H
