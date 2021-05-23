#ifndef FORTHEREST_MAINWINDOW_H
#define FORTHEREST_MAINWINDOW_H

#include <QWidget>

#include "GLWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* m_ui;
    GLWidget* m_glDisplay;
};


#endif //FORTHEREST_MAINWINDOW_H
