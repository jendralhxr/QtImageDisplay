#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <image.h>
#include <display.h>

#define BARWIDTH 200
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    image picture(argv[1]);

    QLineEdit linePosition;
    linePosition.setReadOnly(true);
    linePosition.setMinimumWidth(BARWIDTH);
    QLineEdit lineRGB;
    lineRGB.setReadOnly(true);
    lineRGB.setMinimumWidth(BARWIDTH);
    QLineEdit lineZoom("1.00");
    lineZoom.setReadOnly(true);

    display disp;
    QVBoxLayout layout;
    disp.setLayout(&layout);

    layout.addWidget(&linePosition, 0, Qt::AlignLeft);
    layout.addWidget(&lineRGB, 0, Qt::AlignLeft);
    layout.addWidget(&picture, 0, Qt::AlignCenter);
    layout.addWidget(&lineZoom, 0, Qt::AlignLeft);
    layout.setSizeConstraint(QLayout::SetFixedSize);

    disp.show();

    QObject::connect(&picture, SIGNAL(pixelPosition(QString)), \
                     &linePosition, SLOT(setText(QString)));
    QObject::connect(&picture, SIGNAL(pixelValue(QString)), \
                     &lineRGB, SLOT(setText(QString)));
    QObject::connect(&picture, SIGNAL(imageZoom(QString)), \
                     &lineZoom, SLOT(setText(QString)));


    return a.exec();
}
