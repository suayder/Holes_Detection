// g++ ssearch.cpp -std=c++11 `pkg-config --cflags --libs opencv`

#include "ssearch.h"

std::vector<Rect> SelectiveSearch::generateListOfRects(Mat &im){

    Mat imClone;

    // speeding-up using multithreading
    setUseOptimized(true);
    setNumThreads(this->_nThreads);

    // resize image
    //TODO: parametrizar estas opções.
    int newHeight = 200;
    int newWidth = im.cols*newHeight/im.rows;
    resize(im, imClone, Size(newWidth, newHeight));


    // create Selective Search Segmentation Object using default parameters
    Ptr<SelectiveSearchSegmentation> ss = createSelectiveSearchSegmentation();
    // set input image on which we will run segmentation
    ss->setBaseImage(imClone);

    // Switch to fast but low recall Selective Search method
    ss->switchToSelectiveSearchFast();

    // run selective search segmentation on input image
    std::vector<Rect> rects;
    ss->process(rects);

    //To map points to the points at orginal imag
    float relx = im.cols/imClone.cols;
    float rely = im.rows/imClone.rows;

    unsigned int aux_width, aux_height;
    for(Rect& rect:rects){
        aux_width = rect.width*relx;
        aux_height = rect.height*rely;

        rect.x = rect.x*relx;
        rect.y = rect.y*rely;

        rect.width = aux_width;
        rect.height = aux_height;
    }
    
    return rects;
}
