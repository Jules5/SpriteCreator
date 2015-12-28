#ifndef FRAME_H
#define FRAME_H

#include <QRect>

#include <iostream>
#include <fstream>

using namespace std;

class Frame
{
private:
    double hotx,hoty; // Hot point (ratio)

public:
    int x,y,w,h; // Geometry
    int min_w,min_h; // Taille minimale

    Frame();
    Frame(int,int,int,int);
    Frame(const Frame&);
    Frame(ifstream&);

    QRect getQRect();

    void check();

    int getHotX();
    int getHotY();

    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);
    void setHX(int);
    void setHY(int);

    void move(int, int);
    void moveX(int);
    void moveY(int);
    void moveW(int);
    void moveH(int);
    void moveHotpoint(int,int);

    friend ostream& operator << (ostream& os, Frame&);
};

#endif // FRAME_H
