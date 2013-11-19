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
        MainWindow->resize(800, 600);

        // xml 展显出下面的结构出来.
       HUIReader uiReader;
       uiReader.createChildWithGView(":/layout/main/lt.main.xml",MainWindow);
/*
        MainWindow->setLayoutType(HEnums::kVBox);

        HGView *graphicsView = 0;
        {
            graphicsView = new HGView(MainWindow);

            HGWidget* clientWidget = graphicsView->clientWidget();

            long hr = 0;
            if (1)
            {//1
                HGView* widget = new HGView();

                widget->setLayoutType(HEnums::kGrid);
                QGridLayout* layout = static_cast<QGridLayout*>(widget->layout());
                for( int i = 0; i < 6 ; i++)
                {
                    QPushButton* button =
                            static_cast<QPushButton*>(HFACTORY->createQWidget(HClassInfo("QPushButton","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    button->setFixedSize(80,48);
                    layout->addWidget(button,i%3,i/3);
                }
                widget->setFixedSize(400,200);
                clientWidget->addWidget(widget);

            }
            if (1)
            {
                HGView* widget = new HGView();

                widget->setLayoutType(HEnums::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QCheckBox* button =
                            static_cast<QCheckBox*>(HFACTORY->createQWidget(HClassInfo("QCheckBox","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
            }
            if (1)
            {
                HGView* widget = new HGView();

                widget->setLayoutType(HEnums::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QRadioButton* button =
                            static_cast<QRadioButton*>(HFACTORY->createQWidget(HClassInfo("QRadioButton","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
            }
            if (1)
            {
                HGView* widget = static_cast<HGView*>(HFACTORY->createQWidget(HClassInfo("HGView","framewindowId",""),NULL,HCreateParameter(),&hr));

                widget->setLayoutType(HEnums::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QRadioButton* button =
                            static_cast<QRadioButton*>(HFACTORY->createQWidget(HClassInfo("QRadioButton","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
            }
            if (1)
            {//2
                HGWidget* grwidget2 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget2);
                {
                    grwidget2->setLayoutType(HEnums::kHBox);
                    HGStackedWidget* grwidget2_1 = new HGStackedWidget(grwidget2);
                    grwidget2->addItem(grwidget2_1);

                    HGWidget* grwidget2_2 = new HGWidget(grwidget2_1);
                    grwidget2_1->addHGWidget(grwidget2_2);
                    grwidget2_1->setCurrentIndex(0);
                }
            }
            for(int i = 0; i<8;i++)
            {//3
                HGWidget* grwidget3 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget3);
            }
            MainWindow->layout()->addWidget(graphicsView);
        }
*/
        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(HGView *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

#endif // TEST_H
