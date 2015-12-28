#include "frame.h"

Frame::Frame()
{
    x = y = w = h = 0;
    hotx = hoty = .5;
    min_w = min_h = 18;
}

Frame::Frame(int px, int py, int pw, int ph)
{
    x = px;
    y = py;
    w = pw;
    h = ph;

    if(w < 0)
    {
        w = -w;
        x -= w;
    }

    if(h < 0)
    {
        h = -h;
        y -= h;
    }

    hotx = hoty = .5;

    min_w = min_h = 18;
}


Frame::Frame(const Frame& other)
{
    x = other.x;
    y = other.y;
    w = other.w;
    h = other.h;
    hotx = other.hotx;
    hoty = other.hoty;
    min_w = min_h = 18;
}



Frame::Frame(ifstream& file)
{
    min_w = min_h = 18;

    file >> x;
    file >> y;
    file >> w;
    file >> h;

    int tmp_hx, tmp_hy;
    file >> tmp_hx;
    file >> tmp_hy;

    setHX(tmp_hx);
    setHY(tmp_hy);
}


ostream& operator << (ostream& os, Frame& f)
{
    os << f.x << " " << f.y << " " << f.w << " " << f.h << " " << f.getHotX() << " " << f.getHotY() << "\n";

    return os;
}



QRect Frame::getQRect()
{
    return QRect(x,y,(int)w,(int)h);
}


void Frame::check()
{
    x = max(0,x);
    y = max(0,y);
    w = max(min_w,w);
    h = max(min_h,h);

    hotx = max(0.0,hotx);
    hotx = min(1.0,hotx);
    hoty = max(0.0,hoty);
    hoty = min(1.0,hoty);
}



int Frame::getHotX()
{
    return (int)(hotx*w);
}


int Frame::getHotY()
{
    return (int)(hoty*h);
}



void Frame::setX(int px)
{
    x = px;
    x = max(0,x);
}


void Frame::setY(int py)
{
    y = py;
    y = max(0,y);
}


void Frame::setW(int px)
{
    w = px;
    if(w < 0)
    {
        w = -w;
        x -= w;
    }
}


void Frame::setH(int py)
{
    h = py;
    if(h < 0)
    {
        h = -h;
        y -= h;
    }
}


void Frame::setHX(int px)
{
    hotx = (double)px/w;
    check();
}


void Frame::setHY(int py)
{
    hoty = (double)py/h;
    check();
}



void Frame::move(int dx, int dy)
{
    x += dx;
    y += dy;

    check();
}



void Frame::moveX(int dx)
{
    x += dx;
    w -= dx;

    if(w < min_w)
        w = min_w;

    check();
}


void Frame::moveY(int dy)
{
    y += dy;
    h -= dy;

    if(h < min_h)
        h = min_h;

    check();
}


void Frame::moveW(int dx)
{
    w += dx;

    if(w < min_w)
    {
        x += dx;
        w = min_w;
    }

    check();
}


void Frame::moveH(int dy)
{
    h += dy;

    if(h < min_h)
    {
        y += dy;
        h = min_h;
    }

    check();
}



void Frame::moveHotpoint(int dx, int dy)
{
    hotx += (double)dx/w;
    hoty += (double)dy/h;
    check();
}



