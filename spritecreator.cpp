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
    animations.clear();
    showMaximized();

    // Connections
    connect(anim_explorer,SIGNAL(itemSelectionChanged()),this,SLOT(changeAnimationSelection()));
    connect(add_anim_button,SIGNAL(clicked(bool)),this,SLOT(addAnimation()));
    connect(anim_param,SIGNAL(animationEdited()),this,SLOT(animationEdited()));
    connect(frames_picker,SIGNAL(spriteSheetLoaded()),this,SLOT(spriteSheetLoaded()));
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
    anim_explorer = new AnimationsExplorer(&animations, this);
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
    anim_player = new AnimationPlayer(this);
    anim_player->setDisabled(true);
    anim_player->setFixedWidth(200);
    anim_player->setFixedHeight(220);
    left_layout->addWidget(anim_player);

    // Sprite Picker
    frames_picker = new FramePicker(this);
    right_layout->addWidget(frames_picker);

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

    disconnect(anim_explorer,SIGNAL(itemSelectionChanged()),this,NULL);

    frames_picker->reset();
    anim_explorer->reset();
    anim_player->reset();
    frames_explorer->reset();

    connect(anim_explorer,SIGNAL(itemSelectionChanged()),this,SLOT(changeAnimationSelection()));

    animations.clear();

    anim_explorer->setEnabled(false);
    add_anim_button->setEnabled(false);
    anim_param->setEnabled(false);
    anim_param->clearForm();
    anim_player->setEnabled(false);
    frames_explorer->setEnabled(false);
}


void SpriteCreator::save()
{
    if(filename == "")
        return saveAs();

    SpritePackage package;
    package.animations = &animations;
    package.image = frames_picker->getPixmapReference();
    if(!package.save(filename))
        QMessageBox::information(this,tr("Error"),tr("Impossible to write in the specified file."),QMessageBox::Ok);
}


void SpriteCreator::saveAs()
{
    filename = QFileDialog::getSaveFileName(this, tr("Save Package"), "", tr("Sprite Package (*.spr)"));
    save();
}



void SpriteCreator::spriteSheetLoaded()
{
    // On active les widgets désactivés
    anim_explorer->setEnabled(true);
    add_anim_button->setEnabled(true);
    anim_param->setEnabled(true);
    anim_player->setEnabled(true);
    frames_explorer->setEnabled(true);

    action_save->setEnabled(true);
    action_save_as->setEnabled(true);

    // On crée une animation vide et on met à jour les widgets
    animations.push_back(Animation());
    frames_picker->setFrames(&(animations.back().frames));
    anim_explorer->animationInserted();
    anim_param->animation = &(animations.back());
    anim_param->updateForm();
    anim_player->setAnimation(&animations.back());
    anim_player->setPixmap(frames_picker->getPixmapReference());
    frames_explorer->setImage(frames_picker->getPixmapReference());
    frames_explorer->setFrames(&(animations.back().frames));
    frames_explorer->update();
}



void SpriteCreator::addAnimation()
{
    // Ajout de l'animation
    animations.push_back(Animation());

    // Répercussion dans les widgets
    anim_explorer->animationInserted();
}


void SpriteCreator::animationEdited()
{
    anim_explorer->updateSelectedItem();
}


void SpriteCreator::changeAnimationSelection()
{
    Animation* current = &(animations.at(anim_explorer->getSelectedIndex()));
    anim_param->animation = current;
    anim_param->updateForm();
    frames_picker->setFrames(&(current->frames));
    frames_picker->update();
    frames_explorer->setFrames(&(current->frames));
    frames_explorer->update();
}


void SpriteCreator::frameUpdated()
{
    frames_explorer->update();
    anim_player->play();
}


void SpriteCreator::duplicateFrame()
{
    frames_picker->duplicateFrame();
}

