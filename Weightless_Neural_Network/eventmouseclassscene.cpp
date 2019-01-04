#include "eventmouseclassscene.h"
#include <QDebug>
#include <QRect>




EventMouseClassScene::EventMouseClassScene(QWidget *parent) : QGraphicsScene(parent)
{

}

QPoint EventMouseClassScene::getPoint1() const
{
    return point1;
}

QPoint EventMouseClassScene::getPoint2() const
{
    return point2;
}

int EventMouseClassScene::sizeframe()
{
    return ABSOLUTEVALUE((this->point1.x()-this->point2.x())*(this->point1.y()-this->point2.y()));
}

void EventMouseClassScene::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    this->pointflag = false;
    if(ev->button()==Qt::LeftButton){
        this->point1 = ev->pos().toPoint();
        this->point2 = ev->pos().toPoint();
        emit Mouse_Pressed();
        this->pointflag = true;
        qDebug() <<"position x: "<< QString::number(this->point1.x());
    }

}

void EventMouseClassScene::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    if(this->pointflag ==true){
        this->point2 = ev->pos().toPoint();
        emit Mouse_Move();
    }
}

void EventMouseClassScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    this->point2 = ev->pos().toPoint();
    this->pointflag = false;
    qDebug() << "\n\nX1: "<<this->point1.x()<< "\nY1: " << this->point1.y() << "\nX2" << this->point2.x() << "\nY2: " << this->point2.y();
    emit Mouse_Released();

}

/*************************************************************************************************************

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine){
        if(!itemToDraw){
            itemToDraw = new QGraphicsLineItem();
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            itemToDraw->setPos(origPoint);
        }
        itemToDraw->setLine(0,0,
                            event->scenePos().x() - origPoint.x(),
                            event->scenePos().y() - origPoint.y());
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}
*/
