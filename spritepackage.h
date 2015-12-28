#ifndef SPRITEPACKAGE_H
#define SPRITEPACKAGE_H

#include <QPixmap>

#include <animation.h>
#include <frame.h>

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class SpritePackage
{

public:
    SpritePackage();

    QPixmap image;
    vector<Animation> animations;

    bool save(QString filename);
    bool load(QString filename);
    void reset();

};

#endif // SPRITEPACKAGE_H
