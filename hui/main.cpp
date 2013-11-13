#include "mainwindow.h"
#include <hcore.h>
#include <hsystem.h>
#include <QApplication>

class HApplication : public QApplication
{
public:
    HApplication(int argc,char*argv[]) :
        QApplication(argc,argv)
    {
        mHCore = new HCore(this);
        HCore::initHCore(mHCore);
        //
        HSYSTEM->setAppPath(applicationDirPath());
        //
    }

    ~HApplication()
    {
        HCore::initHCore(NULL);
        delete mHCore;
    }

private:
    HCore* mHCore;
};

int main(int argc, char *argv[])
{
    HApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
