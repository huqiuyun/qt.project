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
#include <Qtwidgets/QBoxLayout>
#include <Qtwidgets/QStackedLayout>
#include <Qtwidgets/QGridLayout>
#include <hgview.h>
#include <hgwidget.h>
#include <hbackgrounditem.h>
#include <hfactory.h>
#include <hcore.h>

class HMainTest
{
public:

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);

        // xml 展显出下面的结构出来.

        HGView *centralWidget = new HGView(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayout(qy::kVBox);

        HGView *graphicsView = 0;
        {
            graphicsView = new HGView(centralWidget);
            graphicsView->setObjectName(QStringLiteral("graphicsView"));

            HGWidget* clientWidget = graphicsView->clientWidget();
            clientWidget->backgroundItem()->setColor(QColor(250,250,250));

            long hr = 0;
            {//1
                HGView* widget1 = new HGView();

                widget1->setLayout(qy::kGrid);
                QGridLayout* layout = static_cast<QGridLayout*>(widget1->layout());
                for( int i = 0; i < 10 ; i++)
                {
                    QPushButton* button =
                            static_cast<QPushButton*>(HFACTORY->createQWidget(HClassInfo("QPushButton","",""),widget1,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    button->setFixedSize(80,48);
                    layout->addWidget(button,i%4,i/4);
                }
                clientWidget->addWidget(widget1);

                widget1->clientWidget()->backgroundItem()->setColor(QColor(100,100,100));
            }
            {//2
                HGWidget* grwidget2 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget2);
                grwidget2->backgroundItem()->setColor(QColor(150,150,50));
                {
                    grwidget2->setLayout(qy::kHBox);
                    HGWidget* grwidget2_1 = new HGWidget(grwidget2);
                    grwidget2->addItem(grwidget2_1);
                    grwidget2_1->backgroundItem()->setColor(QColor(150,50,50));

                    HGWidget* grwidget2_2 = new HGWidget(grwidget2);
                    grwidget2->addItem(grwidget2_2);
                    grwidget2_2->backgroundItem()->setColor(QColor(150,50,250));
                }
            }
            {//3
                HGWidget* grwidget3 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget3);
                grwidget3->backgroundItem()->setColor(QColor(50,250,50));
            }
            centralWidget->layout()->addWidget(graphicsView);
        }
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

#endif // TEST_H
