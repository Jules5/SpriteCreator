#include "spritecreator.h"

SpriteCreator::SpriteCreator(QWidget *parent) :
    QWidget(parent)
{
    // Menu bar
    initMenuBar();

    // Layouts
    initLayouts();

    // Widgets
    initWidgets();

    // Window attributes & properties
    filename = "";
    showMaximized();

    // Connections
    connect(sprite_picker,SIGNAL(spriteSheetLoaded()),this,SLOT(spriteSheetLoaded()));

    // Debug
//    spriteSheetLoaded();
}



void SpriteCreator::initMenuBar()
{
    menubar = new QMenuBar(this);

    QMenu* menu;
    QAction* action;

    // File
    menu = new QMenu(tr("File"),menubar);

    action = new QAction(tr("New package..."),menu);
    menu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(newPackage()));

    action = new QAction(tr("Open package..."),menu);
    menu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(openPackage()));

    menu->addSeparator();

    action_save = new QAction(tr("Save"),menu);
    action_save->setDisabled(true);
    menu->addAction(action_save);
    connect(action_save,SIGNAL(triggered()),this,SLOT(save()));

    action_save_as = new QAction(tr("Save as..."),menu);
    action_save_as->setDisabled(true);
    menu->addAction(action_save_as);
    connect(action_save_as,SIGNAL(triggered()),this,SLOT(saveAs()));

    menu->addSeparator();

    action = new QAction(tr("Quit"),menu);
    menu->addAction(action);
    connect(action,SIGNAL(triggered()),qApp,SLOT(quit()));

    menubar->addMenu(menu);

    menubar->setMaximumHeight(20);
    menubar->show();
}



void SpriteCreator::initLayouts()
{
    main_layout  = new QHBoxLayout();
    left_layout  = new QVBoxLayout();
    right_layout = new QVBoxLayout();

    main_layout->addLayout(left_layout);
    main_layout->addLayout(right_layout);

    main_layout->setContentsMargins(5,24,5,5);

    this->setLayout(main_layout);
}



void SpriteCreator::initWidgets()
{
    // Animations explorer
    anim_explorer = new AnimationsExplorer(this);
    anim_explorer->setDisabled(true);
    anim_explorer->setMaximumWidth(200);
    left_layout->addWidget(anim_explorer);

    // Animation parametrer
    anim_param = new AnimationParameters(this);
    anim_param->setDisabled(true);
    anim_param->setMaximumWidth(200);
    left_layout->addWidget(anim_param);

    // Animation Player
    anim_player = new AnimationPlayer(this);
    anim_player->setDisabled(true);
    anim_player->setFixedWidth(200);
    anim_player->setFixedHeight(220);
    left_layout->addWidget(anim_player);

    // Sprite Picker
    sprite_picker = new SpritePicker(this);
    right_layout->addWidget(sprite_picker);

    // Frames Explorer
    frames_explorer = new FramesExplorer(this);
    frames_explorer->setDisabled(true);
    right_layout->addWidget(frames_explorer);
}


bool SpriteCreator::savePackage()
{
    return false;
}



void SpriteCreator::newPackage()
{
    int rep = QMessageBox::question(this, tr("New package"), tr("Do you want to save your work before create a new package ?")
                                    ,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    switch(rep)
    {
        case QMessageBox::Yes :
            if(!savePackage())
                return;
            break;

        case QMessageBox::Cancel :
            return;
    }

    sprite_picker->reset();
    anim_explorer->reset();
    anim_player->reset();
    frames_explorer->reset();

    anim_explorer->setEnabled(false);
    anim_param->setEnabled(false);
    anim_param->clearForm();
    anim_player->setEnabled(false);
    frames_explorer->setEnabled(false);
}



void SpriteCreator::spriteSheetLoaded()
{
    anim_explorer->setEnabled(true);
    anim_param->setEnabled(true);
    anim_player->setEnabled(true);
    frames_explorer->setEnabled(true);

    action_save->setEnabled(true);
    action_save_as->setEnabled(true);
}
