#include "mainwindow.h"
#include "hmaintest.h"

MainWindow::MainWindow(QWidget *parent) :
    HGView(HObjectInfo("framewindowId",""),parent),
    mainTest(NULL)
{
    init();
}

void MainWindow::init()
{
    mainTest = new HMainTest();
    mainTest->setupUi(this);
}

MainWindow::~MainWindow()
{
    hDelete(mainTest);
}
