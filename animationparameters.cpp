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
    connect(name,SIGNAL(editingFinished()),this,SLOT(changeAnimationParams()));
    connect(speed,SIGNAL(editingFinished()),this,SLOT(changeAnimationParams()));
    connect(is_repeated,SIGNAL(toggled(bool)),this,SLOT(changeAnimationParams()));
}



void AnimationParameters::clearForm()
{
    name->setText("");
    speed->setValue(0);
    is_repeated->setChecked(false);
}


void AnimationParameters::updateForm()
{
    if(animation == NULL)
        return;

    name->setText(animation->name);
    speed->setValue(animation->speed);
    is_repeated->setChecked(animation->repeated);
}



void AnimationParameters::changeAnimationParams()
{
    animation->name = name->text();
    animation->speed = speed->value();
    animation->repeated = is_repeated->isChecked();

    emit animationEdited();
}
