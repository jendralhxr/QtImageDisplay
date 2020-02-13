#include "imagedisplay.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

imagedisplay::imagedisplay(QWidget *parent) : QLabel(parent){
}

imagedisplay::imagedisplay(char* filename){
    setFocusPolicy(Qt::StrongFocus);

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setMouseTracking(true);
#ifdef OPENCV3
    source= imread(filename, CV_LOAD_IMAGE_COLOR); // opencv3
#endif
#ifdef OPENCV4
    source= imread(filename, IMREAD_ANYCOLOR); // opencv4
#endif
    image = source.clone();
    updateRender();
}

void imagedisplay::mouseMoveEvent(QMouseEvent *ev){
    double x, y;
    x= ev->x() / zoomscale;
    y= ev->y() / zoomscale;
    emit(pixelPosition(QString::asprintf("x,y: %d %d", int(x), int(y) )));
    emit(pixelValue(QString::asprintf("RGB: %d %d %d",\
        image.data[(image.cols*int(y)+int(x))*image.channels()], \
        image.data[(image.cols*int(y)+int(x))*image.channels() +1], \
        image.data[(image.cols*int(y)+int(x))*image.channels() +2] )));
}

void imagedisplay::mousePressEvent(QMouseEvent *ev){
    switch(ev->button()){
    case 2: zoomscale += SCALING_INCREMENT; break;
    case 1: zoomscale -= SCALING_INCREMENT; break;
    default: break;
    }
#ifdef OPENCV3
    cv::resize(source, image, cv::Size(0,0), zoomscale, zoomscale, CV_INTER_LINEAR); // opencv3
#endif
#ifdef OPENCV4
    cv::resize(source, image, cv::Size(0,0), zoomscale, zoomscale, INTER_LINEAR); // opencv4
#endif
    updateRender();
}

void imagedisplay::wheelEvent(QWheelEvent *ev){
    if (ev->delta()==120) rotate(image, image, ROTATE_90_CLOCKWISE);
    else if (ev->delta()==-120) rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);
    updateRender();
}

void imagedisplay::updateRender(){
  setPixmap(QPixmap::fromImage(QImage(static_cast<unsigned char*>(image.data), \
        image.cols, image.rows, 3*image.cols, QImage::Format_RGB888).rgbSwapped()));
  resize(image.cols, image.rows);
  setFrameRect(QRect(0,0,0,0));
  update();
 // updateGeometry();
}
