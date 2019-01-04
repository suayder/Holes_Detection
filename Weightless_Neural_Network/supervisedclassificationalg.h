#ifndef SUPERVISEDCLASSIFICATIONALG_H
#define SUPERVISEDCLASSIFICATIONALG_H
#include<vector>

template <class T>
struct ClassificationAnswer{
    uint winnerClass;
    //uint identificando a classe e o double pra dizer a quantidade de pertencimento.
    std::vector<unsigned int, double> answer;
    T optional;
};
/**
 * A classe abstrata SupervisedClassificationAlg é utilizada apenas para organização do tracker.
 * Um tracker possui um ou mais algoritmos de classificação supervisionado.
 * T é o tipo de retorno da tarefa de classificação. Por exemplo, se é uma rede neural sem peso como a WISARD,
 * o tipo retornado pode ser um vetor de informações
 * (como o discriminador com mais rams disparadas, o segundo discriminador disparado, número de rams disparadas, etc.)
 */
template <class T>
class SupervisedClassificationAlg
{
public:
    virtual SupervisedClassificationAlg();
    virtual ClassificationAnswer<T> classify(const CvMat input, const Rect area);
    virtual void train(uint discriminatorId, const CvMat input, const Rect area);
};

#endif // SUPERVISEDCLASSIFICATIONALG_H
