#include <QApplication>
#include "treevisualizer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TreeVisualizer window;
    window.show();

    return app.exec();
}
