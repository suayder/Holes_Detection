#ifndef WISARD_H
#define WISARD_H
#include <vector>

#include "supervisedclassificationalg.h"
#include "discriminator.h"
#include "ram.h"

using namespace std;

struct WisardAnswer{
    //the index of the discriminator with the greatest number of fired rams
    uint winner;
    //number of fired rams of the winner discriminator
    uint winnerFiredRams;
    //This gives a vector with all discriminators and their respective number of fired rams
    vector<uint> answer;
};

class Wisard: public SupervisedClassificationAlg<WisardAnswer>
{
    vector<Discriminator*> discs;
public:
    Wisard();
};

#endif // WISARD_H
