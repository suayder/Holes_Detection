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
    int auxCont, auxToopsr, otheraux, t=0;
    vector<int> PointsOfimage;
    //Walks for all rects
    _int64 aux_get_inputs = 0;
    Point opsr, epsr; //Origin point of short rectangle, End Point of short rectangle
    for(int p=0;p<((*this->image)->getVr()).size();p++){

        (*this->image)->setPointsWithinVector(p);

        opsr.x = (((*this->image)->getTopLeft().x-5)>=0)?(*this->image)->getTopLeft().x-5:0;
        opsr.y = (((*this->image)->getTopLeft().y-5)>=0)?(*this->image)->getTopLeft().y-5:0;

        epsr.x = ((*this->image)->getButtonRight().x+5<=(*this->image)->getImageSize().width)?((*this->image)->getTopLeft().x+5):(*this->image)->getImageSize().width-((*this->image)->getTopLeft().x+5);
        epsr.y = ((*this->image)->getButtonRight().y+5<=(*this->image)->getImageSize().height)?((*this->image)->getTopLeft().y+5):(*this->image)->getImageSize().height-((*this->image)->getTopLeft().y+5);

        auxToopsr = opsr.y;

        //-----------------------------------------------------------------
        for(;opsr.x<epsr.x;opsr.x++){
            for(opsr.y = auxToopsr;opsr.y<epsr.y;opsr.y++){
                auxCont = 0;
                (*this->image)->allocateAuxMatrix(opsr, this->sizeOfRect);

                PointsOfimage = (*this->image)->getAuxRandom();

                //Walks for all RAM vector
                for(RAM& ram:this->ramVector){
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();
                    for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                        otheraux = PointsOfimage.at(this->retinalOrdering.at(auxCont));
                        aux_get_inputs = (otheraux==0)?(aux_get_inputs*10):(aux_get_inputs*10+1);
                        auxCont++;
                    }
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
                    //qDebug() <<"Duration: "<< duration;
                    t+=duration;
                    ram.insertValue_this_ram(aux_get_inputs, 1);
                    aux_get_inputs = 0;
                }
                (*this->image)->deleteAuxMatrix();
            }
        }
        qDebug()<<"Tes"<<t;
    }
}

vector<int> Descriptor::recognize(Point P) // Make multithreading
{
    //vector<std::thread> threads;
    //thread threads;
    vector<int> vectorOfResults; //int is the ammount of fired rams
    int resultFunction;



    //threads.push_back(std::thread(&Descriptor::FunctionOfEachRect, this, opsr));
    //threads.join();
    resultFunction = this->FunctionOfEachRect(P);
    //if(resultFunction>(this->ramVector.size()*0.8)){
    vectorOfResults.push_back(resultFunction);
    //qDebug()<<opsr.x<<opsr.y;
    //}

    //for(auto& t:threads)
    //   t.join();
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

void Descriptor::setSizeOfRect(int width, int heidth)
{
    this->sizeOfRect = Size(width, heidth);
}

int Descriptor::FunctionOfEachRect(Point _P) //Just to recognize
{
    int cont = 0, auxCont = 0, otherAux, t =0;
    vector<int> PointsOfimage;
    _int64 aux_get_inputs=0;

    (*this->image)->allocateAuxMatrix(_P, this->sizeOfRect);

    PointsOfimage = (*this->image)->getAuxRandom();

    //Walk through all the RAM
    for(RAM ram:this->ramVector){
        for(unsigned int i=0; i<this->ramNumberOfInputs;i++){
            otherAux = PointsOfimage.at(this->retinalOrdering.at(auxCont));
            aux_get_inputs = (otherAux==0)?(aux_get_inputs*10):(aux_get_inputs*10+1);
            auxCont++;
        }
        if(ram.search_Pattern(aux_get_inputs))
            cont++;


        aux_get_inputs = 0;
    }

    (*this->image)->deleteAuxMatrix(); //((*this->image)->getButtonRight().x - (*this->image)->getTopLeft().x);
    return cont;
}

void Descriptor::setRamNumberOfInputs(unsigned int value)
{
    this->ramNumberOfInputs = value;
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
            it->insertValue_this_ram(stoull(auxiliary), iaux);
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

void Descriptor::set_retine(vector<unsigned int> & retine)
{
    this->retinalOrdering = retine;
}

unsigned int Descriptor::getRamNumber() const
{
    return ramNumber;
}

unsigned int Descriptor::getRamNumberOfInputs() const
{
    return ramNumberOfInputs;
}

vector<unsigned int> Descriptor::getRetinalOrdering() const
{
    return retinalOrdering;
}
