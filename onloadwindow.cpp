#include "onloadwindow.h"

OnLoadWindow::OnLoadWindow(QWidget *parent) :
    QWidget(parent)
{
    // Window properties
    setFixedSize(400,65);

    // Buttons
    b_new = new QPushButton("Créer un sprite",this);
    b_new->move(60,20);

    b_load = new QPushButton("Charger un sprite",this);
    b_load->move(210,20);

    // Signals
    QObject::connect(b_new, SIGNAL(clicked()), this, SLOT(newFile()));
    QObject::connect(b_load, SIGNAL(clicked()), this, SLOT(loadFile()));
}


void OnLoadWindow::newFile()
{

}

void OnLoadWindow::loadFile()
{

}
