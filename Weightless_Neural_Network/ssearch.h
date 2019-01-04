#ifndef SSEARCH_H
#define SSEARCH_H
#include "globalsearch.h"

#include "opencv2/ximgproc/segmentation.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <ctime>

using namespace cv;
using namespace cv::ximgproc::segmentation;


class SelectiveSearch: public GlobalSearch{
    unsigned int _nThreads;
public:
    inline SelectiveSearch(unsigned int nThreads = 4): _nThreads(nThreads){}
    std::vector<Rect> generateListOfRects(Mat &img source);

}
#endif // SSEARCH_H
