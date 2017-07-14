#include "originimagemanipulation.h"
#include <QDebug>


originImageManipulation::originImageManipulation()
{
    this->auxRandom = NULL;
}

originImageManipulation::~originImageManipulation()
{
    if(this->auxRandom!=NULL) this->deleteAuxMatrix();//((this->buttonRight.x - this->topLeft.x)*(this->buttonRight.y - this->topLeft.y));
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
}

void originImageManipulation::thresholding()
{
    Mat im;
    unsigned long int sum_of_image = 0;
    for(int i = 0;i<=this->image.cols;i++){
        for(int j=0;j<=this->image.rows;j++){
            sum_of_image+=this->image.at<uchar>(j,i);
        }
    }
    sum_of_image /=(this->image.rows*this->image.cols);
    threshold(this->image, this->image, sum_of_image, 255, THRESH_BINARY);
    //resize(this->image, im,Size(this->image.cols/4, this->image.rows/5));
    //namedWindow("WINDOW", WINDOW_AUTOSIZE);
    //imshow("image", im);
    //waitKey(0);

}

void originImageManipulation::setCorrespondingPoins(int x1, int y1, int x2, int y2, int width, int height)
{

    this->topLeft = Point(((this->image.size().width/(double)width)*x1), ((this->image.size().height/(double)height)*y1));
    this->buttonRight = Point(((this->image.size().width/(double)width)*x2), ((this->image.size().height/(double)height)*y2));
    //qDebug()<< "topleft: (" << this->topLeft.x << "," << this->topLeft.y<<")";

}

void originImageManipulation::drawRect(Point topLeft, Point ButtonRiht)
{
    rectangle(this->image, topLeft, ButtonRiht, Scalar(255,0,255), 3,0,0);
    Mat im;
    resize(this->image, im,Size(this->image.cols/4, this->image.rows/5));
    namedWindow("WINDOW", WINDOW_AUTOSIZE);
    imshow("image", im);
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

char originImageManipulation::getRandomPoint() // This function return one binary value randommizing
{
    /*Point aux;

    while(1){
        srand(clock());
        int x =rand()%(this->buttonRight.x - this->topLeft.x);
        int y =rand()%(this->buttonRight.y - this->topLeft.y);

        //if((this->auxRandom)==NULL) this->allocateAuxMatrix((this->buttonRight.x - this->topLeft.x), (this->buttonRight.y - this->topLeft.y));
        aux = Point((this->topLeft.x + x), (this->topLeft.y + y));
        qDebug() << "("<<aux.x<<","<< aux.y<<")";
        if((this->auxRandom[x][y]) == false){
            this->auxRandom[x][y] = true;//setar um valor para o pixel da imagem

            qDebug() << "VALUE: " <<this->image.at<uchar>(aux);
            this->image.at<uchar>(aux) = 254;

            namedWindow( "Display window", WINDOW_AUTOSIZE );
            imshow("image", this->image);
            waitKey(1);*/
/*            break;
        }

        //return true;
    }
    if(this->image.at<uchar>(aux) == 255)
        return '1';
    else
        return '0';*/
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

void originImageManipulation::deleteAuxMatrix()
{
    free(this->auxRandom);
    this->auxRandom = NULL;
}

void originImageManipulation::allocateAuxMatrix(int col, int row)
{
    int contAux = 0;
    this->auxRandom = (char*) malloc((row*col)*sizeof(char));
    for(int n = 0; n<row; n++){
        for(int m = 0; m < col; m++){
            this->auxRandom[contAux] = ((this->image.at<uchar>((n+this->topLeft.y),(m+this->topLeft.x)) == 255)?'1':'0');
            contAux++;
            //this->image.at<uchar>((n+this->topLeft.x),(m+this->topLeft.y)) = 254;
            //namedWindow( "Display window", WINDOW_AUTOSIZE );
            //imshow("image", this->image);
            //waitKey(1);
        }
    }
}

void originImageManipulation::allocateAuxMatrix(Point _P, Size s)
{
    int contAux = 0;
    this->auxRandom = (char*) malloc((s.area())*sizeof(char));
    for(int n = 0; n< s.width; n++){
        for(int m = 0; m < s.height; m++){
            this->auxRandom[contAux] = ((this->image.at<uchar>((m+_P.y),(n+_P.x)) == 255)?'1':'0');
            contAux++;
            //this->image.at<uchar>((m+_P.y),(n+_P.x)) = 254;
        }
    }
    //namedWindow( "Display window", WINDOW_AUTOSIZE );
    //imshow("image", this->image);
    //waitKey(10);
}

void originImageManipulation::insertRect()
{
    this->vr.push_back(make_pair(this->topLeft, this->buttonRight));
}

vector<pair<Point, Point> > originImageManipulation::getVr() const
{
    return vr;
}

void originImageManipulation::setPointsWithinVector(int pos)
{
    qDebug() << "Pos: (" << this->vr[pos].first.x<<","<<this->vr[pos].first.y<<")";
    this->topLeft = this->vr[pos].first;
    this->buttonRight = this->vr[pos].second;
}

char *originImageManipulation::getAuxRandom() const
{
    return auxRandom;
}
