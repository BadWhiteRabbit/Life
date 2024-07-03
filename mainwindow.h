#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QMap>
#include <QTimeEdit>
#include <QLabel>

#include "lifestream.h"
#include "molecule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
     void paintEvent(QPaintEvent *) override;

signals:
     void testSendCoords(int x, int y);

public slots:
    void createMolecule             (int id, int qsX, int qsY);
    void updateRec                  (int id, int qsX, int qsY);
    void moleculeWasDiedAnibiotik   (int id);
    void updateStatistic            (int molecul);

private:
    Ui::MainWindow*     ui;
    QVector<QRect>      rectengules;
    QPushButton*        buttonStart;
    QPushButton*        buttonAntibiotic;
    QMutex              m_mutex;
    Lifestream*         life;
    QMap<int, QRect>    map_rectengules;
    QLabel*             statistic_int; // Для отображения живых молекул
    int                 nextCoordsX = 0;
    int                 nextCoordsY = 50;
    int                 nextLine = 0;
};
#endif // MAINWINDOW_H
