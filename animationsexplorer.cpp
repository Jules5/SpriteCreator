#include "animationsexplorer.h"

AnimationsExplorer::AnimationsExplorer(QWidget *parent) : QListWidget(parent)
{
    setContentsMargins(10,5,10,5);

    addItem(new QListWidgetItem("Animation 1"));
    addItem(new QListWidgetItem("Animation 2"));
    addItem(new QListWidgetItem("Animation 3"));
    addItem(new QListWidgetItem("Animation 4"));
}



void AnimationsExplorer::reset()
{

}
