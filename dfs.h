#ifndef DFS_H
#define DFS_H

#include <stack>
#include <vector>
#include <qbrush.h>
#include <QPen>
#include <qapplication.h>
//#include <QDebug>
#include <QMessageBox>
#include "cell.h"

using std::vector;
using std::stack;

class DFS : public QObject  // реализация алгоритма поиска в глубину
{
    Q_OBJECT
public:
    DFS(int startX, int startY, int finishX, int finishY, vector<vector<Cell*>> maze, QGraphicsRectItem *bp, QGraphicsScene *sc);
    void setFinishX(int x);
    void setFinishY(int y);
    void solve();           // запуск поиска пути
    void updateCell();      // помечает пройденные клетки
    stack<Cell*> getPath() const;
private:
    QGraphicsRectItem *bigParent;
    QGraphicsScene *scene;
    stack<Cell*>path;
    vector<vector<Cell*>> maze_m;
    int start_x;
    int start_y;
    int finish_x;
    int finish_y;
    int operations;
    int currentX, currentY;

};

#endif // DFS_H
