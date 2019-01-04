#ifndef IMAGEJSON_H
#define IMAGEJSON_H

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QPoint>
#include <QMap>

//Temporary libraries
#include <QDebug>
#include <typeinfo>


using namespace std;

class Imagejson
{
public:
    Imagejson();
    QStringList getListOfNames();
    QMap<QString, vector<QPoint> > getImagepoints() const;
    vector<QPoint> searchPoints(QString);
    vector<QPoint> searchEndPoints(QString);
    int averageHeigh();
    int averageWidth();
    
protected:
    bool openImageToTrain(QString path); //Open each image
    bool openFolder(QString folderPath); //Folder wiht many images to use

private:
    unsigned int sumHeight; //sum of all height
    unsigned int sumWidth;
    int numberHoles; //in all images
    QMap<QString, vector<QPoint>> Imagepoints;
    QMap<QString, vector<QPoint>> imageEndPoints;
    vector<QPoint> vpoint;
    vector<QPoint> vEndPoint;

    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    QFile ImageFile;
    QFileInfo infoFile;
    QDir fileDirectory;
    QStringList files; //List of all images names
};

#endif // IMAGEJSON_H
