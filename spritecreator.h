#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QLabel>

#include <vector>

#include <spritepackage.h>
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
    SpritePackage package;
    Animation* current_anim;

    QMenuBar* menubar;
    QAction* action_save;
    QAction* action_save_as;
    QMenu* menu_anim;
    QMenu* menu_frame;

    AnimationsExplorer* anim_explorer;
    QPushButton* add_anim_button;
    AnimationParameters* anim_param;
    AnimationPlayer* anim_player;
    FramePicker* frames_picker;
    FramesExplorer* frames_explorer;

    QHBoxLayout* main_layout;
    QVBoxLayout* left_layout;
    QVBoxLayout* right_layout;

    void initMenuBar();
    void initLayouts();
    void initWidgets();

    void setModeInit();
    void setModeEdition();

    void updateAll();

    int askToSave();

signals:

public slots:
    bool newPackage();
    void loadPackage();
    void loadSpriteSheet();
    bool save();
    bool saveAs();
    void addAnimation();
    void duplicateFrame();
    void animationUpdated();
    void animationSelectionUpdated();
    void frameUpdated();

};

#endif // SPRITECREATOR_H
