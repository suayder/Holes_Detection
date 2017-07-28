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
    this->set_retine();
}

Descriptor::Descriptor()
{

}

void Descriptor::training()
{
    int auxCont;
    char *PointsOfimage=NULL;
    //Walks for all rects
    string aux_get_inputs;
    for(int p=0;p<((*this->image)->getVr()).size();p++){
        auxCont = 0;

        /************
        qDebug()<<"TOTAL BITS IN RECT: " <<this->ramNumberOfInputs*this->ramNumber;
        qDebug()<<"SIZE OF RECT: "<<(*this->image)->rectangleSize(); //THIS IS THE SIZE
        qDebug()<<"SIZE OF RECT IN NETWORK: "<<this->sizeOfRect.area();
        qDebug()<<"RAM NUMBER: " <<this->ramNumber;
        /**********/

        //this->fillRamVector(this->ramVector, this->ramNumberOfInputs, this->ramNumber);

        //qDebug()<<"RAM VECTOR SIZE: "<<this->ramVector.size();

        (*this->image)->setPointsWithinVector(p);

        (*this->image)->allocateAuxMatrix(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x),
                                          ((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));

        //qDebug()<<"SIZE OF AUX MATRIX: "<<(((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x)*
        //                                 ((*this->image)->getButtonRight().y - (*this->image)->getTopLeft().y));
        PointsOfimage = (*this->image)->getAuxRandom();
        this->test = (*this->image)->getAuxRandom();

        //Walks for all RAM vector
        //qDebug()<<PointsOfimage;
        for(RAM& ram:this->ramVector){
            for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                aux_get_inputs.push_back(PointsOfimage[this->retinalOrdering.at(auxCont)]);
                auxCont++;
            }
            ram.insertValue_this_ram(aux_get_inputs, 1);
            //qDebug()<<QString::fromStdString(aux_get_inputs);
            //qDebug()<<this->ramVector.size();
            //this->ramVector.at(0).print();
            aux_get_inputs.clear();
        }
        //(*this->image)->deleteAuxMatrix();
    }
}

vector<pair<Point, int>> Descriptor::recognize(Point P) // Make multithreading
{
    //vector<std::thread> threads;
    //thread threads;
    vector<pair<Point, int>> vectorOfResults;
    int resultFunction;
    for(P.x;P.x+(*this->image)->getRectWidth()<(*this->image)->getImageSize().width;P.x+=(*this->image)->getRectWidth()){
        //P.y = 0;
        for(P.y=0;P.y+(*this->image)->getRecHeight()<(*this->image)->getImageSize().height;P.y+=(*this->image)->getRecHeight()){
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
    int cont = 0, auxCont = 0;
    char *PointsOfimage;
    string aux_get_inputs;

    (*this->image)->allocateAuxMatrix(_P, this->sizeOfRect);
    //(*this->image)->shufflePoints(this->ramNumber, this->sizeOfRect.width*this->sizeOfRect.height);
    PointsOfimage = (*this->image)->getAuxRandom();
    //this->ramNumber = (unsigned int) (*this->image)->rectangleSize()/this->ramNumberOfInputs;
    //RAM _ram(this->ramNumberOfInputs);
    //qDebug()<< _P.x<<","<<_P.y;
    if(_P ==Point(0,0)){
        int b=0;
        for(auto ram:this->ramVector){
            for(unsigned int i=0;i<this->ramNumberOfInputs;i++){
                if(this->test[b]!=PointsOfimage[b])
                    qDebug()<<b<<":"<<this->test[b]<<"-"<<PointsOfimage[b];
                b++;
            }
        }
        //qDebug()<<"BITS:"<<PointsOfimage;
    }

    //Walk through all the RAM
    for(auto ram:this->ramVector){

        for(unsigned int i=0; i<this->ramNumberOfInputs;i++){
            aux_get_inputs.push_back(PointsOfimage[this->retinalOrdering.at(auxCont)]);
            auxCont++;
        }
        if(ram.search_Pattern(aux_get_inputs))
            cont++;

        aux_get_inputs.clear();
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

void Descriptor::load_a_map()
{
    ifstream input;
    string auxiliary, auxiliary1;
    int iaux;
    input.open("../Weightless_Neural_Network/fileSalved/file.txt");
    if(input.is_open()){
        getline(input, auxiliary);
        this->ramNumberOfInputs = stoi(auxiliary);
        auxiliary.clear();
        getline(input, auxiliary);
        this->ramNumber = stoi(auxiliary);
        auxiliary.clear();
        getline(input, auxiliary);
        getline(input, auxiliary1);
        this->sizeOfRect = Size(stoi(auxiliary), stoi(auxiliary1));

        this->fillRamVector();
        vector<RAM>::iterator it = this->ramVector.begin();
        char delimiter(',');
        char ramDelimiter('-');
        getline(input, auxiliary);

        while(!input.eof()){
            getline(input, auxiliary, delimiter);
            if(auxiliary.front()==ramDelimiter){
                it++;
                auxiliary.erase(auxiliary.begin(), auxiliary.begin()+2);
                //getline(input, auxiliary, delimiter);
            }
            //qDebug()<<QString::fromStdString(auxiliary);
            getline(input, auxiliary1);
            iaux = stoi(auxiliary1);
            it->insertValue_this_ram(auxiliary, iaux);
        }
    }
    else{
        cout<<"ERROR: Cannot open file"<<endl;
    }
    input.close();
    qDebug()<< "PRINT: ";
    this->p();
    //this->mappingclass.readHash(, this- >numOfIter);
}

void Descriptor::set_retine()
{
    int v = (*this->image)->rectangleSize();
    for(int i=0;i<v;i++){
        this->retinalOrdering.push_back(i);
    }
    int i=0;
    while(i<2*this->ramNumber){
        srand(clock());
        int x =rand()%v;
        srand(clock());
        int x1 =rand()%v;
        if(x!=x1){
            SWAP(this->retinalOrdering[x],this->retinalOrdering[x1]);
            i++;
        }
    }
}

unsigned int Descriptor::getRamNumber() const
{
    return ramNumber;
}
