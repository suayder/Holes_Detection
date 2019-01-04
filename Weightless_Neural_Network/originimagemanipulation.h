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
    #include <cstdlib>
    #include <QDebug>
    #include "look-up_table.h"
    //TODO: Isto não deveria estar aqui. Temos que criar uma hierarquia de classes de buscas globais e uma delas faz isso, ok?
    #include <opencv2/ximgproc/segmentation.hpp>

    using namespace std;
    using namespace cv;

    class originImageManipulation
    {
    public:
        originImageManipulation();
        ~originImageManipulation();

        void imageRead(String directory);

        void imageWrite(String directory, Mat image);

        void thresholding();

        void show();

        void setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height); //return corresponding point with another scaled image

        void setCorrespondingPoins(int x1, int y1, int width, int height, Size size, int); //return corresponding point with another scaled image

        void drawRect(Point topLeft, Point ButtonRiht); //Only to see the selected rect into the original image

        static void drawRect(const Point &topLeft, const Point &ButtonRiht, Mat &image);

        uint rectangleSize();
        uint getRectWidth();
        uint getRecHeight();

        void shufflePoints(int numberOfRans, int sizeOfvector); //Not used anymore

        Size getImageSize();

        Point getTopLeft() const;
        void setTopLeft(const Point &value);

        Point getButtonRight() const;
        void setButtonRight(const Point &value);

        void insertRect();

        vector<pair<Point, Point>> getVr() const;

        void delLastVR();

        void setPointsWithinVector(int pos);

        vector<uint> &getAuxRandom();

        Mat &getImage();

        int getHeightOfImage();
        int getWidthOfImage();

    private:

        Mat image;
        Point topLeft, buttonRight;
        vector<pair<Point,Point>> vr; //Vector of Rects
        vector<uint> auxRandom; //It is the Matrix to check the values
    };

    #endif // ORIGINIMAGEMANIPULATION_H
