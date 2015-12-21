#include "spritepicker.h"

SpritePicker::SpritePicker(QWidget *parent) : QGraphicsView(parent)
{
//    setMinimumWidth(185);

    filename = "";

    button_load = new QPushButton("Load a spritesheet...",this);
    connect(button_load,SIGNAL(clicked(bool)),this,SLOT(loadSpriteSheet()));

    scene = new QGraphicsScene(this);
    setScene(scene);

    image = NULL;
}


void SpritePicker::reset()
{
    if(image != NULL)
        delete image;

    scene->clear();

    button_load->show();
}


void SpritePicker::loadSpriteSheet()
{
    QString old_filename = filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Package"), "", tr("Image File (*.png *.jpg *.jpeg *tga *bmp)"));
    if(filename.size() <= 0)
    {
        filename = old_filename;
        return;
    }

    if(image != NULL)
        delete image;

    image = new QImage(filename);

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*image));

    button_load->hide();

    spriteSheetLoaded(); // Envoi signal au parent
}
