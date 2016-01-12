#include "framepicker.h"

FramePicker::FramePicker(QPixmap* img, QWidget *parent) : QGraphicsView(parent)
{
    enabled = false;

    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    is_selecting = false;
    is_dragging = false;

    frames = NULL;
    selected_frame = NULL;

    button_load = new QPushButton("Load a spritesheet...",this);

    image = img;
    scene = new QGraphicsScene(this);
    setScene(scene);

    brush = QColor(0,0,0,128);
    pen_selected = QColor(73,255,20);
    brush_selected = QColor(73,255,20);

    update();
}


void FramePicker::reset()
{
    scene->clear();
    setEnabled(false);
    update();
}


void FramePicker::update()
{
    scene->clear();

    if(image == NULL || !enabled)
    {
        button_load->show();
        return;
    }

    button_load->hide();
    scene->addPixmap(*image);

//    QImage tmp_img = image->toImage();
//    const uchar* bits = tmp_img.constBits();
//    cout << (int)tmp_img.byteCount() << endl;

    if(frames != NULL)
    {
        for(vector<Frame>::iterator it=frames->begin(); it!=frames->end(); ++it)
            if(&*it != selected_frame)
                drawFrame(&*it);
        drawFrame(selected_frame);
    }

    if(is_selecting)
        scene->addRect(getSelection(),QPen(),brush);
}


void FramePicker::setEnabled(bool b)
{
    enabled = b;
    update();
}



void FramePicker::drawFrame(Frame* frame)
{
    if(frame == NULL)
        return;

    // Cadre
    scene->addRect(frame->getQRect(),QPen(),brush);

    // Frame selectionnée
    if(!is_selecting && selected_frame == &*frame)
    {
        // Hot Point Grid
        scene->addLine(QLine(frame->x,frame->getHotY()+frame->y,frame->x+frame->w,frame->getHotY()+frame->y),pen_selected);
        scene->addLine(QLine(frame->x+frame->getHotX(),frame->y,frame->x+frame->getHotX(),frame->y+frame->h),pen_selected);

        // Corners + Hot Point
        int s = 8;
        scene->addRect(QRect(frame->x,frame->y,s,s),QPen(),brush_selected);
        scene->addRect(QRect(frame->x+frame->w-s,frame->y,s,s),QPen(),brush_selected);
        scene->addRect(QRect(frame->x,frame->y+frame->h-s,s,s),QPen(),brush_selected);
        scene->addRect(QRect(frame->x+frame->w-s,frame->y+frame->h-s,s,s),QPen(),brush_selected);
        scene->addRect(QRect(frame->x+frame->getHotX()-s/2,frame->y+frame->getHotY()-s/2,s,s),QPen(),brush_selected);
    }

    // Les autres frames
    else
    {
        // Hot Point Grid
        scene->addLine(QLine(frame->x,frame->getHotY()+frame->y,frame->x+frame->w,frame->getHotY()+frame->y));
        scene->addLine(QLine(frame->x+frame->getHotX(),frame->y,frame->x+frame->getHotX(),frame->y+frame->h));
    }
}


void FramePicker::sceneResized()
{
    QRectF rect = scene->itemsBoundingRect();
    scene->setSceneRect(rect);
}


void FramePicker::setFrames(vector<Frame>* f)
{
    frames = f;
    selected_frame = NULL;
}



void FramePicker::setImage(QPixmap* img)
{
    image = img;
}



QRect FramePicker::getSelection()
{
    QRect tmp(x,y,w,h);

    if(w < 0)
    {
        tmp.setX(x+w);
        tmp.setWidth(-w);
    }

    if(h < 0)
    {
        tmp.setY(y+h);
        tmp.setHeight(-h);
    }

    return tmp;
}



void FramePicker::duplicateFrame()
{
    if(selected_frame != NULL)
    {
        Frame frame(*selected_frame);
        frame.move(20,20);
        frames->push_back(frame);
        selected_frame = &frames->back();
        update();
    }
}



void FramePicker::deleteFrame(Frame* frame)
{
    if(frame != NULL)
        for(vector<Frame>::iterator it=frames->begin(); it!=frames->end(); ++it)
            if(&*it == frame)
            {
                if(frame == selected_frame)
                    selected_frame = it != frames->begin() ? &*(it-1) : it != frames->end()-1 ? &*(it) : NULL;

                frames->erase(it);
                update();
                emit frameUpdated();
                break;
            }
}




bool FramePicker::checkClickCollision(int rx, int ry, Frame* frame)
{
    if(frame == NULL)
        return false;

    if(rx >= frame->x && rx <= frame->x+frame->w && ry >= frame->y && ry <= frame->y+frame->h)
    {
        is_dragging = true;
        old_x = rx;
        old_y = ry;
        selected_frame = &*frame;

        int size = 8;
        if(rx <= frame->x+size && ry <= frame->y+size)
            dragged = "topLeft";
        else if(rx >= frame->x+frame->w-size && ry <= frame->y+size)
            dragged = "topRight";
        else if(rx <= frame->x+size && ry >= frame->y+frame->h-size)
            dragged = "bottomLeft";
        else if(rx >= frame->x+frame->w-size && ry >= frame->y+frame->h-size)
            dragged = "bottomRight";
        else if(rx >= frame->x+frame->getHotX()-size/2 && rx <= frame->x+frame->getHotX()+size/2 && ry >= frame->y+frame->getHotY()-size/2 && ry <= frame->y+frame->getHotY()+size/2)
            dragged = "center";
        else
            dragged = "frame";

        return true;
    }

    return false;
}



void FramePicker::mousePressEvent(QMouseEvent *event)
{
    if(!enabled)
        return;

    int rx = event->pos().x()+horizontalScrollBar()->value();
    int ry = event->pos().y()+verticalScrollBar()->value();

    if(image != NULL && event->button() == Qt::LeftButton)
    {
        bool ok = checkClickCollision(rx,ry,selected_frame);

        for(vector<Frame>::iterator it=frames->begin(); !ok && it!=frames->end(); it++)
            if(checkClickCollision(rx,ry,&*it))
                break;

        if(!is_dragging)
        {
            is_selecting = true;
            x = rx;
            y = ry;
            w = h = 0;
            update();
        }
    }
}



void FramePicker::mouseMoveEvent(QMouseEvent *event)
{
    int rx = event->pos().x()+horizontalScrollBar()->value();
    int ry = event->pos().y()+verticalScrollBar()->value();

    if(is_selecting)
    {
        int dx = rx - x;
        int dy = ry - y;
        w = dx;
        h = dy;
        update();
    }
    else if(is_dragging)
    {
        int dx = rx - old_x;
        int dy = ry - old_y;
        old_x = rx;
        old_y = ry;

        if(dragged == "frame")
            selected_frame->move(dx,dy);
        else if(dragged == "topLeft")
        {
            selected_frame->moveX(dx);
            selected_frame->moveY(dy);
        }
        else if(dragged == "topRight")
        {
            selected_frame->moveW(dx);
            selected_frame->moveY(dy);
        }
        else if(dragged == "bottomLeft")
        {
            selected_frame->moveX(dx);
            selected_frame->moveH(dy);
        }
        else if(dragged == "bottomRight")
        {
            selected_frame->moveW(dx);
            selected_frame->moveH(dy);
        }
        else if(dragged == "center")
            selected_frame->moveHotpoint(dx,dy);

        update();
    }
}


void FramePicker::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(is_selecting)
        {
            is_selecting = false;
            frames->push_back(Frame(x,y,w,h));
            selected_frame = &(frames->back());
        }
        else if(is_dragging)
        {
            is_dragging = false;
        }

        emit frameUpdated();
    }
}



void FramePicker::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D && event->modifiers() == Qt::ControlModifier) // Ctrl+D
        duplicateFrame();

    else switch(event->key())
    {
        case Qt::Key_D :
            if(event->modifiers() == Qt::ControlModifier) // Ctrl+D
                duplicateFrame();
            break;

        case Qt::Key_Backspace : // Delete
        case Qt::Key_Delete :
            deleteFrame(selected_frame);
            break;

        case Qt::Key_Up :
            if(selected_frame != NULL)
                selected_frame->move(0,-1);
            break;

        case Qt::Key_Down :
            if(selected_frame != NULL)
                selected_frame->move(0,1);
            break;

        case Qt::Key_Left :
            if(selected_frame != NULL)
                selected_frame->move(-1,0);
            break;

        case Qt::Key_Right :
            if(selected_frame != NULL)
                selected_frame->move(1,0);
            break;
    }

    emit frameUpdated();
}
