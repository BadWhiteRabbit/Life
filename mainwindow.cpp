#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPalette pall;
    pall.setColor(this->backgroundRole(), Qt::white);

    this->setPalette(pall);
    this->move      (300, 0);
    this->resize    (1400, 700);

    buttonStart =           new QPushButton("Start", this);
    buttonAntibiotic =      new QPushButton("Antibiotic", this);

    buttonStart->resize     (buttonAntibiotic->width(), buttonAntibiotic->height());
    buttonStart->move       (this->width() - buttonStart->width()
                            ,this->height() - buttonStart->height());
    buttonAntibiotic->move  (this->width() - buttonStart->width() - buttonAntibiotic->width() - 1
                            ,this->height() - buttonAntibiotic->height());

    QString set_style("QLabel { color : black; font-size : 20px; padding: 5px; }");
    QLabel* statistic_text;

    statistic_int = new QLabel(this);
    statistic_text = new QLabel(this);

    statistic_text->setText("Живых молекул: ");
    statistic_int->setNum(0);

    statistic_int->setStyleSheet(set_style);
    statistic_text->setStyleSheet(set_style);

    statistic_text->resize(200, statistic_int->height() + 10);
    statistic_int->move(this->width() - statistic_int->width() * 2 , statistic_text->height() + 5);
    statistic_text->move(this->width() - statistic_int->width() * 4, statistic_text->height());

    life = new Lifestream(10);

     connect(life, SIGNAL(sendCoordForDraw(int,int,int)), this, SLOT(createMolecule(int,int,int)));
     connect(buttonStart, SIGNAL(clicked()), life, SLOT(start()));
     connect(life, &Lifestream::updateStats, this, &MainWindow::updateRec);
     connect(life, &Lifestream::sendStatistic, this, &MainWindow::updateStatistic);
     connect(buttonAntibiotic, SIGNAL(clicked()), life, SLOT(applyAntibiotic()));
     connect(life, &Lifestream::microorganismIdDied, this, &MainWindow::moleculeWasDiedAnibiotik);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent     (QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen{Qt::blue, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
    for(const auto& i : map_rectengules){
        //qDebug() << "I = " << i;
        painter.drawRect(i);
    }
    painter.end();
   // qDebug() << "Paint Event size vector = " << rectengules.size();
}
void MainWindow::createMolecule (int id,int qsX, int qsY)
{
    m_mutex.lock();

    nextCoordsX += (qsX + 10);

    if(nextCoordsX >= (qsX + 10) * 20){
        nextCoordsX = qsX + 10;
        nextCoordsY += (qsY + 60);
        ++nextLine;
    }
    auto r2 = QRect{QPoint(nextCoordsX,nextCoordsY), QSize(qsY,qsX)};
    map_rectengules.insert(id, r2);
    //qDebug() << "nextCoordsY = " << nextCoordsY;
    //qDebug() << "createMolecule, vector size = " << rectengules.size();
    update();

    m_mutex.unlock();
}

void MainWindow::updateRec(int id, int qsX, int qsY){
    m_mutex.lock();
  //  qDebug() << "ACCEPT SIGNAL" << qsX << "qsY = " << qsY;
    if(qsY > 0)
    {
        map_rectengules[id].setSize({qsY,qsX});
        update();
        if(qsX <= 0){
            qDebug() << "Molecule ID =" << id << "WAS DIED!";
            map_rectengules.remove(id);
        }
    }
    m_mutex.unlock();
}

void MainWindow::moleculeWasDiedAnibiotik(int id){
    m_mutex.lock();
    qDebug() << "Molecule ID =" << id << "APPLY ANTIBIOTIK!";
    map_rectengules.remove(id);
    //qDebug() << "SIZE MAP IMAGE" << map_rectengules.size();
    update();
    m_mutex.unlock();
}

void MainWindow::updateStatistic(int molecul){
    statistic_int->setNum(molecul);
}


