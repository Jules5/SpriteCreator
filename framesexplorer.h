#ifndef FRAMESEXPLORER_H
#define FRAMESEXPLORER_H

#include <QDir>
#include <QListWidget>
#include <QCoreApplication>

class FramesExplorer : public QListWidget
{
    Q_OBJECT
public:
    explicit FramesExplorer(QWidget *parent = 0);

    void reset();

signals:

public slots:
};

#endif // FRAMESEXPLORER_H
