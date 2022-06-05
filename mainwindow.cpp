#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QList>
#include "rect.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Rect *r = nullptr; Rect *q = nullptr; Rect *i = nullptr;
    if (event->modifiers() & Qt::ControlModifier && num==0)
    {
        x = event->x(); y = event->y();
        qDebug("%d, %d", x, y);
        num = 1;
    }
    else if (event->modifiers() & Qt::ControlModifier && num==1)
    {
        if (x!=event->x() && y!=event->y()) {
            if (x < event->x() && y < event->y()) r = new Rect(x, y, event->x(), event->y(), 0);
            else if (x < event->x() && y > event->y()) r = new Rect(x, event->y(), event->x(), y, 0);
            else if (x > event->x() && y < event->y()) r = new Rect(event->x(), y, x, event->y(), 0);
            else r = new Rect(event->x(), event->y(), x, y, 0); }
        else qDebug("Такого прямоугольника не существует");
        qDebug("%d, %d, %d, %d", r->getX1(), r->getY1(), r->getX2(), r->getY2());
        num = 0;
    }
    else {
        int kmax = 0;
        for (Rect *r : rs)
            if (r && r->contains(event->x(), event->y())) {
                q = r;
                kmax++;
                qs.append(q);
            }
        qDebug("%d", kmax);
        QRect ok = contentsRect();
        int cnt = 0, xp, yp, lrb = 0;
        for (int x = 0; x<ok.width() ; x++)
            for (int y = 0 ; y<ok.height() ; y++){
                cnt = 0;
                for (Rect *q : qs) {
                    if (cnt!=kmax && q->contains(x, y)) cnt++;
                    if (!lrb && cnt==kmax) {
                        xp = x-1;
                        yp = y-1;
                        lrb = 1;
                    } } }
        for (int x = ok.width(); x>-1; x--)
            for (int y = ok.height(); y>-1; y--) {
                cnt = 0;
                for (Rect *q : qs) {
                    if (cnt != kmax && q->contains(x, y)) cnt++;
                    if (lrb && cnt==kmax) {
                        if (xp < x+1 && yp < y+1) i = new Rect(xp, yp, x+1, y+1, kmax);
                        else if (xp < x+1 && yp > y+1) i = new Rect(xp, y+1, x+1, yp, kmax);
                        else if (xp > x+1 && yp < y+1) i = new Rect(x+1, yp, xp, y+1, kmax);
                        else i = new Rect(x+1, y+1, xp, yp, kmax);
                        lrb = 0;
                    } } }
       // if (i)
       //     for (Rect *q : qs)
      //          if (q)
     //               qs.clear();
    }
    if (r)
        rs.append(r);
    if (i){
        is.append(i);
        qs.clear();
    }
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (Rect *r : rs)
        if (r)
            r->draw(&painter);
    for (Rect *i: is)
        if (i)
            i->draw(&painter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
