#ifndef SUPERVISEDCLASSIFICATIONALG_H
#define SUPERVISEDCLASSIFICATIONALG_H
#include<vector>

typedef unsigned int uint;
template<class T>
struct ClassificationAnswer{
    uint winnerClass;
    //Class and values
    std::vector<unsigned int, double> answer;
    T optional;
};


template<class T>
class SupervisedClassificationAlg
{
public:
    virtual SupervisedClassificationAlg();
    virtual ClassificationAnswer<T> classify(const CvMat input, const Rect area);
    virtual void train(uint discriminatorId, const CvMat input, const Rect area);
};

#endif // SUPERVISEDCLASSIFICATIONALG_H
