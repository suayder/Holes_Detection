#include "tracker.h"

Tracker::Tracker()
{
    this->numberHoles = 0;
    this->sumWidth = 0;
    this->sumHeight = 0;
}

int Tracker::averageHeigh()
{
    return (this->sumHeight/this->numberHoles);
}

int Tracker::averageWidth()
{
    return (this->sumWidth/this->numberHoles);
}

bool Tracker::openImageToTrain(QString path)
{
    this->ImageFile.setFileName(path);
    if(this->ImageFile.open(QIODevice::ReadOnly)){
        QJsonObject objAux;
        this->jsonDocument.fromJson(this->ImageFile);
        this->jsonObject = this->jsonDocument.object();
        this->jsonArray = this->jsonObject["points"].toArray();
        foreach(const QJsonValue& t,this->jsonArray){
            objAux = t.toObject();
            this->sumHeight+=(objAux["BottonRight_X"].toInt()-objAux["TopLeft_X"].toInt());
            this->sumWidth+=(objAux["BottonRight_Y"].toInt()-objAux["TopLeft_Y"].toInt());
            this->numberHoles++;
        }
        this->ImageFile.close();
        return true;
    }
    else{
        return false;
    }
}

bool Tracker::openFolder(QString folderPath)
{
    this->fileDirectory.setPath(folderPath);
    if(this->fileDirectory.exists()){
        this->files = this->fileDirectory.entryList(QDir::Filters("*.json"));
        for(auto file:this->files){
            if(!this->openImageToTrain(this->fileDirectory.filePath(file)))
                return false;
        }
        return true;
    }
    return false;
}
