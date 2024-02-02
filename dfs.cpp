#include "dfs.h"

const int cellSize = 50;

DFS::DFS(int startX, int startY, int finishX, int finishY, vector<vector<Cell*>> maze,QGraphicsRectItem *bp, QGraphicsScene *sc)
    :start_x{startX},start_y{startY}, finish_x{finishX}, finish_y{finishY}, maze_m{maze}, bigParent{bp}, scene{sc}
{


}
void DFS::setFinishX(int x){
    finish_x = x;
}
void DFS::setFinishY(int y){
    finish_y = y;
}
stack<Cell*> DFS::getPath() const{
    return path;
}
void DFS::updateCell()
{
    path.top()->setR(new QGraphicsRectItem(cellSize * path.top()->getX() + 15, cellSize * path.top()->getY()+ 15, 20, 20, bigParent));
    path.top()->getRect()->setBrush(QColor(Qt::green));
    path.top()->getRect()->setPen(Qt::NoPen);
    QApplication::processEvents();
}
void DFS::solve(){

    int currentX = start_x;
    int currentY = start_y;
    path.push(maze_m.at(currentY).at(currentX));

    maze_m.at(currentY).at(currentX)->setVisit(false);
    operations = 1;

   // qDebug() << start_x << " " << start_y << "\n";

    while (maze_m.at(currentY).at(currentX)->getStatus() != Finish)
    {
        operations++;
        if (currentX + 1 <= maze_m.at(0).size() - 1
            && maze_m.at(currentY).at(currentX + 1)->getStatus() != NoClean
            && maze_m.at(currentY).at(currentX + 1)->getStatus() != Start
            && maze_m.at(currentY).at(currentX + 1)->getVisit() == false)
        {

            currentX++;

            path.push(maze_m.at(currentY).at(currentX));
            maze_m.at(currentY).at(currentX)->setVisit(true);

            updateCell();

        }
        else if (currentY - 1 >= 0
                   && maze_m.at(currentY - 1).at(currentX)->getStatus() != NoClean
                   && maze_m.at(currentY - 1).at(currentX)->getStatus() != Start
                   && maze_m.at(currentY - 1).at(currentX)->getVisit() == false)
        {
            currentY--;

            path.push(maze_m.at(currentY).at(currentX));
            maze_m.at(currentY).at(currentX)->setVisit(true);

            updateCell();
        }
        else if (currentY + 1 <= maze_m.size()-1
                   && maze_m.at(currentY+1).at(currentX)->getStatus()!= NoClean
                   && maze_m.at(currentY+1).at(currentX)->getStatus()!= Start
                   && maze_m.at(currentY + 1).at(currentX)->getVisit() == false)
        {
            currentY++;

            path.push(maze_m.at(currentY).at(currentX));
            maze_m.at(currentY).at(currentX)->setVisit(true);

            updateCell();
        }
        else if (currentX - 1 >= 0
                   && maze_m.at(currentY).at(currentX - 1)->getStatus() != NoClean
                   && maze_m.at(currentY).at(currentX - 1)->getStatus() != Start
                   && maze_m.at(currentY).at(currentX - 1)->getVisit() == false)
        {
            currentX--;

            path.push(maze_m.at(currentY).at(currentX));
            maze_m.at(currentY).at(currentX)->setVisit(true);

            updateCell();
        }
        else if(maze_m.at(currentY).at(currentX)->getStatus() != Start)
        {
            scene->removeItem(path.top()->getRect());

            QGraphicsRectItem *rr = new QGraphicsRectItem(cellSize * path.top()->getX() + 20, cellSize * path.top()->getY()+ 20, 20, 20, bigParent);
            rr->setBrush(QColor(Qt::black));  // перекрашивает клетки в черный при перемещении назад
            rr->setPen(Qt::NoPen);
           // scene->addItem(rr);


            path.pop();
            currentX = path.top()->getX();
            currentY = path.top()->getY();
            QApplication::processEvents();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("No way..");
            msgBox.exec();
            break;
        }
    }
 //   qDebug() << finish_x << " " << finish_y << "\n";
}


// QGraphicsLineItem *line = new QGraphicsLineItem(cellSize * (path.top())->getX() + 20,
//                                                 cellSize * (path.top())->getY() + 20,
//                                                 cellSize * (path.top()-1)->getX() + 20,
//                                                 cellSize * (path.top()-1)->getY() + 20, bigParent);
// line->setPen(QPen(QColor(Qt::green), 5, Qt::SolidLine));

// scene->addItem(line);

// new QGraphicsLineItem(20 * path.at(path.size() - 1)->getX() + 10, 20 * path.at(path.size() - 1)->getY() + 10,
//                     20 * path.at(path.size() - 2)->getX() + 10, 20 * path.at(path.size() - 2)->getY() + 10, parL);

