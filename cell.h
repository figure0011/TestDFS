#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <qgraphicsscene.h>
#include <qbrush.h>


enum Status{Clean, NoClean, Start, Finish, NoStatus }; // возможные статусы клетки

class Cell: public QGraphicsRectItem         // создает клетку
{
public:
    Cell(int x, int y, int size,int st, QGraphicsItem *parent = nullptr);

    Cell(const Cell &c){
        x_m = c.x_m;
        y_m = c.y_m;
        status = c.status;
        rect = c.getRect();
        Visited = c.Visited;
    }
    void updateStatus(int upd);                       // позволяет обновить статус клетки
    void clickCell(int id);
    int getX() const;
    int getY() const;
    bool getVisit() const;
    Status getStatus() const;
    QGraphicsRectItem* getRect() const;
    void setVisit(bool vs);
    void setR(QGraphicsRectItem*r);
private:
    int x_m, y_m;
    Status status;
    QGraphicsRectItem *rect;
    bool Visited = false;
};

#endif // CELL_H
