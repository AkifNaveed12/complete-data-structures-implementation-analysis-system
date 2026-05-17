#include <QApplication>
#include <QStyleFactory>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set modern style base
    app.setStyle(QStyleFactory::create("Fusion"));

    MainWindow window;
    window.resize(1200, 800);
    window.show();

    return app.exec();
}
