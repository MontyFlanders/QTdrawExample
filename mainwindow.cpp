#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), label(new QLabel(this)), pixmap(100, 100)
{
    ui->setupUi(this);

    // Initialize the toolbar and set it to the left side // can set one of these slots to set
    // central widget to color picker, as well as set our desired drawing obj
    sideToolBar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, sideToolBar);

    QAction *action1 = new QAction("Action 1", this);
    QAction *action2 = new QAction("Action 2", this);
    sideToolBar->addAction(action1);
    sideToolBar->addAction(action2);
    sideToolBar->setMovable(false);
    sideToolBar->setFloatable(false);

    // Initialize the pixmap and display it on the label (this allows us to "zoom" as well as switch pixmaps easier)
    pixmap.fill(Qt::blue);
    label->setPixmap(pixmap);
    label->setScaledContents(true);  
    label->resize(pixmap.size());
    label->setAlignment(Qt::AlignRight);
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// need to be able to change these methods based on the drawing tool selected
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = scaledPoint(event->pos());
        drawing = true;
        // here is the only place that painter is initialized, we should initialize like this
        // whenever in a method which will draw
        painter.begin(&pixmap);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawPoint(lastPoint);

        // update the label to display the modified pixmap
        label->setPixmap(pixmap);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPoint currentPoint = scaledPoint(event->pos());
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
        label->setPixmap(pixmap);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        painter.end();
        label->setPixmap(pixmap);
    }
}

QPoint MainWindow::scaledPoint(const QPoint &point) const
{
    QPoint labelPoint = label->mapFrom(this, point);

    float xScale = static_cast<float>(pixmap.width()) / label->width();
    float yScale = static_cast<float>(pixmap.height()) / label->height();

    int x = labelPoint.x() * xScale;
    int y = labelPoint.y() * yScale;

    return QPoint(x, y);
}
