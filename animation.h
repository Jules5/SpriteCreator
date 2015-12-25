#ifndef ANIMATION_H
#define ANIMATION_H

#include <QString>

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

    friend ostream& operator << (ostream& os, const Animation&);
};

#endif // ANIMATION_H
