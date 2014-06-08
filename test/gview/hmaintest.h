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
#include <Qtwidgets/QLineEdit>
#include <Qtwidgets/QTextEdit>
#include <Qtgui/QMovie>

#include <hgview.h>
#include <hgwidget.h>
#include <hfactory.h>
#include <hcore.h>
#include <hgstackedwidget.h>
#include <huireader.h>
#include <hpropertyproxy.h>
#include <hdraw.h>

class HMainTest : public QObject
{
    Q_OBJECT
public:
    HMainTest()
    {
    }

    void setupUi(HGView *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(10, 20);

        HPropertyProxy proproxy;
        HuiReader uiReader(&proproxy);

        qDebug("1----");
        // Test : xml for MainWindow set property.
        uiReader.createChild(":/xml/main.property.xml",QString(),MainWindow);

        // Test : xml for native window
  /*      QList<QWidget*> qwlist = uiReader.createWidget(":/xml/main.widget.xml",QString(),MainWindow);
        for (int i = 0; i< qwlist.size();i++) {
            QWidget* first = qwlist.at(i);
            first->show();
        }
*/
        // Test :
        qDebug("2----");
        uiReader.createChild(":/xml/main.scene.xml",QString(),MainWindow);

        qDebug("3----");
        mEditor = MainWindow->rootWidget()->findWidget<QTextEdit*>(QLatin1String("qlineedit.usrname"));
        QObject::connect(mEditor,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
        QObject::connect(mEditor,SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),this,SLOT(onCurrentCharFormatChanged(const QTextCharFormat&)));

        QTextCursor cursor = mEditor->textCursor();
        if (0)
        {//html
            QFile file(":/theme/xx.html");
            file.open(QFile::ReadOnly);
            QByteArray data = file.readAll();
            mEditor->setHtml(QString(data));
        }

        if (1)
        {
            QTextFrameFormat format;
            format.setBackground(QBrush(QColor(192,192,192)));
            format.setHeight(80);
            cursor.insertFrame(format);
        }

        if (1)
        {//image
            QImage image;
            image.load(":/theme/bg.png");
            mEditor->document()->addResource(QTextDocument::ImageResource,QUrl("edit:/res/screenshot_1"),QVariant(image));
            QTextImageFormat format;
            format.setName("edit:/res/screenshot_1");
            format.setWidth(image.width());
            format.setHeight(image.height());
            cursor.insertImage(format);
        }

        if (1)
        {//gif
            QMovie* movie = new QMovie(this);
            movie->setFileName(":/theme/loading.gif");
            movie->setCacheMode(QMovie::CacheNone);

            connect(movie, SIGNAL(frameChanged(int)), this, SLOT(onAnimate(int)));
            movie->start();

            QTextImageFormat format;
            format.setName("editor:/gifTag");
            cursor.insertImage(format);
        }

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(HGView *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

private slots:
    void onTextChanged()
    {
        QTextEdit* edit = qobject_cast<QTextEdit*>(sender());
        QRect  rect = edit->geometry();
        qDebug("0 Rect(%d,%d,%d,%d)",rect.left(),rect.top(),rect.right(),rect.bottom());
    }

    void onCurrentCharFormatChanged(const QTextCharFormat&)
    {
        QTextEdit* edit = qobject_cast<QTextEdit*>(sender());
        QRect  rect = edit->geometry();
        qDebug("1 Rect(%d,%d,%d,%d)",rect.left(),rect.top(),rect.right(),rect.bottom());
    }

    void onAnimate(int a)
    {
        Q_UNUSED(a);
        if (QMovie* movie = qobject_cast<QMovie*>(sender()))
        {
            mEditor->document()->addResource(QTextDocument::ImageResource,QUrl("editor:/gifTag"), movie->currentPixmap());
            mEditor->setLineWrapColumnOrWidth(mEditor->lineWrapColumnOrWidth());
        }
    }
private:
    QPointer<QTextEdit> mEditor;
};

#endif // TEST_H
