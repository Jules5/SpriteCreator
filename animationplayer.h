#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <QGraphicsView>
#include <QDir>

class AnimationPlayer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AnimationPlayer(QWidget *parent = 0);

    void reset();

private:
    QGraphicsScene* scene;

signals:

public slots:
};

#endif // ANIMATIONPLAYER_H
