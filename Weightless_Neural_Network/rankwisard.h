#ifndef RANKWIZARD_H
#define RANKWIZARD_H

#include "rankalgorithm.h"
#include "originimagemanipulation.h"
#include "ram.h"

class RankWisard
{

private:
    const n_Tuple_size n_tuple;
    const cv::Size boundingBox;
    vector<RAM_RankWizard> discriminator;
    RankAlgorithm rank;

    vector<pair<uint,uint>> retina;
    void set_retine();

    //-----------Functions used in tracking part------------
    uint* allocRandVector(uint sizeVector);

public:
    RankWisard(const n_Tuple_size n_tuple, const cv::Size s);
    ~RankWisard();

    void training(const Point initialPoint, const Mat &image); //Train in user interface
    void training(const Mat &image); //Train unsing Selective Search Algorithm
    uint testBox(const Point topLeft, const Mat &image); //Test in user interface mode
    void _tracker_ssearch(Mat &image, vector<Rect> rects, String path_to_save, double thereshold); //Tracker with selective search algorithm
    void tracker(const Mat &image, String path_to_save); //Go through a image and search holes at then

    uint getDescriptorSize();
    cv::Size getBoundingBox() const;
};


#endif // RANKWIZARD_H
