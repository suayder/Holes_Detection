#include "imagejson.h"

Imagejson::Imagejson()
{
    this->numberHoles = 0;
    this->sumWidth = 0;
    this->sumHeight = 0;
    this->vpoint.clear();
}

int Imagejson::averageHeigh()
{
    return (this->sumHeight/this->numberHoles);
}

int Imagejson::averageWidth()
{
    return (this->sumWidth/this->numberHoles);
}

bool Imagejson::openImageToTrain(QString path)
{
    this->ImageFile.setFileName(path);
    if(this->ImageFile.open(QIODevice::ReadOnly)){
        QJsonObject objAux;
        this->jsonDocument = QJsonDocument::fromJson(QString(this->ImageFile.readAll()).toUtf8());
        this->ImageFile.close();
        this->jsonObject = this->jsonDocument.object();
        this->jsonArray = this->jsonObject["points"].toArray();
        foreach(const QJsonValue& t,this->jsonArray){
            objAux = t.toObject();
            this->sumHeight+=(objAux["BottonRight_X"].toInt()-objAux["TopLeft_X"].toInt());
            this->sumWidth+=(objAux["BottonRight_Y"].toInt()-objAux["TopLeft_Y"].toInt());
            this->numberHoles++;
            this->vpoint.push_back(QPoint(objAux["TopLeft_X"].toInt(),objAux["TopLeft_Y"].toInt()));
        }
        this->Imagepoints.insert(this->ImageFile.fileName(), this->vpoint);
        this->vpoint.clear();
        return true;
    }
    else{
        return false;
    }
}

bool Imagejson::openFolder(QString folderPath)
{
    this->fileDirectory.setPath(folderPath);
    if(this->fileDirectory.exists()){
        this->fileDirectory.setNameFilters(QStringList()<<"*.json");
        this->files = this->fileDirectory.entryList();
        for(auto file:this->files){
            if(!this->openImageToTrain(this->fileDirectory.filePath(file)))
                return false;
        }
        for(auto& file:this->files){
            file.remove(".json", Qt::CaseSensitive);
        }
        return true;
    }
    return false;
}

QStringList Imagejson::getListOfNames()
{
    return this->files;
}

QHash<QString, vector<QPoint> > Imagejson::getImagepoints() const
{
    return Imagepoints;
}

vector<QPoint> Imagejson::searchPoints(QString strTosearch)
{
    QHash<QString, vector<QPoint>>::const_iterator it = this->Imagepoints.find(strTosearch);
    return *it;
}
