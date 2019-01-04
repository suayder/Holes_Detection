#ifndef GLOBALSEARCH_H
#define GLOBALSEARCH_H
//TODO: include all necessary classes Rect, Mat, etc.
/**
 * This abstract class works like an interface for all global search algorithm.
 * GlobalSearch stands for algorithms that generate a list of rects for a tracker to explore.
 * A simple example of an algorithm like that is to generate a list of linearly spaced equal rects.
 * @brief The GlobalSearch class
 */
class GlobalSearch
{
public:
    virtual GlobalSearch();
    virtual vector<Rect> generateListOfRects(Mat &img source);
};

#endif // GLOBALSEARCH_H
