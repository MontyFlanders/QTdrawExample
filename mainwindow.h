#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QToolBar>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLabel *label;
    QPixmap pixmap;
    QToolBar *sideToolBar;
    QPainter painter;  
    QPoint lastPoint;
    bool drawing = false;

    QPoint scaledPoint(const QPoint &point) const;
};

#endif // MAINWINDOW_H
