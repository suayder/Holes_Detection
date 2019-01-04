#include "discriminator.h"
#include <QDebug>
#include <QMessageBox>
Discriminator::Discriminator(unsigned int ramNumberofInputs, originImageManipulation **image)
{
    this->image = image;
    this->ramNumberOfInputs = ramNumberofInputs;
    this->ramNumber = 0;
    this->numOfIter = 0;
    this->imageData = (*this->image)->getImage();
}

Discriminator::Discriminator(Size Sdefault, unsigned int ramNumberOfInputs, originImageManipulation **image)
{
    this->image = image;
    this->ramNumberOfInputs = ramNumberOfInputs;
    this->sizeOfRect = Sdefault;
    this->ramNumber = Sdefault.area()/ramNumberOfInputs;
    this->numOfIter = 0;
    this->fillRamVector();
    this->set_retine();
    if(*this->image!=NULL)
        this->imageData = (*this->image)->getImage();
}

Discriminator::Discriminator()
{

}

void Discriminator::training()
{
    int auxCont, auxToopsr, x, y;
    uchar otherAux;
    bitStore get_inputs;
    Point opsr, epsr; //Origin point of short rectangle, End Point of short rectangle

    for(int p=0;p<((*this->image)->getVr()).size();p++){  //Walks for all rects

        (*this->image)->setPointsWithinVector(p);

        opsr.x = (((*this->image)->getTopLeft().x-5)>=0)?(*this->image)->getTopLeft().x-5:0;
        opsr.y = (((*this->image)->getTopLeft().y-5)>=0)?(*this->image)->getTopLeft().y-5:0;

        epsr.x = ((*this->image)->getButtonRight().x+5<=(*this->image)->getImageSize().width)?((*this->image)->getTopLeft().x+5):(*this->image)->getImageSize().width-((*this->image)->getTopLeft().x+5);
        epsr.y = ((*this->image)->getButtonRight().y+5<=(*this->image)->getImageSize().height)?((*this->image)->getTopLeft().y+5):(*this->image)->getImageSize().height-((*this->image)->getTopLeft().y+5);

        auxToopsr = opsr.x;

        //-----------------------------------------------------------------
        for(;opsr.y<epsr.y;opsr.y++){
            for(opsr.x = auxToopsr;opsr.x<epsr.x;opsr.x++){
                auxCont = 0;

                //Walks for all RAM vector
                for(RAM& ram:this->ramVector){
                    for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
                        y = this->retinalOrdering.at(auxCont)/this->sizeOfRect.width;
                        x = this->retinalOrdering.at(auxCont)%this->sizeOfRect.width;
                        otherAux = imageData.at<uchar>(y+opsr.y,x+opsr.x);

                        (otherAux==255)?(get_inputs.push_back('1')):(get_inputs.push_back('0'));
                        auxCont++;
                    }
                    ram.insertValue_this_ram(get_inputs, 1);
                    get_inputs.clear();
                }
            }
        }
    }
}

void Discriminator::training(Mat &im)
{
    int auxCont = 0, x, y;
    uchar otherAux;
    bitStore get_inputs = "";

    //Walks for all RAM vector
    for(RAM& ram:this->ramVector){
        for(unsigned int j = 0; j<this->ramNumberOfInputs; j++){
            y = this->retinalOrdering.at(auxCont)/this->sizeOfRect.width;
            x = this->retinalOrdering.at(auxCont)%this->sizeOfRect.width;
            otherAux = im.at<uchar>(y,x);
            (otherAux==255)?get_inputs.push_back('1'):get_inputs.push_back('0');
            auxCont++;
        }
        ram.insertValue_this_ram(get_inputs, 1);
        get_inputs.clear();
    }
}

//Function to Tracker
void Discriminator::recognize(Mat& image, const vector<Rect>& rects, const std::string& path_to_save, double thereshold)
{
    Mat im_clone;

    int cont = 0, auxCont = 0, x, y;
    uchar otherAux;
    bitStore get_inputs="";

    for(Rect rect:rects){
        im_clone = image(rect); //Cut rectangle rect
        resize(im_clone,im_clone,this->sizeOfRect);

        //Walk through all the RAM
        for(RAM ram:this->ramVector){
            for(unsigned int i=0; i<this->ramNumberOfInputs;i++){
                if(auxCont>=this->retinalOrdering.size()) //GAMBIARRA. Arrumar depois
                    break;
                y = this->retinalOrdering.at(auxCont)/this->sizeOfRect.width;
                x = this->retinalOrdering.at(auxCont)%this->sizeOfRect.width;

                otherAux = im_clone.at<uchar>(y,x);

                (otherAux==255)?(get_inputs.push_back('1')):(get_inputs.push_back('0'));
                auxCont++;
            }

            if(ram.search_Pattern(get_inputs))
                cont++;
            get_inputs.clear();
        }
        if(cont>=this->ramNumber*thereshold){
            originImageManipulation::drawRect(rect.tl(),rect.br(),image);
        }
    }
    imwrite(path_to_save,image);
}

void Discriminator::scrollThroughY(Point _p, const vector<int> &vrandom, int dx, int dy) //Only to be called by recognize function
{
    if(_p.y+this->sizeOfRect.height+dy > (*this->image)->getHeightOfImage())
        return;

    qDebug("1.2.3");

    this->scrollThroughX(_p, vrandom, dx, dy);

    _p.y += this->sizeOfRect.height + dy;

    this->scrollThroughY(_p, vrandom, dx, dy);

}

void Discriminator::scrollThroughX(Point _p, const vector<int> &vrandom, int _dx, int _dy)
{

    if(_p.x+this->sizeOfRect.width+_dx > (*this->image)->getWidthOfImage())
        return;

    Point P1; // this is to save the randomized point to send to the functionOfEachRect
    int resultFunction, x, y;

    for(int i = 0; i<(int)(_dx*_dy*0.02);i++){
        x = vrandom[i]%_dx;
        y = vrandom[i]/_dx;
        P1.x = _p.x+x;
        P1.y = _p.y+y;
        resultFunction =  this->FunctionOfEachRect(P1);
        qDebug()<<"Result Function: "<<resultFunction;
        if(resultFunction>this->ramNumber*0.85){
            originImageManipulation::drawRect(P1,Point(P1.x+this->sizeOfRect.width, P1.y+this->sizeOfRect.height), this->imageToDrawResult);
            break;
        }
    }

    _p.x = _p.x+this->sizeOfRect.width+_dx;

    this->scrollThroughX(_p, vrandom, _dx, _dy);

}

void Discriminator::fillRamVector()
{
    for(int i = 0; i<this->ramNumber; i++){
        RAM newRam(this->ramNumberOfInputs);
        this->ramVector.push_back(newRam);
    }
}

void Discriminator::setSizeOfRect(const int width, const int height, const int P_width, const int P_heigth) //P_width = Pixmap width
{
    int w = ((*this->image)->getImageSize().width/P_width)*width;
    int h = ((*this->image)->getImageSize().height/P_heigth)*height;
    this->sizeOfRect = Size(w,h);
}

void Discriminator::setSizeOfRect(int width, int heidth)
{
    this->sizeOfRect = Size(width, heidth);
}

uint Discriminator::FunctionOfEachRect(Point _P) //Just to recognize
{
    int cont = 0, auxCont = 0, x, y;
    uchar otherAux;
    bitStore get_inputs="";

    qDebug("Starting Point: %i, %i", _P.x, _P.y);

    //Walk through all the RAM
    for(RAM ram:this->ramVector){
        for(unsigned int i=0; i<this->ramNumberOfInputs;i++){
            y = this->retinalOrdering.at(auxCont)/this->sizeOfRect.width;
            x = this->retinalOrdering.at(auxCont)%this->sizeOfRect.width;

            otherAux = imageData.at<uchar>(y+_P.y,x+_P.x);


            (otherAux==255)?(get_inputs.push_back('1')):(get_inputs.push_back('0'));
            auxCont++;
        }
        if(ram.search_Pattern(get_inputs))
            cont++;
        get_inputs.clear();
    }

    return cont;
}

void Discriminator::setRamNumberOfInputs(unsigned int value)
{
    this->ramNumberOfInputs = value;
}

cv::Size Discriminator::getSizeOfRect() const
{
    return sizeOfRect;
}

void Discriminator::saveNetwork()
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

void Discriminator::load_a_map() //Text file
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

void Discriminator::set_retine()
{
    int v = this->sizeOfRect.area();
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

void Discriminator::set_retine(vector<unsigned int> & retine)
{
    this->retinalOrdering = retine;
}

unsigned int Discriminator::getRamNumber() const
{
    return ramNumber;
}

unsigned int Discriminator::getRamNumberOfInputs() const
{
    return ramNumberOfInputs;
}

vector<unsigned int> Discriminator::getRetinalOrdering() const
{
    return retinalOrdering;
}

void Discriminator::setImage(const Mat &value)
{
    this->imageData = value;
}
