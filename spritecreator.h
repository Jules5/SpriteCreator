#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QLabel>

#include <vector>

#include <animation.h>
#include <animationsexplorer.h>
#include <animationparameters.h>
#include <framepicker.h>
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
    vector<Animation> animations;

    QMenuBar* menubar;
    QAction* action_save;
    QAction* action_save_as;

    AnimationsExplorer* anim_explorer;
    QPushButton* add_anim_button;
    AnimationParameters* anim_param;
    AnimationPlayer* anim_player;
    FramePicker* sprite_picker;
    FramesExplorer* frames_explorer;

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
    void addAnimation();
    void animationEdited();
    void changeAnimationSelection();

};

#endif // SPRITECREATOR_H
