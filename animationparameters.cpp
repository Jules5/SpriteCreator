#include "animationparameters.h"

AnimationParameters::AnimationParameters(QWidget *parent) : QWidget(parent)
{
    animation = NULL;

    // Inputs
    name = new QLineEdit();
    speed = new QSpinBox();
    is_repeated = new QCheckBox();

    // Formulaire
    form = new QFormLayout(this);
    form->addRow(tr("Name"),name);
    form->addRow(tr("Speed"),speed);
    form->addRow(tr("Repeated"),is_repeated);
    setLayout(form);

    // Connexions
    connect(name,SIGNAL(editingFinished()),this,SLOT(updateAnimation()));
    connect(speed,SIGNAL(editingFinished()),this,SLOT(updateAnimation()));
    connect(is_repeated,SIGNAL(toggled(bool)),this,SLOT(updateAnimation()));
}





void AnimationParameters::update()
{
    if(animation == NULL)
    {
        reset();
        return;
    }

    name->setText(animation->name);
    speed->setValue(animation->speed);
    is_repeated->setChecked(animation->repeated);
}


void AnimationParameters::reset()
{
    animation = NULL;
    name->clear();
    speed->clear();
    is_repeated->setChecked(false);
}


void AnimationParameters::setAnimation(Animation* a)
{
    animation = a;
}



void AnimationParameters::updateAnimation()
{
    if(animation == NULL)
        return;

    animation->name = name->text();
    animation->speed = speed->value();
    animation->repeated = is_repeated->isChecked();

    emit animationUpdated();
}
