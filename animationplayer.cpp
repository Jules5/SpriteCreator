#include "animationplayer.h"

AnimationPlayer::AnimationPlayer(QPixmap* img, QWidget *parent) : QGraphicsView(parent)
{
    animation = NULL;
    image = img;
    current_frame = 0;
    is_playing = false;

    scene = new QGraphicsScene(this);
    setScene(scene);

    scene->clear();
}




void AnimationPlayer::reset()
{
    scene->clear();
}


void AnimationPlayer::setAnimation(Animation* a)
{
    animation = a;
}



void AnimationPlayer::setPixmap(QPixmap* img)
{
    image = img;
}



void AnimationPlayer::update()
{
    if(animation->frames.size() <= 0)
        return;

    if(timer.elapsed() >= 1000/animation->speed)
    {
        current_frame++;
        if(current_frame >= (int)animation->frames.size())
            current_frame = 0;
        timer.restart();
    }

    scene->clear();
    Frame* f = &animation->frames.at(current_frame);
    scene->addPixmap(QPixmap(image->copy(f->x,f->y,f->w,f->h)));
}



void AnimationPlayer::play()
{
    is_playing = true;
    current_frame = 0;
    timer.start();

    while(is_playing)
    {
        loop.processEvents();
        update();
    }
}
