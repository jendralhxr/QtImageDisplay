#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>


class imagedisplay : public QLabel
{
    Q_OBJECT
public:
    explicit imagedisplay(QWidget *parent = nullptr);
    imagedisplay(QString filename);

signals:
    void pixelPosition(QString pos);
    void pixelValue(QString val);
    void imageRescale(int width, int height);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;

public slots:
    void rescale(int width, int height);

private:
    int imageWidth, imageHeight;
    int displayWidth, displayHeight;

};

#endif // IMAGEDISPLAY_H
