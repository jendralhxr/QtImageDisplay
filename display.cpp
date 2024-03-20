#include "display.h"
#include <QKeyEvent>

display::display(QWidget *parent) : QWidget(parent){
    setFocusPolicy(Qt::StrongFocus);
}

void display::keyPressEvent(QKeyEvent *ev){
//    qDebug("%d",ev->key());
    if (ev->key()=='Q') exit(0);
}

