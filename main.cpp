#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <imagedisplay.h>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imagedisplay picture(QString::fromLocal8Bit(argv[1]));
    picture.setText("abc");
    picture.setMinimumSize(200,200);

    QLineEdit linePosition;
    linePosition.setReadOnly(true);
    linePosition.setText("12312312");
    QLineEdit lineRGB;
    lineRGB.setReadOnly(true);
    lineRGB.setText("gogogogo");

    QWidget display;
    QGridLayout layout;
    display.setLayout(&layout);

    layout.addWidget(&linePosition, 0, 0, Qt::AlignLeft);
    layout.addWidget(&lineRGB, 0, 1, Qt::AlignRight);
    layout.addWidget(&picture, 1, 1, Qt::AlignCenter);

    display.show();


    return a.exec();
}
