#include "originimagemanipulation.h"


originImageManipulation::originImageManipulation()
{
    this->auxRandom.clear();
}

originImageManipulation::~originImageManipulation()
{
    if(!this->auxRandom.empty()) this->auxRandom.clear();
}

Point originImageManipulation::getTopLeft() const
{
    return topLeft;
}

void originImageManipulation::setTopLeft(const Point &value)
{
    topLeft = value;
}

Point originImageManipulation::getButtonRight() const
{
    return buttonRight;
}

void originImageManipulation::setButtonRight(const Point &value)
{
    buttonRight = value;
}

void originImageManipulation::imageRead(String directory)
{
    this->buttonRight = Point(0,0);
    this->topLeft = Point(0,0);
    this->image = imread(directory, CV_LOAD_IMAGE_GRAYSCALE);
    //resize(this->image, this->image,Size(this->image.cols/5, this->image.rows/5));
}

void originImageManipulation::imageWrite(String directory, Mat image)
{
    qDebug()<<"write";
    imwrite(directory, image);
}

void originImageManipulation::thresholding()
{
    //Mat im;
    unsigned long int sum_of_image = 0;
    for(int i = 0;i<this->image.rows;i++){
        uchar *pt = this->image.ptr<uchar>(i);
        for(int j=0;j<=this->image.cols;j++){
            sum_of_image+= pt[j];
        }
    }
    sum_of_image /=(this->image.rows*this->image.cols);
    threshold(this->image, this->image, sum_of_image, 255, THRESH_BINARY);

}

void originImageManipulation::show()
{
    imshow("image", this->image);
    waitKey(0);

}

void originImageManipulation::setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height)
{

    this->topLeft = Point(((this->image.size().width/(double)width)*x1), ((this->image.size().height/(double)height)*y1));
    this->buttonRight = Point(((this->image.size().width/(double)width)*x2), ((this->image.size().height/(double)height)*y2));
    //qDebug()<< "topleft: (" << this->topLeft.x << "," << this->topLeft.y<<")";

}

void originImageManipulation::setCorrespondingPoins(int x1, int y1, int width, int height, Size size, int auxReference)
{
    this->topLeft = Point(((this->image.size().width/(double)width)*x1), ((this->image.size().height/(double)height)*y1));
    this->buttonRight = Point(this->topLeft.x+size.width, this->topLeft.y+size.height);
    this->vr.at(auxReference).first = this->topLeft;
    this->vr.at(auxReference).second = this->buttonRight;
}

void originImageManipulation::drawRect(Point topLeft, Point ButtonRiht)
{
    Mat im = this->image.clone();
    rectangle(im, topLeft, ButtonRiht, Scalar(125,0,125), 6,0,0);
    resize(im, im,Size(im.cols/4, im.rows/5));
    //namedWindow("WINDOW", WINDOW_AUTOSIZE);
    imshow("image", im);
    waitKey(0);
}

void originImageManipulation::drawRect(const Point& topLeft,const Point& ButtonRiht, Mat& image)
{
    rectangle(image, topLeft, ButtonRiht, Scalar(255,0,255), 6,0,0);
}

uint originImageManipulation::rectangleSize()
{
    try{
        return ABSOLUTEVALUE((this->topLeft.x - this->buttonRight.x)*(this->topLeft.y - this->buttonRight.y));
    }
    catch(exception& e){
        cout << "ERROR IN RECTANGLE SIZE FUNCTION - "<< e.what() <<endl;
    }
}

uint originImageManipulation::getRectWidth()
{
    return ABSOLUTEVALUE(this->buttonRight.x - this->topLeft.x);
}

uint originImageManipulation::getRecHeight()
{
    return ABSOLUTEVALUE(this->buttonRight.y-this->topLeft.y);
}

void originImageManipulation::shufflePoints(int numberOfRans, int sizeOfvector)
{
    int i = 0;
    while(i<numberOfRans){
        srand(clock());
        int x =rand()%(sizeOfvector);
        int x1 =rand()%(sizeOfvector);
        if(x!=x1 && ((this->auxRandom[x]=='0' || this->auxRandom[x]=='1') && (this->auxRandom[x1]=='0' || this->auxRandom[x1]=='1'))){
            SWAP(this->auxRandom[x],this->auxRandom[x1]);
            i++;
        }
    }
}

Size originImageManipulation::getImageSize()
{
    return this->image.size();
}

void originImageManipulation::insertRect()
{
    this->vr.push_back(make_pair(this->topLeft, this->buttonRight));
}

vector<pair<Point, Point> > originImageManipulation::getVr() const
{
    return vr;
}

void originImageManipulation::delLastVR()
{
    this->vr.pop_back();
}

void originImageManipulation::setPointsWithinVector(int pos)
{
    qDebug() << "Points within vector - Pos: (" << this->vr[pos].first.x<<","<<this->vr[pos].first.y<<")";
    this->topLeft = this->vr[pos].first;
    this->buttonRight = this->vr[pos].second;
}

vector<uint>& originImageManipulation::getAuxRandom()
{
    return auxRandom;
}

Mat& originImageManipulation::getImage()
{
    return image;
}

int originImageManipulation::getHeightOfImage()
{
    return this->image.size().height;
}

int originImageManipulation::getWidthOfImage()
{
    return this->image.size().width;
}
