#include "descriptor.h"
#include <QDebug>
#include <QMessageBox>
Descriptor::Descriptor(unsigned int ramNumberofInputs, originImageManipulation **image)
{
    this->image = image;
    this->ramNumberOfInputs = ramNumberofInputs;
    this->ramNumber = 0;
    this->numOfIter = 0;
}

Descriptor::Descriptor(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image)
{
    this->image = image;
    this->ramNumberOfInputs = ramNumberOfInputs;
    this->ramNumber = Sdefault.area()/ramNumberOfInputs;
    this->numOfIter = 0;
    //this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);
    this->sizeOfRect = Sdefault;
    this->fillRamVector();
}

void Descriptor::training()
{
    int auxCont;
    char *randomPoints=NULL;
    string aux_get_inputs;

    //Walks for all rects
    for(int p=0;p<((*this->image)->getVr()).size();p++){
        auxCont = 0;

        //************
        qDebug() << "NUMBER IN EACH RAM: "<<this->ramNumberOfInputs;
        qDebug()<<"TOTAL BITS IN RECT: " <<this->ramNumberOfInputs*this->ramNumber;
        qDebug()<<"TOTAL BITS IN RECT - " <<this->sizeOfRect.area();
        qDebug()<<"RAM NUMBER: " <<this->ramNumber;
        //**********

        //this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);

        qDebug()<<"RAM VECTOR SIZE: "<<this->ramVector.size();

        (*this->image)->setPointsWithinVector(p);

        (*this->image)->allocateAuxMatrix(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x),
                                          ((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));

        qDebug()<<"SIZE OF AUX MATRIX: "<<(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x)*
                                           ((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));

        (*this->image)->shufflePoints(this->ramNumber, ABSOLUTEVALUE(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x)*((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y)));
        randomPoints = (*this->image)->getAuxRandom();

        //Walks for all RAM vector
        foreach(RAM ram, this->ramVector){
            for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                aux_get_inputs.append(&randomPoints[auxCont]);
                auxCont++;
            }
            //qDebug()<< auxCont;
            ram.insertValue_this_ram(1, aux_get_inputs);
            aux_get_inputs.clear();
        }

        //this->mappingclass.print_hash();

        (*this->image)->deleteAuxMatrix();
        this->numOfIter++;
    }
    //qDebug()<< this->mappingclass.test();
}

vector<pair<Point, int>> Descriptor::recognize(Point P) // Make multithreading
{
  /*  //vector<std::thread> threads;
    //thread threads;
    vector<pair<Point, int>> vectorOfResults;
    int resultFunction;
    for(P.x+this->sizeOfRect.width;P.x+this->sizeOfRect.width<(*this->image)->getImageSize().width;P.x+=this->sizeOfRect.width){
        P.y = 0;
        for(P.y+this->sizeOfRect.height;P.y+this->sizeOfRect.height<(*this->image)->getImageSize().height;P.y+=this->sizeOfRect.height){
            //thread threads(&Descriptor::FunctionOfEachRect, this, P);
            //threads.join();
            resultFunction = this->FunctionOfEachRect(P);
            qDebug() <<"Result function: "<< resultFunction;
            if(resultFunction>((this->mappingclass.getSetSize()/this->numOfIter)*0.8)){
                vectorOfResults.push_back(make_pair(P, resultFunction));
            }
        }
    }
    //for(auto& t:threads)
        //t.join();
    return vectorOfResults;*/
}

void Descriptor::fillRamVector()
{
    for(int i = 0; i<this->ramNumber; i++){
        RAM newRam(this->ramNumberOfInputs);
        this->ramVector.push_back(newRam);
    }
}

int Descriptor::getHashSize()
{
    return this->mappingclass.getSetSize();
}

void Descriptor::setSizeOfRect(const int width, const int height, const int P_width, const int P_heigth) //P_width = Pixmap width
{
    int w = ((*this->image)->getImageSize().width/P_width)*width;
    int h = ((*this->image)->getImageSize().height/P_heigth)*height;
    this->sizeOfRect = Size(w,h);
}
/*
int Descriptor::FunctionOfEachRect(Point _P) //Just to recognize
{
    int cont = 0;
    char *randomPoints;

    (*this->image)->allocateAuxMatrix(_P, this->sizeOfRect);
    (*this->image)->shufflePoints(this->ramNumber, this->sizeOfRect.width*this->sizeOfRect.height);
    randomPoints = (*this->image)->getAuxRandom();
    this->ramNumber = (unsigned int)(this->sizeOfRect.width*this->sizeOfRect.height)/this->ramNumberOfInputs;
    RAM _ram(this->ramNumberOfInputs);

    for(int i=0; i<this->ramNumber;i++){

        if(i%this->ramNumberOfInputs==0){
            if(this->mappingclass.searchPatterns(_ram.getInputstandart())){
                cont++;
            }
            _ram.deleteVector();
        }
        _ram.setInputstandart(randomPoints[i]);
    }
    (*this->image)->deleteAuxMatrix(); //((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x);
    return cont;
}*/

void Descriptor::setRamNumberOfInputs(unsigned int value)
{
    ramNumberOfInputs = value;
}

cv::Size Descriptor::getSizeOfRect() const
{
    return sizeOfRect;
}

void Descriptor::saveMap()
{
    this->mappingclass.writeHash("../Weightless_Neural_Network/fileSalved/file.bin", this->ramNumberOfInputs, this->numOfIter);
}

void Descriptor::read_a_map()
{
    this->mappingclass.readHash("../Weightless_Neural_Network/fileSalved/file.bin", this->numOfIter);
}
