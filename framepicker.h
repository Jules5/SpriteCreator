#ifndef SPRITEPICKER_H
#define SPRITEPICKER_H

#include <QString>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QScrollBar>

#include <iostream>

using namespace std;

class FramePicker : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FramePicker(QWidget *parent);

    void reset();
    void update();
    void loadImage(const QString&);

private:
    QString filename;
    QPushButton* button_load;
    QGraphicsScene* scene;
    QPixmap image;

    int x,y,w,h;
    bool is_selecting;
    QRect getSelection();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


signals:
    void spriteSheetLoaded();

public slots:
    void loadSpriteSheet();
    void sceneResized();

};

#endif // SPRITEPICKER_H
