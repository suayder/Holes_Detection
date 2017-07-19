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
    this->sizeOfRect = Sdefault;
    this->ramNumber = Sdefault.area()/ramNumberOfInputs;
    this->numOfIter = 0;
    //this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);
    this->fillRamVector();
}

void Descriptor::training()
{
    int auxCont;
    char *randomPoints=NULL;
    //Walks for all rects
    string aux_get_inputs;
    for(int p=0;p<((*this->image)->getVr()).size();p++){
        auxCont = 0;

        //************
        qDebug() << "NUMBER IN EACH RAM: "<<this->ramNumberOfInputs;
        qDebug()<<"TOTAL BITS IN RECT: " <<this->ramNumberOfInputs*this->ramNumber;
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
        //qDebug()<<randomPoints;
        for(RAM& ram:this->ramVector){
            for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                aux_get_inputs.push_back(randomPoints[auxCont]);
                auxCont++;
            }
            ram.insertValue_this_ram(aux_get_inputs, 1);
            //qDebug()<<QString::fromStdString(aux_get_inputs);
            //qDebug()<<this->ramVector.size();
            //this->ramVector.at(0).print();
            aux_get_inputs.clear();
        }
        (*this->image)->deleteAuxMatrix();
    }
}

vector<pair<Point, int>> Descriptor::recognize(Point P) // Make multithreading
{
    //vector<std::thread> threads;
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
            if(resultFunction>(this->ramVector.size()*0.8)){
                vectorOfResults.push_back(make_pair(P, resultFunction));
            }
        }
    }
    //for(auto& t:threads)
        //t.join();
    return vectorOfResults;
}

void Descriptor::fillRamVector()
{
    for(int i = 0; i<this->ramNumber; i++){
        RAM newRam(this->ramNumberOfInputs);
        this->ramVector.push_back(newRam);
    }
}

void Descriptor::setSizeOfRect(const int width, const int height, const int P_width, const int P_heigth) //P_width = Pixmap width
{
    int w = ((*this->image)->getImageSize().width/P_width)*width;
    int h = ((*this->image)->getImageSize().height/P_heigth)*height;
    this->sizeOfRect = Size(w,h);
}

int Descriptor::FunctionOfEachRect(Point _P) //Just to recognize
{
    int cont = 0, ramReference = 0;
    char *randomPoints;
    string aux_get_inputs;

    (*this->image)->allocateAuxMatrix(_P, this->sizeOfRect);
    (*this->image)->shufflePoints(this->ramNumber, this->sizeOfRect.width*this->sizeOfRect.height);
    randomPoints = (*this->image)->getAuxRandom();
    this->ramNumber = (unsigned int)(this->sizeOfRect.width*this->sizeOfRect.height)/this->ramNumberOfInputs;
    //RAM _ram(this->ramNumberOfInputs);

    for(int i=0; i<this->ramNumber;i++){
        aux_get_inputs.push_back(randomPoints[i]);

        if(i%this->ramNumberOfInputs==0){
            if(this->ramVector.at(ramReference).search_Pattern(aux_get_inputs))
                cont++;
            aux_get_inputs.clear();
        }
    }
    (*this->image)->deleteAuxMatrix(); //((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x);
    return cont;
}

cv::Size Descriptor::getSizeOfRect() const
{
    return sizeOfRect;
}

void Descriptor::saveNetwork()
{
    ofstream output;
    output.open("../Weightless_Neural_Network/fileSalved/file.txt");
    output << this->ramNumberOfInputs<<endl; //Number of inputs on each ram
    output<<this->ramNumber<<endl; //Number of rans
    output<<((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x)<<endl;//Width
    output<<((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y); //Height
    for(auto _ram:this->ramVector){
        output<<"\n";
        output<<"-";
        for(auto &valueThisRam:_ram.getMap()){
           output<<"\n";
           output<<valueThisRam.first<<","<<valueThisRam.second;
        }
    }
    output.close();
}

void Descriptor::read_a_map()
{
    ifstream input;
    char auxiliary;
    int i;
    input.open("../Weightless_Neural_Network/fileSalved/file.bin");
    getline(input, this->ramNumberOfInputs);
    getline(input, this->ramNumber);
    i = stoi(sizeOfVector);
    getline(input, sizeOfVector);
    numiter = stoi(sizeOfVector);
    /*if(input.is_open()){
        this->setPatterns.clear();
        while(input >> auxiliary){
            this->patterns.push_back(auxiliary);
            if(this->patterns.size()==i){
                this->setPatterns.insert(this->patterns);
                this->patterns.clear();
            }
        }
    }
    else{
        cout<<"ERROR: Cannot open file"<<endl;
    }*/
    input.close();
    //this->mappingclass.readHash(, this- >numOfIter);
}
