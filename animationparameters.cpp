#include "animationparameters.h"

AnimationParameters::AnimationParameters(QWidget *parent) : QWidget(parent)
{
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

}



void AnimationParameters::clearForm()
{
    name->setText("");
    speed->setValue(0);
    is_repeated->setChecked(false);
}
