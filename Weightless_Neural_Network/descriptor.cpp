#include "descriptor.h"

Descriptor::Descriptor(unsigned int ramNumber, unsigned int ramNumberofInputs)
{
    this->ramNumberOfInputs = ramNumberofInputs;
    this->ramNumber = ramNumber;
    this->ramVector = vector<RAM>(this->ramNumber, this->ramNumberOfInputs);
}

void Descriptor::setValuesOnEachRam(vector<char> &vector)
{
    for(int i= 0; i<this->ramVector.size(); i++){

        RAM *v = &this->ramVector[i];
        //Here i have to recive the values of the image and set in each vector[i]

    }

}


void Descriptor::training()
{

    for(int i= 0; i<this->ramVector.size(); i++){

        RAM *v = &this->ramVector[i];
    //    v->setInputstandart(vector);
        if(this->status==1){
    //       this->mappingclass.insetIntoSet(vector);
        }
    }
}


/*void Descriptor::insetIntoHash(int indexVector)
{
    size_t hashvalue = this->paternstrained(*(this->ramVector)[indexVector]);
}*/
