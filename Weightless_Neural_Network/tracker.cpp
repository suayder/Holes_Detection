#include "tracker.h"

Tracker::Tracker()
{

}

TrackerAnswer* Tracker::process(const Mat &source)
{
    TrackerAnswer* ans = new TrackerAnswer<void*>();
    Mat preImage = this->preproc->preprocess(source);
    std::vector<Rect> listOfRects = this->gSearchAlg->GlobalSearch(source);
    //foreach( rect) send it to classification
    //compose the classification answer
    //return the object ans

}
