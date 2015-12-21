#include <QApplication>
#include <QTextStream>

#include "spritecreator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/style.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
        file.close();
    }

    SpriteCreator window;
    window.show();

    return app.exec();
}
