#include "imagedisplay.h"
#include <QMouseEvent>
#include <QWheelEvent>


imagedisplay::imagedisplay(QWidget *parent) : QLabel(parent){
setMouseTracking(true);
}

imagedisplay::imagedisplay(char* filename){
    setMouseTracking(true);
    image= imread(filename, CV_LOAD_IMAGE_COLOR);
    updateRender();
}

void imagedisplay::mouseMoveEvent(QMouseEvent *ev){
    //qDebug("move %d %d from %d %d", ev->x(), ev->y(), ev->globalX(), ev->globalY());
    int x= ev->x() * zoomscale;
    int y= ev->y() * zoomscale;
    emit(pixelPosition(QString::asprintf("x,y: %d %d",x, y )));
    emit(pixelValue(QString::asprintf("RGB: %d %d %d",\
        image.data[(image.cols*y+x)*image.channels()], \
        image.data[(image.cols*y+x)*image.channels() +1], \
        image.data[(image.cols*y+x)*image.channels() +2] )));
}

void imagedisplay::mousePressEvent(QMouseEvent *ev){
    qDebug("pressed %d %d: %d", ev->x(), ev->y(), ev->button());
    switch(ev->button()){
    case 1:
        rotate(image, image, ROTATE_90_CLOCKWISE);
        break;
    case 2:
        rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);
        break;
    default: break;
    }
    updateRender();
}

void imagedisplay::wheelEvent(QWheelEvent *ev){
    if (ev->delta()==120) zoomscale += SCALING_INCREMENT;
    else if (ev->delta()==-120) zoomscale -= SCALING_INCREMENT;
    //qDebug("scroll %d %d %f", ev->buttons(), ev->delta(), zoomscale);
    cv::resize(image, image, cv::Size(0,0), zoomscale, zoomscale, CV_INTER_LINEAR);
    updateRender();
}

void imagedisplay::updateRender(){
    setPixmap(QPixmap::fromImage(QImage(static_cast<unsigned char*>(image.data), \
        image.cols, image.rows, 3*image.cols, QImage::Format_RGB888).rgbSwapped()));
    update();
}

