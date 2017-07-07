#include "descriptor.h"
#include <QDebug>
#include <QMessageBox>
Descriptor::Descriptor(unsigned int ramNumberofInputs, originImageManipulation **image)
{
    qDebug()<< "NUMBER: " << ramNumber;
    this->image = image;
    this->ramNumberOfInputs = ramNumberofInputs;
    this->ramNumber = 0;
    //(*this->image)->allocateAuxMatrix(Point(0,0), this->sizeOfRect); //Somente Para Teste
}

Descriptor::Descriptor(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image)
{
    qDebug()<< "NUMBER: " << ramNumber;
    this->image = image;
    this->ramNumberOfInputs = ramNumberOfInputs;
    this->ramNumber = 0;
    //this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);
    this->sizeOfRect = Sdefault;
    //(*this->image)->allocateAuxMatrix(Sdefault, this->sizeOfRect); //Somente Para Teste
}

void Descriptor::training()
{
    int auxCont;
    char *randomPoints;
    //Walks for all rects
    for(int p=0;p<((*this->image)->getVr()).size();p++){
        auxCont = 0;
        this->ramNumber = (unsigned int)((
                                          ((*this->image)->getVr()[p].first.x - (*this->image)->getVr()[p].second.x)*
                                          ((*this->image)->getVr()[p].first.y - (*this->image)->getVr()[p].second.y))/
                                         this->ramNumberOfInputs);

        this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);
        (*this->image)->setPointsWithinVector(p);

        (*this->image)->allocateAuxMatrix(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x),
                                          ((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));
        qDebug() <<"NAo OK";
        (*this->image)->shufflePoints(this->ramNumber, ((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x)*((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));
        randomPoints = (*this->image)->getAuxRandom();
        qDebug() <<"OK";

        //Walks for all RAM vector
        foreach(RAM ram, this->ramVector){

            for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                //qDebug() <<"V: "<< (*this->image)->getRandomPoint();
                ram.setInputstandart(randomPoints[auxCont]);
                //ram.setInputstandart((*this->image)->getRandomPoint());
                auxCont++;
            }
            this->mappingclass.insetIntoSet(ram.getInputstandart());
        }

        (*this->image)->deleteAuxMatrix();
    }
    //qDebug()<< this->mappingclass.test();
}

int Descriptor::recognize()
{
    int cont = 0, auxCont = 0;
    char *randomPoints;
    QMessageBox msg; //ATTENTION::: Erase this line of message
    (*this->image)->allocateAuxMatrix(this->sizeOfRect.width, this->sizeOfRect.height);
    (*this->image)->shufflePoints(this->ramNumber, this->sizeOfRect.width*this->sizeOfRect.height);
    randomPoints = (*this->image)->getAuxRandom();
    foreach (RAM ram, this->ramVector) {
        for(unsigned int i = 0; i<this->ramNumberOfInputs; i++){
            ram.setInputstandart(randomPoints[auxCont]);
            auxCont++;
        }

        if(!this->mappingclass.searchPatterns(ram.getInputstandart())){
            cont++;
        }
    }
    (*this->image)->deleteAuxMatrix();
    return cont;
}

void Descriptor::fillRamVector(vector<RAM> &ramV, unsigned int inputNumberBits, unsigned int ramNumber)
{
    for(int i = 0; i<ramNumber; i++){
        RAM newRam(inputNumberBits);
        ramV.push_back(newRam);
    }
}

int Descriptor::getHashSize()
{
    return this->mappingclass.getSetSize();
}

void Descriptor::deleteAllVector()
{
    foreach(RAM ram, this->ramVector)
        ram.deleteVector();
    this->ramVector.~vector();
}

void Descriptor::setSizeOfRect(const int width, const int height, const int P_width, const int P_heigth) //P_width = Pixmap width
{
    int w = ((*this->image)->getImageSize().width/P_width)*width;
    int h = ((*this->image)->getImageSize().height/P_heigth)*height;
    this->sizeOfRect = Size(w,h);
}

int Descriptor::FunctionOfEachRect()
{
    int cont = 0;
    char *randomPoints;

    (*this->image)->allocateAuxMatrix(this->sizeOfRect.width, this->sizeOfRect.height);
    (*this->image)->shufflePoints(this->ramNumber, this->sizeOfRect.width*this->sizeOfRect.height);
    randomPoints = (*this->image)->getAuxRandom();
    this->ramNumber = (unsigned int)(this->sizeOfRect.width*this->sizeOfRect.height)/this->ramNumberOfInputs;
    RAM _ram(this->ramNumberOfInputs);

    for(int i=0; i<this->ramNumber;i++){

        if(i%this->ramNumberOfInputs==0){
            if(!this->mappingclass.searchPatterns(_ram.getInputstandart())){
                cont++;
            }
            _ram.deleteVector();
        }
        _ram.setInputstandart(randomPoints[i]);
    }
    (*this->image)->deleteAuxMatrix();//((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x);
    return cont;
}

void Descriptor::setRamNumberOfInputs(unsigned int value)
{
    ramNumberOfInputs = value;
}
