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
#include <hbackgrounditem.h>
#include <hfactory.h>
#include <hcore.h>
#include <hgstackedwidget.h>

class HMainTest
{
public:

    void setupUi(HGView *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);

        // xml 展显出下面的结构出来.

        MainWindow->setLayout(qy::kVBox);

        HGView *graphicsView = 0;
        {
            graphicsView = new HGView(MainWindow);
            graphicsView->setObjectName(QStringLiteral("graphicsView"));

            HGWidget* clientWidget = graphicsView->clientWidget();
            clientWidget->backgroundItem()->setColor(QColor(250,250,250));

            long hr = 0;
            {//1
                HGView* widget = new HGView();

                widget->setLayout(qy::kGrid);
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

                widget->clientWidget()->backgroundItem()->setColor(QColor(100,100,100));
            }
            {
                HGView* widget = new HGView();

                widget->setLayout(qy::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QCheckBox* button =
                            static_cast<QCheckBox*>(HFACTORY->createQWidget(HClassInfo("QCheckBox","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
                widget->clientWidget()->backgroundItem()->setColor(QColor(100,110,100));
            }
            {
                HGView* widget = new HGView();

                widget->setLayout(qy::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QRadioButton* button =
                            static_cast<QRadioButton*>(HFACTORY->createQWidget(HClassInfo("QRadioButton","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
                widget->clientWidget()->backgroundItem()->setColor(QColor(100,120,100));
            }
            {
                HGView* widget = new HGView();

                widget->setLayout(qy::kHBox);
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(widget->layout());
                for( int i = 0; i < 4 ; i++)
                {
                    QRadioButton* button =
                            static_cast<QRadioButton*>(HFACTORY->createQWidget(HClassInfo("QRadioButton","",""),widget,HCreateParameter(false,QString("button%1").arg(i)),&hr));
                    layout->addWidget(button);
                }
                widget->setFixedHeight(40);
                clientWidget->addWidget(widget);
                widget->clientWidget()->backgroundItem()->setColor(QColor(100,150,100));
            }
            {//2
                HGWidget* grwidget2 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget2);
                grwidget2->backgroundItem()->setColor(QColor(150,150,50));
                {
                    grwidget2->setLayout(qy::kHBox);
                    HGStackedWidget* grwidget2_1 = new HGStackedWidget(grwidget2);
                    grwidget2->addItem(grwidget2_1);
                   // grwidget2_1->backgroundItem()->setColor(QColor(150,50,50));

                    HGWidget* grwidget2_2 = new HGWidget(grwidget2_1);
                    grwidget2_1->addHGWidget(grwidget2_2);
                    grwidget2_1->setCurrentIndex(0);
                    grwidget2_2->backgroundItem()->setColor(QColor(150,50,250));
                }
            }
           // for(int i = 0; i<8;i++)
            {//3
                HGWidget* grwidget3 = new HGWidget(clientWidget);
                clientWidget->addItem(grwidget3);
                grwidget3->backgroundItem()->setColor(QColor(50,250,50));
            }
            MainWindow->layout()->addWidget(graphicsView);
        }

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(HGView *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

#endif // TEST_H
