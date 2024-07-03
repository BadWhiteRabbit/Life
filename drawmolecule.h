#ifndef DRAWMOLECULE_H
#define DRAWMOLECULE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>


class DrawMolecule : public QWidget
{
    Q_OBJECT
public:
    //explicit DrawMolecule(QWidget *parent = nullptr);
    DrawMolecule(QWidget *parent = nullptr, int x = 0, int y = 0)
        : QWidget{parent}
        , X(x)
        , Y(y)
    {
        painter = new QPainter(parent);
    }

protected:
    void paintEvent(QPaintEvent*) override;

signals:

private:
    QPainter* painter;

    QPaintDevice *device;
    int X;
    int Y;

};







#endif // DRAWMOLECULE_H
