#include "animation.h"

Animation::Animation()
{
    name = "Unnamed";
    speed = 10;
    repeated = false;
}


ostream& operator << (ostream& os, const Animation& anim)
{
    os << anim.name.toStdString();
    os << "caca";
    return os;
}
