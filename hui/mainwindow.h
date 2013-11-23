#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <hgview.h>

namespace Ui {
class MainWindow;
}
class HMainTest;

class MainWindow : public HGView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    Ui::MainWindow *ui;
    HMainTest* mainTest;
};

#endif // MAINWINDOW_H
