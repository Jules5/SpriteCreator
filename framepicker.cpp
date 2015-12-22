#include "framepicker.h"

FramePicker::FramePicker(QWidget *parent) : QGraphicsView(parent)
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    filename = "";
    is_selecting = false;

    button_load = new QPushButton("Load a spritesheet...",this);
    connect(button_load,SIGNAL(clicked(bool)),this,SLOT(loadSpriteSheet()));

    scene = new QGraphicsScene(this);
    setScene(scene);

    connect(scene,SIGNAL(changed(QList<QRectF>)),this,SLOT(sceneResized()));

    update();
}


void FramePicker::reset()
{
    filename = "";
    scene->clear();
    button_load->show();
}


void FramePicker::update()
{
    scene->clear();
    scene->addPixmap(image);

    if(is_selecting)
        scene->addRect(getSelection());
}


void FramePicker::loadSpriteSheet()
{
    QString old_filename = filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Package"), "", tr("Image File (*.png *.jpg *.jpeg *tga *bmp)"));
    if(filename.size() <= 0)
    {
        filename = old_filename;
        return;
    }

    image = QPixmap::fromImage(QImage(filename));

    scene->clear();
    scene->addPixmap(image);

    button_load->hide();

    spriteSheetLoaded(); // Envoi signal au parent
}



void FramePicker::sceneResized()
{
    QRectF rect = scene->itemsBoundingRect();
    scene->setSceneRect(rect);
}


QRect FramePicker::getSelection()
{
    QRect tmp(x,y,w,h);

    if(w < 0)
    {
        tmp.setX(x+w);
        tmp.setWidth(-w);
    }

    if(h < 0)
    {
        tmp.setY(y+h);
        tmp.setHeight(-h);
    }

    return tmp;
}



void FramePicker::mousePressEvent(QMouseEvent *event)
{
    if(filename != "" && event->button() == Qt::LeftButton)
    {
        is_selecting =true;
        x = event->pos().x()+horizontalScrollBar()->value();
        y = event->pos().y()+verticalScrollBar()->value();
        w = h = 0;
        update();
    }
}



void FramePicker::mouseMoveEvent(QMouseEvent *event)
{
    if(is_selecting)
    {
        int dx = (event->x()+horizontalScrollBar()->value()) - x;
        int dy = (event->y()+verticalScrollBar()->value()) - y;

//        if(dx < 0)
//        {
//            selection.setX(selection.x()+dx);
//            dx = -dx;
//        }

//        if(dy < 0)
//        {
//            selection.setY(selection.y()+dy);
//            dy = -dy;
//        }

        w = dx;
        h = dy;

        update();
    }
}


void FramePicker::mouseReleaseEvent(QMouseEvent *event)
{
    if(is_selecting && event->button() == Qt::LeftButton)
    {
        is_selecting = false;
        x = y = w = h = 0;
        update();
    }
}
