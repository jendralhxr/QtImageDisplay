#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <imagedisplay.h>
#include <QString>

#define BARWIDTH 200
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imagedisplay picture(argv[1]);

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

    QObject::connect(&picture, SIGNAL(pixelPosition(QString)), \
                     &linePosition, SLOT(setText(QString)));
    QObject::connect(&picture, SIGNAL(pixelValue(QString)), \
                     &lineRGB, SLOT(setText(QString)));
    display.show();

    return a.exec();
}
