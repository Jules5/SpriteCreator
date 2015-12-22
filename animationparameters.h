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
    Animation* animation;

    explicit AnimationParameters(QWidget *parent = 0);

    void clearForm();
    void updateForm();

private:
    QFormLayout* form;

    QLineEdit* name;
    QSpinBox* speed;
    QCheckBox* is_repeated;

signals:
    void animationEdited();

public slots:
    void changeAnimationParams();

};

#endif // ANIMATIONPARAMETRER_H
