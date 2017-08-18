#ifndef IMAGEJSON_H
#define IMAGEJSON_H

#include<iostream>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QFile>
#include<QDir>
#include<QPoint>

#include <QDebug>

using namespace std;

class Imagejson
{
public:
    Imagejson();
    QStringList getListOfNames();
    QHash<QString, vector<QPoint> > getImagepoints() const;
    vector<QPoint> searchPoints(QString);
    int averageHeigh();
    int averageWidth();
    
protected:
    bool openImageToTrain(QString path); //Open each image
    bool openFolder(QString folderPath); //Folder wiht many images to use

private:
    unsigned int sumHeight; //sum of all height
    unsigned int sumWidth;
    int numberHoles; //in all images
    QHash<QString, vector<QPoint>> Imagepoints;
    vector<QPoint> vpoint;

    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    QFile ImageFile;
    QDir fileDirectory;
    QStringList files; //List of all images names
};

#endif // IMAGEJSON_H
