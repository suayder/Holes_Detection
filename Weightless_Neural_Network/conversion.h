#ifndef CONVERSION_H
#define CONVERSION_H

#include <QDebug>
#include <QImage>
#include <QPixmap>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

class Conversion
{
public:

    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);
    cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );

};

#endif // CONVERSION_H
