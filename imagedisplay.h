#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <opencv/cv.hpp>

#define SCALING_INCREMENT .1

using namespace cv;

class imagedisplay : public QLabel
{
    Q_OBJECT
public:
    explicit imagedisplay(QWidget *parent = nullptr);
    imagedisplay(char* filename);

signals:
    void pixelPosition(QString pos);
    void pixelValue(QString val);
    void imageRescale(int width, int height);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;

public slots:
    void updateRender();

private:
    int imageWidth, imageHeight;
    int displayWidth, displayHeight;
    double zoomscale= 1;
    cv::Mat image;
};

#endif // IMAGEDISPLAY_H
