#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QLabel>

#include <animationsexplorer.h>
#include <animationparameters.h>
#include <spritepicker.h>
#include <framesexplorer.h>
#include <animationplayer.h>

using namespace std;

class SpriteCreator : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteCreator(QWidget *parent = 0);

private:
    QString filename;

    QMenuBar* menubar;
    QAction* action_save;
    QAction* action_save_as;

    AnimationsExplorer* anim_explorer;
    AnimationParameters* anim_param;
    SpritePicker* sprite_picker;
    FramesExplorer* frames_explorer;
    AnimationPlayer* anim_player;

    QHBoxLayout* main_layout;
    QVBoxLayout* left_layout;
    QVBoxLayout* right_layout;

    void initMenuBar();
    void initLayouts();
    void initWidgets();

    bool savePackage();

signals:

public slots:
    void newPackage();
    void spriteSheetLoaded();

};

#endif // SPRITECREATOR_H
