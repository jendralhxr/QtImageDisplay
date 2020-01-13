#include "imagedisplay.h"
#include <QMouseEvent>
#include <QWheelEvent>

imagedisplay::imagedisplay(QWidget *parent) : QLabel(parent){
setMouseTracking(true);
}

imagedisplay::imagedisplay(QString filename){
}

void imagedisplay::mouseMoveEvent(QMouseEvent *ev){
    qDebug("move %d %d from %d %d", ev->x(), ev->y(), ev->globalX(), ev->globalY());
}

void imagedisplay::mousePressEvent(QMouseEvent *ev){
    qDebug("pressed %d %d: %d", ev->x(), ev->y(), ev->button());

}

void imagedisplay::wheelEvent(QWheelEvent *ev){
    qDebug("scroll %d %d", ev->buttons(), ev->delta());
//    if (ev->delta()>0 ) emit
}

void imagedisplay::rescale(int width, int height){

}
