#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <QGraphicsView>
#include <QDir>
#include <QEventLoop>
#include <QElapsedTimer>

#include <vector>

#include <animation.h>
#include <frame.h>

using namespace std;

class AnimationPlayer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AnimationPlayer(QWidget *parent = 0);

    void reset();
    void setAnimation(Animation* = NULL);
    void setPixmap(QPixmap*);
    void update();
    void play();

private:
    QPixmap* image;
    QEventLoop loop;
    QElapsedTimer timer;
    QGraphicsScene* scene;
    Animation* animation;
    int current_frame;
    bool is_playing;

signals:

public slots:
};

#endif // ANIMATIONPLAYER_H
