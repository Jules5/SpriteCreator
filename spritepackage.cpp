#include "spritepackage.h"

SpritePackage::SpritePackage()
{
    image = NULL;
    animations = NULL;
}


bool SpritePackage::save(QString filename)
{
    ofstream file(filename.toStdString().c_str(), ios::out | ios::binary);

    if(!file)
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return false;
    }

    file << animations->size();

    for(vector<Animation>::iterator it=animations->begin(); it!=animations->end(); ++it)
        file << *it;


    file.close();
    return true;
}
