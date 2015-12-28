#ifndef ANIMATION_H
#define ANIMATION_H

#include <QString>

#include <iostream>
#include <fstream>
#include <vector>
#include <frame.h>

using namespace std;

class Animation
{
public:
    vector<Frame> frames;
    QString name;
    int speed;
    bool repeated;

    Animation();
    Animation(ifstream&);

    friend ostream& operator << (ostream& os, Animation&);
};

#endif // ANIMATION_H
