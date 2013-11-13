#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hmaintest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(NULL),
    mainTest(NULL)
{
#if 0
    ui = new Ui::MainWindow();
    ui->setupUi(this);
#else
    mainTest = new HMainTest();
    mainTest->setupUi(this);
#endif
}

MainWindow::~MainWindow()
{
    hDelete(ui);
    hDelete(mainTest);
}