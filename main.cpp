#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <imagedisplay.h>
#include <QString>

#define BARWIDTH 200
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imagedisplay picture(argv[1]);
    //picture.setMinimumSize(BARWIDTH,BARWIDTH);
    //picture.setMaximumSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    QLineEdit linePosition;
    linePosition.setReadOnly(true);
    linePosition.setMinimumWidth(BARWIDTH);
    QLineEdit lineRGB;
    lineRGB.setReadOnly(true);
    lineRGB.setMinimumWidth(BARWIDTH);

    QWidget display;

    QGridLayout layout;
    display.setLayout(&layout);

    layout.addWidget(&linePosition, 0, 0, Qt::AlignLeft);
    layout.addWidget(&lineRGB, 0, 1, Qt::AlignRight);
    layout.addWidget(&picture, 1, 0, 2, Qt::AlignCenter);
    layout.setSizeConstraint(QLayout::SetFixedSize);

    //QObject::connect(cameraHead1, SIGNAL(getImage(QImage)), camimage, SLOT(receiveBitmap(QImage)));

    QObject::connect(&picture, SIGNAL(pixelPosition(QString)), \
                     &linePosition, SLOT(setText(QString)));
    QObject::connect(&picture, SIGNAL(pixelValue(QString)), \
                     &lineRGB, SLOT(setText(QString)));

    display.show();

    return a.exec();
}
