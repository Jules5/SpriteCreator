#ifndef ANIMATIONSEXPLORER_H
#define ANIMATIONSEXPLORER_H

#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

#include <vector>
#include <iostream>

#include <animation.h>

using namespace std;

class AnimationsExplorer : public QListWidget
{
    Q_OBJECT
public:
    explicit AnimationsExplorer(vector<Animation>*, QWidget *parent = 0);

    void reset();
    void updateSelectedItem();

    int getSelectedIndex();

private :
    vector<Animation>* animations;

signals:

public slots:
    void animationInserted();

};

#endif // ANIMATIONSEXPLORER_H
