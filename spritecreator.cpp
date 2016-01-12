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
    current_anim = NULL;
    showMaximized();

    // Connexions
    connect(anim_explorer,SIGNAL(itemSelectionChanged()),this,SLOT(animationSelectionUpdated()));
    connect(add_anim_button,SIGNAL(clicked(bool)),this,SLOT(addAnimation()));
    connect(anim_param,SIGNAL(animationUpdated()),this,SLOT(animationUpdated()));
    connect(frames_picker->button_load,SIGNAL(clicked(bool)),this,SLOT(loadSpriteSheet()));
    connect(frames_picker,SIGNAL(frameUpdated()),this,SLOT(frameUpdated()));
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
    connect(action,SIGNAL(triggered()),this,SLOT(loadPackage()));

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

    // Animation
    menu_anim = new QMenu(tr("Animation"),menubar);

    action = new QAction(tr("Add"),menu_anim);
    menu_anim->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(addAnimation()));

    action = new QAction(tr("Delete"),menu_anim);
    action->setShortcut(QKeySequence::Delete);
    menu_anim->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(deleteFrame()));

    menubar->addMenu(menu_anim);

    // Frame
    menu_frame = new QMenu(tr("Frame"),menubar);

    action = new QAction(tr("Duplicate"),menu_frame);
    action->setShortcut(QKeySequence("Ctrl+D"));
    menu_frame->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(duplicateFrame()));

    action = new QAction(tr("Delete"),menu_frame);
    action->setShortcut(QKeySequence::Delete);
    menu_frame->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(deleteFrame()));

    menubar->addMenu(menu_frame);

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
    anim_explorer = new AnimationsExplorer(&package.animations, this);
    anim_explorer->setDisabled(true);
    anim_explorer->setMaximumWidth(200);
    left_layout->addWidget(anim_explorer);

    // Button add animation
    add_anim_button = new QPushButton("Add animation",this);
    add_anim_button->setDisabled(true);
    left_layout->addWidget(add_anim_button);


    // Animation parametrer
    anim_param = new AnimationParameters(this);
    anim_param->setDisabled(true);
    anim_param->setMaximumWidth(200);
    left_layout->addWidget(anim_param);

    // Animation Player
    anim_player = new AnimationPlayer(&package.image,this);
    anim_player->setDisabled(true);
    anim_player->setFixedWidth(200);
    anim_player->setFixedHeight(220);
    left_layout->addWidget(anim_player);

    // Sprite Picker
    frames_picker = new FramePicker(&package.image,this);
    right_layout->addWidget(frames_picker);

    // Frames Explorer
    frames_explorer = new FramesExplorer(&package.image,this);
    frames_explorer->setDisabled(true);
    right_layout->addWidget(frames_explorer);
}



void SpriteCreator::updateAll()
{
    anim_explorer->update();

    Animation* old_current = current_anim;
    int current_index = anim_explorer->getSelectedIndex();
    if(current_index != -1)
        current_anim = &package.animations.at(current_index);

    if(current_anim != old_current)
    {
        anim_param->setAnimation(current_anim);
        anim_param->update();
    //    anim_player->update();
        frames_picker->setFrames(&current_anim->frames);
        frames_picker->update();
        frames_explorer->setFrames(&current_anim->frames);
        frames_explorer->update();
    }
}



bool SpriteCreator::newPackage()
{
    int rep = QMessageBox::question(this, tr("New package"), tr("Do you want to save your work before create a new package ?")
                                    ,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    switch(rep)
    {
        case QMessageBox::Yes :
            save();
            break;

        case QMessageBox::Cancel :
            return false;
    }

    frames_picker->reset();
    anim_explorer->reset();
    anim_param->reset();
    anim_player->reset();
    frames_explorer->clear();
    package.reset();

    package.animations.clear();
    current_anim = NULL;

    anim_explorer->setEnabled(false);
    add_anim_button->setEnabled(false);
    anim_param->setEnabled(false);
    anim_player->setEnabled(false);
    frames_explorer->setEnabled(false);

    return true;
}



void SpriteCreator::loadPackage()
{
    if((package.animations.size()>0 || !package.image.isNull()) && !newPackage())
        return;

    QString old_filename = filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Package"), "", tr("Sprite Package (*.spr)"));
    if(filename.size() <= 0)
    {
        filename = old_filename;
        return;
    }

    if(package.load(filename))
    {
        setModeEdition();
        frames_picker->update();
    }
}



void SpriteCreator::loadSpriteSheet()
{
    // Chargement de l'image
    QString image_file = QFileDialog::getOpenFileName(this, tr("Open Package"), "", tr("Image File (*.png *.jpg *.jpeg *tga *bmp)"));
    if(image_file.size() <= 0)
        return;

    package.image = QPixmap::fromImage(QImage(image_file));

    // Toggle edition mode
    setModeEdition();
}



void SpriteCreator::setModeEdition()
{
    // On active les widgets désactivés
    anim_explorer->setEnabled(true);
    add_anim_button->setEnabled(true);
    anim_param->setEnabled(true);
    anim_player->setEnabled(true);
    frames_picker->setEnabled(true);
    frames_explorer->setEnabled(true);

    action_save->setEnabled(true);
    action_save_as->setEnabled(true);

    // Si pas d'animation, on en crée une
    if(package.animations.size() <= 0)
        addAnimation();

    // Mise à jour
    updateAll();
}



bool SpriteCreator::save()
{
    if(filename == "")
        return saveAs();

    if(!package.save(filename))
    {
        QMessageBox::information(this,tr("Error"),tr("Impossible to write in the specified file."),QMessageBox::Ok);
        return false;
    }

    return true;
}


bool SpriteCreator::saveAs()
{
    filename = QFileDialog::getSaveFileName(this, tr("Save Package"), "", tr("Sprite Package (*.spr)"));

    if(filename.size() <= 0)
        return false;

    return save();
}





void SpriteCreator::addAnimation()
{
    package.animations.push_back(Animation());
    updateAll();
}


void SpriteCreator::animationUpdated()
{
    anim_explorer->updateSelectedItem();
}


void SpriteCreator::animationSelectionUpdated()
{
    updateAll();
}


void SpriteCreator::frameUpdated()
{
    frames_picker->update();
    frames_explorer->update();
}


void SpriteCreator::duplicateFrame()
{
    frames_picker->duplicateFrame();
}

