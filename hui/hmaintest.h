#ifndef TEST_H
#define TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <Qtwidgets/QBoxLayout>
#include <Qtwidgets/QStackedLayout>
#include <Qtwidgets/QGridLayout>
#include <hgview.h>
#include <hgwidget.h>
#include <hfactory.h>
#include <hcore.h>
#include <hgstackedwidget.h>
#include <huireader.h>
#include <hgscenestyle.h>
#include <hgscene.h>
class HMainTest
{
public:
    HMainTest()
    {
    }

    void setupUi(HGView *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(10, 20);

        HuiReader uiReader;

        // Test : xml for MainWindow set property.
        uiReader.createChild(":/xml/main.property.xml",QString(),MainWindow);

        // Test : xml for native window
        QList<QWidget*> qwlist = uiReader.createWidget(":/xml/main.widget.xml",QString(),MainWindow);
        for (int i = 0; i< qwlist.size();i++) {
            QWidget* first = qwlist.at(i);
            first->show();
        }

        // Test :
        uiReader.createChild(":/xml/main.scene.xml",QString(),MainWindow);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(HGView *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

#endif // TEST_H
