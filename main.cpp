#include <QApplication>
#include <QPushButton>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

	Q_INIT_RESOURCE(Shaders);

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
