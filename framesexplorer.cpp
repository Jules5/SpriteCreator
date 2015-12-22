#include "framesexplorer.h"

FramesExplorer::FramesExplorer(QWidget *parent) : QListWidget(parent)
{
    setFixedHeight(130);

    setViewMode(QListView::IconMode);
    setIconSize(QSize(100,100));

//    QListWidgetItem* item = new QListWidgetItem("Frame 1");
//    item->setIcon(QIcon(QDir::homePath() + "/Images/creeper.jpg"));
//    addItem(item);

//    item = new QListWidgetItem("Frame 2");
//    item->setIcon(QIcon(QDir::homePath() + "/Images/creeper.jpg"));
//    addItem(item);

}




void FramesExplorer::reset()
{

}
