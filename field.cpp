#include "field.h"

const int cellSize = 50;

Field::Field(int w, int h, QWidget *parent)
    : QGraphicsView{parent}, weight{w}, height{h}
{
    QGraphicsScene *sc = new QGraphicsScene(this);
    setGeometry(0, 0, weight, height);
    sc->setSceneRect(0, 0, weight, height);
    setScene(sc);

    maze.resize((sc->height()) / cellSize);

    for(auto &i: maze)
        i.resize((sc->width()) / cellSize);
}
void Field::genrateBarrier(){

    int xi, yi;
    Cell *currCell;

    for (int i = 0; i < weight / cellSize; ++i)
    {
        xi = QRandomGenerator::global()->bounded(weight);
        yi = QRandomGenerator::global()->bounded(height);

        currCell = static_cast<Cell*>(scene()->itemAt(xi, yi, QTransform()));
        currCell->updateStatus(1);
    }
}
void Field::generate()
{

    start = false;
    finish = false;
    scene()->clear();

    for (int i = 0; i < sceneRect().height(); i += cellSize)
    {
        for (int j = 0; j < sceneRect().width(); j += cellSize)
        {
            Cell *cell = new Cell(j, i, cellSize, 0);
            maze.at(i / cellSize).at(j / cellSize) = cell;
            scene()->addItem(cell);
        }
    }
    genrateBarrier();

    if (maze.at(0).at(maze.at(0).size() - 1) == NULL)
    {

        for(auto &i: maze)
            i.resize(i.size() - 1);
    }

}
void Field::dfsSolve(){


    // if (dfsR != NULL)
    //     scene()->removeItem(dfsR);

    // delete dfsR;
    dfsR = NULL;
    dfsR = new QGraphicsRectItem(1, 1, 1, 1);
    scene()->addItem(dfsR);

    // if (dfs != NULL)
    // {
    //     delete dfs;
        
    // }
    dfs = NULL;
    dfs = new DFS(startCell->getX(),startCell->getY(), finishCell->getX(),finishCell->getY(), maze, dfsR, scene());
    dfs->solve();

    // QThread* thread = new QThread();
    // dfs = new SolverDFS(startCell->getX(),startCell->getY(), finishCell->getX(),finishCell->getY(), maze, dfsR, scene());
    // dfs->moveToThread(thread);
    //  connect(thread, &QThread::started, dfs, &SolverDFS::process);
    //
    // connect(dfs, &SolverDFS::finished, this, [](bool state){
    //     if(state)
    //         ;//std::cout << "Успех" << std::endl;
    //     else
    //         {
    //         QMessageBox msgBox;
    //         msgBox.setText("No way..");
    //         msgBox.exec();
    //     }
    // });
    //
    // connect(dfs, &SolverDFS::finished, thread, &QThread::quit);
    //
    // connect(dfs, &SolverDFS::finished, dfs, &QObject::deleteLater);
    //
    // connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    // thread->start();
}

void Field::mousePressEvent(QMouseEvent *event){
    Cell *currCell = static_cast<Cell *>(scene()->itemAt(mapFromGlobal(cursor().pos()), QTransform()));

    if(event->button() == Qt::LeftButton && start == false && finish == false && currCell->getStatus() == Clean){
        currCell->clickCell(0);
        start = true;
        startCell = currCell;
    }
    else if(event->button() == Qt::LeftButton && start == true && finish == false && currCell->getStatus() == Clean){
        currCell->clickCell(1);
        finish = true;
        finishCell = currCell;
        dfsSolve();
    }
}
void Field::wheelEvent(QWheelEvent* event) {

       this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor = 1.15;
        if(event->angleDelta().y() > 0) {

            this-> scale(scaleFactor, scaleFactor);

        } else if(event->angleDelta().y() < 0){

            this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }

 }



    // QThread* thread = QThread::create(std::bind(&DFS::solve, dfs));
    // connect(thread, &QThread::finished, dfs, &QObject::deleteLater);
    // connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    // thread->start();
