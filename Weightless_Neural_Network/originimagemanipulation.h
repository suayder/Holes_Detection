/************************************************************************************
 *                                                                                  *
 *  Project created by QtCreator 2017-03-17T17:57:23                                *
 *  Author: Suayder Milhomem Costa                                                  *
 *  Compile information: This aplication use c++11 version to compile               *
 *                       and need opencv to work
 *                                                                                  *
 *  This class contains all the image manipulation functions                        *
 *                                                                                  *
 ************************************************************************************/

//Just obs for me: COLS = 4000 = X = WIDTH
//                 ROWS = 3000 = Y = HEIGHT

#ifndef ORIGINIMAGEMANIPULATION_H
#define ORIGINIMAGEMANIPULATION_H


#define ABSOLUTEVALUE(a)a<0?a*(-1):a
#define SWAP(a,b) {a = a+b; b = a-b; a = a-b;}


#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "mapping.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

using namespace std;
using namespace cv;

class originImageManipulation
{
public:
    originImageManipulation();
    ~originImageManipulation();

    void imageRead(String directory);
    void thresholding();

    void setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height); //return corresponding point with another scaled image

    void drawRect(Point topLeft, Point ButtonRiht); //Only to see rect selected in original image

    int rectangleSize();

    char getRandomPoint();
    void shufflePoints(int numberOfRans, int sizeOfvector);

    Size getImageSize();

    Point getTopLeft() const;
    void setTopLeft(const Point &value);

    Point getButtonRight() const;
    void setButtonRight(const Point &value);

    void deleteAuxMatrix();
    void allocateAuxMatrix(int, int);
    void allocateAuxMatrix(Point, Size);

    void insertRect();
    
    vector<pair<Point, Point>> getVr() const;

    void setPointsWithinVector(int pos);

    char *getAuxRandom() const;

private:

    Mat image;
    Point topLeft, buttonRight;
    vector<pair<Point,Point>> vr; //Vector of Rects
    char *auxRandom; //Is the Matrix to check the values

};

#endif // ORIGINIMAGEMANIPULATION_H
