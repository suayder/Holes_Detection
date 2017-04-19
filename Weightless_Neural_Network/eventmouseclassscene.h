#ifndef EVENTMOUSECLASSSCENE_H
#define EVENTMOUSECLASSSCENE_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QObject>
#include <QGraphicsLineItem>

#define ABSOLUTEVALUE(a)a<0?a*(-1):a

/*
class Scene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine};
    Scene(QObject* parent = 0);
    void setMode(Mode mode);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    void makeItemsControllable(bool areControllable);
};


/***************************************************************************************/

class EventMouseClassScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QPoint point1, point2;
    bool pointflag;
    QGraphicsRectItem *itemRect;


public:
    explicit EventMouseClassScene(QWidget *parent = Q_NULLPTR);
    int sizeframe();
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    //void paintEvent(QPaintEvent *ev);


    QPoint getPoint1() const;

    QPoint getPoint2() const;

signals:
    void Mouse_Pressed();
    void Mouse_Move();
    void Mouse_Released();
    //void paint_event();

public slots:

};

#endif // EVENTMOUSECLASSSCENE_H
