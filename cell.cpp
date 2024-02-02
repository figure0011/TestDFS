#include "cell.h"

Cell::Cell(int x, int y,int size, int st, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{

    setRect(x, y, size, size);
    updateStatus(st);

    x_m = x / 50;
    y_m = y / 50;
}
int Cell::getX() const{
    return x_m;
}
int Cell::getY() const{
    return y_m;
}
QGraphicsRectItem* Cell::getRect() const{
    return rect;
}
Status Cell::getStatus() const{
    return status;
}
bool Cell::getVisit() const{
    return Visited;
}
void Cell::setR(QGraphicsRectItem*r){
    rect = r;
}
void Cell::setVisit(bool vs){
    Visited = vs;
}
void Cell::updateStatus(int upd){
    switch (upd) {
    case 0:
        setBrush(QBrush(QColor(Qt::white)));
        status = Status::Clean;
        break;
    case 1:
        setBrush(QBrush(QColor(Qt::gray)));
        status = Status::NoClean;
        break;
    case 2:
        setBrush(QBrush(QColor(Qt::red)));
        status = Status::Start;
        break;
    case 3:
        setBrush(QBrush(QColor(Qt::blue)));
        status = Status::Finish;
        break;
    }
}
void Cell::clickCell(int id){
    if (id == 0 && status == Status::Clean){
        updateStatus(2);
    }
    else if(id == 1 && status == Status::Clean){
        updateStatus(3);
    }
}
