#ifndef SPRITEPICKER_H
#define SPRITEPICKER_H

#include <QString>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPushButton>

class SpritePicker : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SpritePicker(QWidget *parent);

    void reset();
    void loadImage(const QString&);

private:
    QString filename;
    QPushButton* button_load;
    QGraphicsScene* scene;
    QImage* image;


signals:
    void spriteSheetLoaded();

public slots:
    void loadSpriteSheet();

};

#endif // SPRITEPICKER_H
