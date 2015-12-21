#ifndef ANIMATIONSEXPLORER_H
#define ANIMATIONSEXPLORER_H

#include <QListWidget>

class AnimationsExplorer : public QListWidget
{
    Q_OBJECT
public:
    explicit AnimationsExplorer(QWidget *parent = 0);

    void reset();

signals:

public slots:
};

#endif // ANIMATIONSEXPLORER_H
