#include "spritepackage.h"

SpritePackage::SpritePackage()
{
    animations.clear();
}


bool SpritePackage::save(QString filename)
{
    ofstream file(filename.toStdString().c_str(), ios::out | ios::binary);

    if(!file)
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return false;
    }

//    QImage tmp_img = image.toImage();
//    const uchar* bits = tmp_img.constBits();
//    file << tmp_img.byteCount() << "\n";
//    file.write((char *)&bits[0],tmp_img.byteCount());

    image = QPixmap::fromImage(QImage("braid.png"));

    file << animations.size() << "\n";

    for(vector<Animation>::iterator it=animations.begin(); it!=animations.end(); ++it)
        file << *it;

    file.close();

    return true;
}



bool SpritePackage::load(QString filename)
{
    ifstream file(filename.toStdString().c_str(), ios::in | ios::binary);

    if(!file)
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return false;
    }

    int nb_bytes;
    file >> nb_bytes;
    char bits[nb_bytes];
    file.read(bits,nb_bytes);
    image.loadFromData((uchar *)&bits[0],nb_bytes);

    animations.clear();

    unsigned int nb_anims;
    file >> nb_anims;

    for(unsigned int i=0; i<nb_anims; ++i)
        animations.push_back(Animation(file));

    file.close();
    cout << "Lecture du fichier terminée." << endl;
    return true;
}



void SpritePackage::reset()
{
    animations.clear();
    image = QPixmap();
}
