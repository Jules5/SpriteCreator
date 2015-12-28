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


void AnimationsExplorer::update()
{
//    int cpt = count();

//    clear();

//    for(vector<Animation>::iterator it=animations->begin(); it!=animations->end(); ++it)
//        addItem(new QListWidgetItem(it->name));

//    // Gestion selection
//    if(cpt < count())
//            item(count()-1)->setSelected(true);
//    else if(selectedItems().count() <= 0 && count() > 0)
//        item(0)->setSelected(true);

    if(selectedItems().count() <= 0 && count() > 0)
        item(0)->setSelected(true);

    if(count() < (int)animations->size())
    {
        for(unsigned int i=count(); i<animations->size(); ++i)
            addItem(new QListWidgetItem(animations->at(i).name));
        item(count()-1)->setSelected(true);
    }
}



void AnimationsExplorer::updateSelectedItem()
{
    QListWidgetItem* item = selectedItems().at(0);
    int index = indexFromItem(item).row();
    item->setText(animations->at(index).name);
}



int AnimationsExplorer::getSelectedIndex()
{
    if(count() <= 0)
        return 0;

    QListWidgetItem* item = selectedItems().first();
    return indexFromItem(item).row();
}
