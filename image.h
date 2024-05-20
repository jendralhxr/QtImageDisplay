#ifndef IMAGE_H
#define IMAGE_H

#include <opencv4/opencv2/opencv.hpp> // if using opencv4
#include <QObject>
#include <QWidget>
#include <QLabel>

#define SCALING_INCREMENT .1

using namespace cv;

class image : public QLabel
{
    Q_OBJECT
public:
    explicit image(QWidget *parent = nullptr);
    image(char* filename);

signals:
    void pixelPosition(QString pos);
    void pixelValue(QString val);
    void imageRescale(int width, int height);
    void imageZoom(QString zoom);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void keyPressEvent(QKeyEvent *ev) override;

public slots:
    void updateRender();

private:
    int imageWidth, imageHeight;
    int displayWidth, displayHeight;
    double zoomscale= 1;
    cv::Mat render, source;
};

#endif // IMAGE_H
