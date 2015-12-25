#ifndef FRAMESEXPLORER_H
#define FRAMESEXPLORER_H

#include <QDir>
#include <QListWidget>
#include <QCoreApplication>

#include <vector>

#include <frame.h>

using namespace std;

class FramesExplorer : public QListWidget
{
    Q_OBJECT
public:
    explicit FramesExplorer(QWidget *parent = 0);

    void setFrames(vector<Frame>*);
    void setImage(QPixmap*);

    void reset();
    void update();

private:
    QPixmap* image;
    vector<Frame>* frames;

signals:

public slots:
};

#endif // FRAMESEXPLORER_H
