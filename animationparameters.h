#ifndef ANIMATIONPARAMETRER_H
#define ANIMATIONPARAMETRER_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>

class AnimationParameters : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationParameters(QWidget *parent = 0);

    void clearForm();

private:
    QFormLayout* form;

    QLineEdit* name;
    QSpinBox* speed;
    QCheckBox* is_repeated;

signals:

public slots:
};

#endif // ANIMATIONPARAMETRER_H
