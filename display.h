#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>

class display : public QWidget
{
    Q_OBJECT
public:
    explicit display(QWidget *parent = nullptr);

signals:

protected:
    void keyPressEvent(QKeyEvent *ev) override;

public slots:
};

#endif // DISPLAY_H
