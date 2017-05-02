#ifndef EVENTMOUSECLASS_H
#define EVENTMOUSECLASS_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

#define ABSOLUTEVALUE(a)a<0?a*(-1):a

class EventMouseClass : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint point1, point2;
    bool pointflag;
    QGraphicsRectItem *itemRect;
    //QPainter painterRect;

public:
    explicit EventMouseClass(QWidget *parent = 0);
    int sizeframe();
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    //void paintEvent(QPaintEvent *ev);


    QPoint getPoint1() const;

    QPoint getPoint2() const;

    void setPoint1(const QPoint &value);

    void setPoint2(const QPoint &value);

    int widthOfRect();

    int heightOfRect();

signals:
    void Mouse_Pressed();
    void Mouse_Move();
    void Mouse_Released();
    //void paint_event();

public slots:
};

#endif // EVENTMOUSECLASS_H
