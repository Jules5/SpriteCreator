#include "animation.h"

Animation::Animation()
{
    name = "Unnamed";
    speed = 10;
    repeated = false;
}


Animation::Animation(ifstream& file)
{
    name = "";
    unsigned int nb_c;
    file >> nb_c;

    for(unsigned int i=0; i<nb_c; ++i)
    {
        char c;
        file >> c;
        name.append(c);
    }

    file >> speed;
    file >> repeated;

    unsigned int nb_frames;
    file >> nb_frames;

    for(unsigned int i=0; i<nb_frames; ++i)
        frames.push_back(Frame(file));
}


ostream& operator << (ostream& os, Animation& anim)
{
    os << anim.name.size() << ' ' << anim.name.toStdString().c_str() << ' ' << anim.speed << ' ' << anim.repeated << ' ' << anim.frames.size() << ' ';

    for(vector<Frame>::iterator it=anim.frames.begin(); it!=anim.frames.end(); ++it)
        os << *it;

    return os;
}
