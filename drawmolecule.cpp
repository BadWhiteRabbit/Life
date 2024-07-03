#include "drawmolecule.h"

//DrawMolecule::DrawMolecule(QWidget *parent)
//    : QWidget{parent}
//{

//}



void DrawMolecule::paintEvent(QPaintEvent*)
{

        auto r1 = QRect{QPoint(X, Y), QSize(60, 30)};
    painter->setPen(QPen{Qt::blue, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
        painter->drawRect(r1);
    painter->end();
}
