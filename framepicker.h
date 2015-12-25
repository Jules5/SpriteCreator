#ifndef SPRITEPICKER_H
#define SPRITEPICKER_H

#include <QString>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QScrollBar>

#include <iostream>
#include <vector>

#include <frame.h>

using namespace std;

class FramePicker : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FramePicker(QWidget *parent);

    void reset();
    void update();
    void loadImage(const QString&);
    void setFrames(vector<Frame>* = NULL);
    void drawFrame(Frame*);
    void duplicateFrame();
    void deleteFrame(Frame*);
    QPixmap* getPixmapReference();

private:
    QString filename;
    QPushButton* button_load;
    QGraphicsScene* scene;
    QPixmap image;

    vector<Frame>* frames;
    Frame* selected_frame;

    QBrush brush, brush_selected;
    QPen pen_selected;

    int x,y,w,h;
    int old_x, old_y;
    bool is_selecting;
    bool is_dragging;
    string dragged;
    QRect getSelection();

    bool checkClickCollision(int rx, int ry, Frame*);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);



signals:
    void spriteSheetLoaded();
    void frameUpdated();

public slots:
    void loadSpriteSheet();
    void sceneResized();

};

#endif // SPRITEPICKER_H
