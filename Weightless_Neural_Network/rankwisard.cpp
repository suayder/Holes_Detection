#include "rankwisard.h"
#define PERCENTAGE_TRIGGER 0.8

RankWisard::RankWisard(const n_Tuple_size n_tuple, const cv::Size s)
    :n_tuple(n_tuple),
      boundingBox(s),
      discriminator(s.area()/this->n_tuple, RAM_RankWizard(this->n_tuple))
{
    rank.setN(n_tuple);
    this->set_retine();
    srand(clock());
}

RankWisard::~RankWisard()
{
    this->discriminator.~vector<RAM_RankWizard>();
}

uint RankWisard::getDescriptorSize()
{
    return this->boundingBox.area()/(double)this->n_tuple;
}

cv::Size RankWisard::getBoundingBox() const
{
    return boundingBox;
}

void RankWisard::set_retine()
{
    int numOfram = this->boundingBox.area()/this->n_tuple;
    int v = this->boundingBox.area();

    for(int i=0;i<this->boundingBox.width;i++){
        for(int j = 0;j<this->boundingBox.height;j++){
            this->retina.push_back(make_pair(i,j));
        }
    }
    int i=0;
    while(i<2*numOfram){
        int x =rand()%v;
        srand(clock());
        int x1 =rand()%v;
        if(x!=x1){
            SWAP(this->retina[x].first,retina[x1].first);
            SWAP(this->retina[x].second,retina[x1].second);
            i++;
        }
    }
}

//================================Training=================================================

void RankWisard::training(const Point initialPoint, const Mat& image)
{
    int auxCont, auxToopsr;
    multimap<uchar,uchar> inputs;
    Point opsr, epsr; //Origin point of short rectangle, End Point of short rectangle

    const size_t numberOframs = this->boundingBox.area()/this->n_tuple;

    opsr.x = ((initialPoint.x-5)>=0)?initialPoint.x-5:0;
    opsr.y = ((initialPoint.y-5)>=0)?initialPoint.y-5:0;

    epsr.x = ((initialPoint.x+this->boundingBox.width+5)<=image.cols)?(initialPoint.x+5):image.cols-(initialPoint.x+5+this->boundingBox.width);
    epsr.y = ((initialPoint.y+this->boundingBox.height+5)<=image.rows)?(initialPoint.y+5):image.rows-(initialPoint.y+5+this->boundingBox.height);

    auxToopsr = opsr.x;

    //-----------------------------------------------------------------
    for(;opsr.y<epsr.y;opsr.y++){
        for(opsr.x = auxToopsr;opsr.x<epsr.x;opsr.x++){
            auxCont = 0;

            if(rand()%10<7){
                //Walks for all RAM vector
                for(unsigned int i = 0; i<numberOframs;i++){
                    for(unsigned int j = 0; j<this->n_tuple; j++){
                        inputs.insert({image.at<uchar>(this->retina[auxCont].second+opsr.y,
                                       this->retina[auxCont].first+opsr.x), (uchar)j});
                        auxCont++;
                    }
                    this->discriminator[i].insertLookUpRankTable(this->rank.encode(inputs));
                    inputs.clear();
                }
            }
        }
    }
}

void RankWisard::training(const Mat &image)
{
    int auxCont = 0;
    multimap<uchar,uchar> inputs;

    const size_t numberOframs = this->boundingBox.area()/this->n_tuple;

    //Walks for all RAM vector
    for(unsigned int i = 0; i<numberOframs;i++){
        for(unsigned int j = 0; j<this->n_tuple; j++){
            inputs.insert({image.at<uchar>(this->retina.at(auxCont).second,
                           this->retina.at(auxCont).first), (uchar)j});
            auxCont++;
        }
        this->discriminator[i].insertLookUpRankTable(this->rank.encode(inputs));
        inputs.clear();
    }
}

//================================Tracker=================================================

uint RankWisard::testBox(const Point topLeft, const Mat &image)
{
    int contReturn = 0, auxCont = 0;
    uint value_rank_decode;
    multimap<uchar, uchar> inputs;

    size_t numberOfRams = this->boundingBox.area()/(double)this->n_tuple;

    //Walk through all the RAM
    for(unsigned int i = 0; i<numberOfRams;i++){
        for(uint j=0; j<this->n_tuple;j++){

            inputs.insert({image.at<uchar>(this->retina.at(auxCont).second+topLeft.y,
                           this->retina.at(auxCont).first+topLeft.x),(uchar)j});

            auxCont++;
        }
        value_rank_decode = this->rank.decode(inputs);
        if(value_rank_decode > 0){
            if(this->discriminator[i].search_key(value_rank_decode))//verificar se o retorno de decode e -1
                contReturn++;
        }
        inputs.clear();
    }

    return contReturn;
}

void RankWisard::tracker(const Mat &image, String path_to_save)
{
    uint boxRows = image.rows/(image.rows/this->boundingBox.height);
    uint boxCols = image.cols/(image.cols/this->boundingBox.width);

    uint diffbox = boxCols*boxRows - this->boundingBox.area();
    uint diffX = boxCols-this->boundingBox.width;
    uint diffY = boxRows-this->boundingBox.height;

    uint *vetRandX = this->allocRandVector(diffX);
    uint *vetRandY = this->allocRandVector(diffY);

    Mat imageClone = image.clone();

    srand(clock());

   pair<uint, cv::Point> largerFitnessValue(0,Point(0,0));
   vector<pair<uint, cv::Point>> biggerFitnessBoxes;
   uint fitnessValue = 0;

    for(int i = 0; i<image.rows;i=i+boxRows){//walks through all image
        for(int j = 0; j<image.cols;j=j+boxCols){

            int q = 0;
            qDebug()<<"I: "<<i<<" J: "<<j;
            do{
                q++;
                coordinates px = rand()%diffX;
                coordinates py = rand()%diffY;
                fitnessValue = this->testBox(Point(vetRandX[px]+j, vetRandY[py]+i),image);
                if(largerFitnessValue.first<fitnessValue){
                    largerFitnessValue.first = fitnessValue;
                    largerFitnessValue.second.x = px;
                    largerFitnessValue.second.y = py;
                }
                if(fitnessValue>=PERCENTAGE_TRIGGER*this->discriminator.size()){
                    originImageManipulation::drawRect(Point(px,py), Point(px+this->boundingBox.height, py+this->boundingBox.width), imageClone);
                    qDebug()<<"Break";
                    break;
                }
                else{
                    if(q>diffX*diffY*0.20 && largerFitnessValue.first<(PERCENTAGE_TRIGGER-0.3)*this->discriminator.size()){
                        qDebug()<<"break";
                        break;
                    }
                }

            }while(q<diffX*diffY*0.35);
            biggerFitnessBoxes.push_back(largerFitnessValue);
        }
    }

    free(vetRandX);
    free(vetRandY);

    imwrite(path_to_save, imageClone);
}

void RankWisard::_tracker_ssearch(Mat &image, vector<Rect> rects, String path_to_save, double thereshold)
{
    int contReturn = 0, auxCont = 0;
    uint value_rank_decode;
    multimap<uchar, uchar> inputs;

    size_t numberOfRams = this->boundingBox.area()/(double)this->n_tuple;
    Mat im_clone, imteste;
    imteste = image.clone();

    //Walk through all the RAM
    for(Rect rect:rects){
        im_clone = image(rect);
        originImageManipulation::drawRect(rect.tl(),rect.br(),imteste);
        resize(im_clone,im_clone,this->boundingBox);

        for(unsigned int i = 0; i<numberOfRams;i++){
            for(uint j=0; j<this->n_tuple;j++){
                if(auxCont>=this->retina.size())//Gambiarra
                    break;
                inputs.insert({im_clone.at<uchar>(this->retina.at(auxCont).second,
                               this->retina.at(auxCont).first),(uchar)j});

                auxCont++;
            }
            value_rank_decode = this->rank.decode(inputs);
            if(value_rank_decode > 0){
                if(this->discriminator[i].search_key(value_rank_decode))//verificar se o retorno de decode e -1
                    contReturn++;
            }
            inputs.clear();
        }
        if(contReturn>=this->discriminator.size()*thereshold){
             originImageManipulation::drawRect(rect.tl(),rect.br(),image);
        }
    }
    imwrite(path_to_save, image);
    imwrite("1.jpg", imteste);
}

uint* RankWisard::allocRandVector(uint sizeVector){

    uint *vect = (uint*) malloc(sizeVector*sizeof(int));
    for(uint i=0; i<sizeVector;i++){
        vect[i] = i;
    }
    int i=0;
    while(i<2*sizeVector){
        srand(clock());
        int x = rand()%sizeVector;
        srand(clock());
        int x1 =rand()%sizeVector;
        if(x!=x1){
            SWAP(vect[x],vect[x1]);
            i++;
        }
    }
    return vect;
}
