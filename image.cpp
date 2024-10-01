#include "image.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>

image::image(QWidget *parent) : QLabel(parent){
}

image::image(char* filename){
    setFocusPolicy(Qt::StrongFocus);

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setMouseTracking(true);
    source= imread(filename, IMREAD_ANYCOLOR); // opencv4
    int numChannels = source.channels();
    qDebug() << numChannels;
    if (numChannels==1){
        source= imread(filename, IMREAD_GRAYSCALE); // opencv4
        cvtColor(source, render, COLOR_GRAY2RGB);
        cvtColor(source, source, COLOR_GRAY2RGB);
    }
    else {
        source= imread(filename, IMREAD_COLOR); // opencv4
        render= source.clone();
    }
    updateRender();
}

void image::mouseMoveEvent(QMouseEvent *ev){
    double x, y;
    x= ev->x();
    y= ev->y();
    //qDebug("%f %f %f %f", x, y, y/zoomscale, y/zoomscale);
    emit(pixelPosition(QString::asprintf("x,y: %d %d", int(x/zoomscale), int(y/zoomscale) )));
    emit(pixelValue(QString::asprintf("RGB: %d %d %d",\
        render.data[(render.cols*int(y)+int(x))*render.channels() +2], \
        render.data[(render.cols*int(y)+int(x))*render.channels() +1], \
        render.data[(render.cols*int(y)+int(x))*render.channels()] )));
}

void image::mousePressEvent(QMouseEvent *ev){
    switch(ev->button()){
        case 1: zoomscale += SCALING_INCREMENT; break;
        case 2: zoomscale -= SCALING_INCREMENT; break;
        default: break;
    }
    emit(imageZoom(QString::asprintf("%.2f",zoomscale)));
    //qDebug("%.2f",zoomscale);
    cv::resize(source, render, cv::Size(0,0), zoomscale, zoomscale, INTER_AREA); // opencv4
    updateRender();
}

void image::wheelEvent(QWheelEvent *ev){
    if (ev->angleDelta().y()==120) rotate(render, render, ROTATE_90_CLOCKWISE);
    else if (ev->angleDelta().y()==-120) rotate(render, render, ROTATE_90_COUNTERCLOCKWISE);
    updateRender();
}

void image::keyPressEvent(QKeyEvent *ev){
    //qDebug("%d",ev->key());
    switch(ev->key()){
        case Qt::Key_9: zoomscale += SCALING_INCREMENT; break;
        case Qt::Key_0: zoomscale -= SCALING_INCREMENT; break;
        default: break;
    }
    emit(imageZoom(QString::asprintf("zoom: %.2fx",zoomscale)));
    cv::resize(source, render, cv::Size(0,0), zoomscale, zoomscale, INTER_AREA); // opencv4
    updateRender();
}

void image::updateRender(){
  setPixmap(QPixmap::fromImage(QImage(static_cast<unsigned char*>(render.data), \
        render.cols, render.rows, 3*render.cols, QImage::Format_RGB888).rgbSwapped()));
  resize(render.cols, render.rows);
  setFrameRect(QRect(0,0,0,0));
  update();
 // updateGeometry();
}
