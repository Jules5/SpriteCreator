#ifndef ANIMATIONPARAMETRER_H
#define ANIMATIONPARAMETRER_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>

#include <animation.h>

class AnimationParameters : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationParameters(QWidget *parent = 0);

    void update();
    void reset();
    void setAnimation(Animation*);

private:
    Animation* animation;

    QFormLayout* form;

    QLineEdit* name;
    QSpinBox* speed;
    QCheckBox* is_repeated;

signals:
    void animationUpdated();

public slots:
    void updateAnimation();

};

#endif // ANIMATIONPARAMETRER_H
