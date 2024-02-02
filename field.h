#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <vector>
#include "dfs.h"
#include "cell.h"

using std::vector;

class Field : public QGraphicsView //создает поле из клеток (методы generate и genrateBarrier)
{
    Q_OBJECT
public:
    explicit Field(int w, int h, QWidget *parent = nullptr);
    void generate();
    void genrateBarrier();
    void dfsSolve();              //функция запуска поиска в глубину
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);

private:
    int weight, height;
    bool start;
    bool finish;

    vector<vector<Cell*>> maze;
    QGraphicsRectItem *dfsR;
    Cell *startCell;
    Cell *finishCell;
    DFS *dfs;
    //SolverDFS *dfs;
};

#endif // FIELD_H
