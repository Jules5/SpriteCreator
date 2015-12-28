#include "framesexplorer.h"

FramesExplorer::FramesExplorer(QPixmap* img, QWidget *parent) : QListWidget(parent)
{
    setFixedHeight(130);

    setViewMode(QListView::IconMode);
    setIconSize(QSize(100,100));

    frames = NULL;
    image = img;
}



void FramesExplorer::setFrames(vector<Frame>* f)
{
    frames = f;
}


void FramesExplorer::setImage(QPixmap * img)
{
    image = img;
}



void FramesExplorer::reset()
{
    if(count() > 0)
        clear();
}



void FramesExplorer::update()
{
    clear();

    if(frames != NULL && image != NULL)
        for(vector<Frame>::iterator it=frames->begin(); it!=frames->end(); ++it)
        {
            QPixmap icon_pix = image->copy(it->x,it->y,it->w,it->h);
            QListWidgetItem* item = new QListWidgetItem(QIcon(icon_pix),"");
            addItem(item);
        }

    repaint();
}
