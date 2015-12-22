#include "animationsexplorer.h"

AnimationsExplorer::AnimationsExplorer(vector<Animation>* anims, QWidget *parent) : QListWidget(parent)
{
    setContentsMargins(10,5,10,5);

    animations = anims;

    for(vector<Animation>::iterator it=animations->begin(); it!=animations->end(); ++it)
        addItem(new QListWidgetItem(it->name));
}



void AnimationsExplorer::reset()
{
    if(count() > 0)
        clear();
}


void AnimationsExplorer::updateSelectedItem()
{
    QListWidgetItem* item = selectedItems().first();
    item->setText(animations->at(indexFromItem(item).row()).name);
}



void AnimationsExplorer::animationInserted()
{
    addItem(new QListWidgetItem(animations->back().name));
    item(count()-1)->setSelected(true);
}



int AnimationsExplorer::getSelectedIndex()
{
    if(count() <= 0)
        return 0;

    QListWidgetItem* item = selectedItems().first();
    return indexFromItem(item).row();
}
