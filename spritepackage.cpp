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

    // En-tête : width height
    int width = image.width();
    int height = image.height();
    file << image.width() << ' ' << image.height() << endl;

    // Image : bits
    QImage tmp_img = image.toImage();

    for(int j=0; j<height; ++j)
        for(int i=0; i<width; ++i)
        {
            QColor pixel = QColor::fromRgba(tmp_img.pixel(i,j));
            file.put((unsigned char)pixel.red());
            file.put((unsigned char)pixel.green());
            file.put((unsigned char)pixel.blue());
            file.put((unsigned char)pixel.alpha());
        }

    // Animations
    file << animations.size() << ' ';
    for(vector<Animation>::iterator it=animations.begin(); it!=animations.end(); ++it)
        file << *it;

    file.close();

    return true;
}



bool SpritePackage::load(QString filename)
{
    ifstream file(filename.toStdString().c_str(), ios::in | ios::binary);
    file.seekg(0, ios_base::beg);

    if(!file)
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return false;
    }

    // En-tête : width height
    int width, height;
    file >> width >> height;
    file.get();

    // Image : bits
    QImage tmp_img(width,height,QImage::Format_ARGB32);

    for(int j=0; j<height; ++j)
        for(int i=0; i<width; ++i)
        {
            unsigned char r,g,b,a;
            r = file.get(); g = file.get(); b = file.get(); a = file.get();
            tmp_img.setPixel(i,j,QColor(r,g,b,a).rgba());
        }

    image = QPixmap::fromImage(tmp_img);

    // Animations
    animations.clear();

    unsigned int nb_anims;
    file >> nb_anims;

    for(unsigned int i=0; i<nb_anims; ++i)
        animations.push_back(Animation(file));

    file.close();
    cout << "Lecture du fichier terminée." << endl;
    return true;
}



void SpritePackage::skip_line(istream& is) // On saute une ligne dans le fichier
{
    char c;
     do
        is.get(c);      // Lire un caractère
    while(c!='\n'); // tant qu'on n'atteint pas la fin de ligne.
}



void SpritePackage::reset()
{
    animations.clear();
    image = QPixmap();
}
