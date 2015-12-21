#include "animationplayer.h"

AnimationPlayer::AnimationPlayer(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    scene->clear();
//    scene->addPixmap(QPixmap::fromImage(QImage(QDir::homePath() + "/Images/creeper.jpg")));
}


void AnimationPlayer::reset()
{
    scene->clear();
}
