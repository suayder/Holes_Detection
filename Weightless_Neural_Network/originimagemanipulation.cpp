#include "originimagemanipulation.h"
#include <QDebug>


originImageManipulation::originImageManipulation()
{
    this->auxRandom = NULL;
}

void originImageManipulation::imageRead(String directory)
{
    this->image = imread(directory, CV_LOAD_IMAGE_GRAYSCALE);
}

void originImageManipulation::thresholding()
{

 threshold(this->image, this->image, 127, 255, THRESH_BINARY);

}

void originImageManipulation::setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height)
{

    this->topLeft = Point(((this->image.size().width/(double)width)*x1), ((this->image.size().height/(double)height)*y1));
    this->buttonRight = Point(((this->image.size().width/(double)width)*x2), ((this->image.size().height/(double)height)*y2));

}

void originImageManipulation::drawRect(Point topLeft, Point ButtonRiht)
{
    rectangle(this->image, topLeft, ButtonRiht, Scalar(0), 3,0,0);
    imshow("image", this->image);
    waitKey(0);

}

int originImageManipulation::rectangleSize()
{
    try{
        return ABSOLUTEVALUE((this->topLeft.x - this->buttonRight.x)*(this->topLeft.y - this->buttonRight.y));
    }
    catch(exception& e){
        cout << "ERROR IN RECTANGLE SIZE FUNCTION - "<< e.what() <<endl;
    }

}


void originImageManipulation::getRandomPoint() // This function return one binary value randommizing
{
    srand(time(NULL));
    int x =rand()%(this->buttonRight.x - this->topLeft.x);
    int y =rand()%(this->buttonRight.y - this->topLeft.y);
    if((this->auxRandom)==NULL) this->allocateAuxMatrix((this->buttonRight.x - this->topLeft.x), (this->buttonRight.y - this->topLeft.y));
    Point aux((this->topLeft.x + x), (this->topLeft.y + y));
    qDebug() << aux.x << aux.y;
    if((this->auxRandom[x][y]) == false){
        this->auxRandom[x][y] = true;//setar um valor para o pixel da imagem
        this->image.at<uchar>(aux) = 254;
    }
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow("image", this->image);
    waitKey(1);
    //return true;
}

void originImageManipulation::deleteAuxRandom(int i)
{
    for(int n = 0; n < i; n++){
        delete[] this->auxRandom[n];
    }
    delete[] this->auxRandom;
    this->auxRandom = NULL;
}

void originImageManipulation::allocateAuxMatrix(int row, int col)
{
    this->auxRandom = new bool *[row];
    for(int n =0; n< row ;n++){
        this->auxRandom[n] = new bool[col];
    }
    for(int n = 0; n<row; n++){
        for(int m = 0; m < col; m++){
            this->auxRandom[n][m] = false;
        }
    }
}
