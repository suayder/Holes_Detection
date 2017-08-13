#ifndef TRACKER_H
#define TRACKER_H

#include<iostream>
#include<QJsonObject>
#include<QJsonDocument>
#include<QFile>
#include<QDir>

using namespace std;

class Tracker
{
public:
    Tracker();

protected:
    void openImageToTrain(string path); //Open each image
    bool openFolder(QString folderPath); //Folder wiht many images to use
    training();
    search();

private:
    QJsonDocument jsonDocument();
    QFile ImageFile;
    QDir fileDirectory;
};

#endif // TRACKER_H
