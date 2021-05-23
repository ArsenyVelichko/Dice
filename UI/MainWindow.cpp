// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGridLayout>


MainWindow::MainWindow(QWidget* parent) :
        QWidget(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    auto* layout = new QGridLayout(this);

    m_glDisplay = new GLWidget;
    layout->addWidget(m_glDisplay);
}

MainWindow::~MainWindow() {
    delete m_ui;
}

