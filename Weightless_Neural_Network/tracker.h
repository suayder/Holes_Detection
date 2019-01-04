#ifndef TRACKER_H
#define TRACKER_H

#include "globalsearch.h"
#include "supervisedclassificationalg.h"
#include "preprocessor.h"

template <class T>
struct TrackerAnswer{
    std::vector<Rect> rectangles;
    T *anotherInfo;
};

class Tracker
{
    //Has a color
    //Has a name
    //Has
    Preprocessor *preproc;
    GlobalSearch *gSearchAlg;
    SupervisedClassificationAlg *classifier;
public:
    Tracker();
    TrackerAnswer* process(const Mat& imgSource);

};

#endif // TRACKER_H
