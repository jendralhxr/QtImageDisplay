#include "imagedisplay.h"
#include <QMouseEvent>
#include <QWheelEvent>


imagedisplay::imagedisplay(QWidget *parent) : QLabel(parent){
setMouseTracking(true);
}

imagedisplay::imagedisplay(char* filename){
    image= imread(filename, CV_LOAD_IMAGE_COLOR);
    setPixmap(QPixmap::fromImage(QImage(static_cast<unsigned char*>(image.data), \
       image.cols, image.rows, 3*image.cols, QImage::Format_RGB888).rgbSwapped()));
    update();
}

void imagedisplay::mouseMoveEvent(QMouseEvent *ev){
    qDebug("move %d %d from %d %d", ev->x(), ev->y(), ev->globalX(), ev->globalY());
}

void imagedisplay::mousePressEvent(QMouseEvent *ev){
    qDebug("pressed %d %d: %d", ev->x(), ev->y(), ev->button());
    int x= ev->x();
    int y= ev->y();
    emit(pixelPosition(QString::asprintf("x,y: %d %d",x, y )));
    emit(pixelValue(QString::asprintf("RGB: %d %d %d",\
        image.data[(image.cols*y+x)*image.channels()], \
        image.data[(image.cols*y+x)*image.channels() +1], \
        image.data[(image.cols*y+x)*image.channels() +2] )));
}

void imagedisplay::wheelEvent(QWheelEvent *ev){
    qDebug("scroll %d %d", ev->buttons(), ev->delta());
//    if (ev->delta()>0 ) emit
}

void imagedisplay::rescale(int width, int height){

}
