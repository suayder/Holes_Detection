#include "eventmouseclass.h"
#include <QDebug>
#include <QRect>

QPoint EventMouseClass::getPoint1() const
{
    return point1;
}

QPoint EventMouseClass::getPoint2() const
{
    return point2;
}

void EventMouseClass::setPoint1(const QPoint &value)
{
    point1 = value;
}

void EventMouseClass::setPoint2(const QPoint &value)
{
    point2 = value;
}

int EventMouseClass::widthOfRect()
{
    return (this->point2.x() - this->point1.x());
}

int EventMouseClass::heightOfRect()
{
    return (this->point2.y() - this->point1.y());
}

EventMouseClass::EventMouseClass(QWidget *parent) : QGraphicsView(parent)
{
    this->pointflag = false;

}

int EventMouseClass::sizeframe()
{
    return ABSOLUTEVALUE((this->point1.x()-this->point2.x())*(this->point1.y()-this->point2.y()));
}

void EventMouseClass::mousePressEvent(QMouseEvent *ev)
{

    if(ev->button()==Qt::LeftButton){
        this->point1 = mapToScene(ev->pos()).toPoint();
        this->point2 = mapToScene(ev->pos()).toPoint();
        emit Mouse_Pressed();
        this->pointflag = true;
        qDebug() <<"position x: "<< QString::number(this->point1.x());
    }

}

void EventMouseClass::mouseMoveEvent(QMouseEvent *ev)
{
    if(this->pointflag ==true){
        this->point2 = mapToScene(ev->pos()).toPoint();
        emit Mouse_Move();
    }
}

void EventMouseClass::mouseReleaseEvent(QMouseEvent *ev)
{
    //this->point2 = mapToScene(ev->pos()).toPoint();
    this->pointflag = false;
    //qDebug() << "\n\nX1: "<<this->point1.x()<< "\nY1: " << this->point1.y() << "\nX2" << this->point2.x() << "\nY2: " << this->point2.y();
    emit Mouse_Released();

}
