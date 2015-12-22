#ifndef FRAME_H
#define FRAME_H


class Frame
{
public:
    int x,y,w,h; // Geometry
    int h_x,h_y; // Hot point

    Frame();
    Frame(int,int,int,int);
};

#endif // FRAME_H
