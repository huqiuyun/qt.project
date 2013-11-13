#include "hcreator.h"

HQCreator::HQCreator()
{
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QWidget>(objinfo,new QWidget(parent,(Qt::WindowFlags)param.mVar0.toUInt()));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QPushButton,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QPushButton>(objinfo,new QPushButton(param.mVar0.toString(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QCheckBox,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QCheckBox>(objinfo,new QCheckBox(parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QRadioButton,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QRadioButton>(objinfo,new QRadioButton(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QComboBox,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QComboBox>(objinfo,new QComboBox(parent));
}

//
IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTreeWidget>(objinfo,new QTreeWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTreeView>(objinfo,new QTreeView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QListWidget>(objinfo,new QListWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QListView>(objinfo,new QListView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTextBrowser,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTextBrowser>(objinfo,new QTextBrowser(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLabel,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QLabel>(objinfo,new QLabel(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLineEdit,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QLineEdit>(objinfo,new QLineEdit(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTabBar,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTabBar>(objinfo,new QTabBar(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QStackedWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QStackedWidget>(objinfo,new QStackedWidget(parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTableWidget>(objinfo,new QTableWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTableView>(objinfo,new QTableView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QSplitter,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QSplitter>(objinfo,new QSplitter((Qt::Orientation)param.mVar0.toUInt(),parent));
}
