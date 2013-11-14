#include "HGView.h"
#include "HGWidget.h"
#include "hframestyle.h"
#include "hbackgrounditem.h"
#include "hcore.h"
#include "hcssstyle.h"
#include "hfactory.h"
#include "private/HGView_p.h"
#include <QGraphicsScene>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>

HGViewPrivate::HGViewPrivate(const QLatin1String& styleid) :
    q_ptr(NULL),
    mScene(NULL),
    mWidget(NULL),
    mFrameStyle(NULL),
    mStyleId(styleid)
{
    mCss =
            QSharedPointer<HCssObject>(HCSSSTYLE->create(HCssStyle::idCheck(styleid,QLatin1String("framewindowId")),"HCssFrame"));
}

HGViewPrivate::~HGViewPrivate()
{
    hDelete(mScene);
}

void HGViewPrivate::initScene()
{
    long hr = 0;
    HClassInfo cls = q_ptr->css()->frameStyle();
    mFrameStyle =
            static_cast<HFrameStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
    mFrameStyle->setView(q_ptr);
    //

    //init scene
    mScene = new QGraphicsScene();
    q_ptr->setScene(mScene);

    //init content item
    cls = q_ptr->css()->clientWidget();
    mWidget = static_cast<HGWidget*>(HFACTORY->createGItem(cls,NULL,HCreateParameter(),&hr));
    mWidget->setParent(mScene);
    mScene->addItem(mWidget);

    mWidget->setLayout(qy::kVBox);

    //保证每个frame必定有名字
    static int s_index = 0;
    QString name = "NoNameFrame" + QString::number(s_index++);
    q_ptr->setObjectName(name);
}

IMPLEMENT_GVIEW_STATIC_CREATE(HGView)
HGView::HGView(QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGViewPrivate(QLatin1String("frameId")))
{
    d_ptr->q_ptr = this;
    d_ptr->initScene();
}

HGView::HGView(const HObjectInfo& objinfo, QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGViewPrivate(objinfo.mStyleId))
{
    d_ptr->q_ptr = this;
    d_ptr->initScene();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName);
}

HGView::~HGView()
{
    delete d_ptr;
}

void HGView::doConstruct()
{
    //
    frameStyle()->init();
    //
    construct();
}

void HGView::setFrameStyle(HFrameStyle *style)
{
    Q_D(HGView);
    HFrameStyle* oldStyle =frameStyle();
    if (oldStyle == style)
        return ;

    if (NULL==style)
    {
        long hr = 0;
        HClassInfo cls = css()->frameStyle();
        style =
                static_cast<HFrameStyle*>(HFACTORY->createObject(cls,this,HCreateParameter(),&hr));
        style->setView(this);
    }
    d->mFrameStyle = style;
    delete oldStyle;
}

HFrameStyle* HGView::frameStyle() const
{
    return d_func()->mFrameStyle;
}

HCssFrame* HGView::css()  const
{
    return static_cast<HCssFrame*>(d_func()->mCss.data());
}

bool HGView::setCss(QSharedPointer<HCssObject> obj)
{
    HCssFrame* css = static_cast<HCssFrame*>(obj.data());
    if (!css)
    {
        return false;
    }
    d_func()->mCss = obj;
    return true;
}

HGWidget* HGView::clientWidget() const
{
    return d_func()->mWidget;
}

void HGView::setSpacing(int s)
{
    css()->setSpacing(s);
    QLayout* l = static_cast<QLayout*>(layout());
    if (!l) return ;

    switch (layoutType())
    {
    case qy::kVBox:
    case qy::kHBox:
    case qy::kVBoxBottomTop:
    case qy::kVBoxTopBottom:
    case qy::kHBoxLeftRight:
    case qy::kHBoxRightLeft:
    {
        static_cast<QBoxLayout*>(l)->setSpacing(s);
        break;
    }
    case qy::kGrid:
    {
        static_cast<QGridLayout*>(l)->setSpacing(s);
        break;
    }
    case qy::kStacked:
    {
        static_cast<QStackedLayout*>(l)->setSpacing(s);
        break;
    }
    default:
        break;
    }
}

QMargins HGView::margins() const
{
    if (layout())
    {
        int left = 0;
        int top = 0;
        int right = 0;
        int bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return QMargins();
}

void HGView::setMargins(const QMargins& m)
{
    if (layout())
    {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
}

Qt::Alignment HGView::alignment() const
{
    HGView* p = static_cast<HGView*>(parent());
    if (p != NULL && p->layout() != NULL)
    {
        switch (p->layoutType())
        {
        case qy::kHBox:
        {
            QHBoxLayout* l = static_cast<QHBoxLayout*>(p->layout());
            return l->alignment();
        }
        case qy::kVBox:
        {
            QVBoxLayout* l = static_cast<QVBoxLayout*>(p->layout());
            return l->alignment();
        }
        case qy::kVBoxBottomTop:
        case qy::kVBoxTopBottom:
        case qy::kHBoxLeftRight:
        case qy::kHBoxRightLeft:
        {
            QBoxLayout* l = static_cast<QBoxLayout*>(p->layout());
            return l->alignment();
        }
        case qy::kGrid:
        {
            QGridLayout* l = static_cast<QGridLayout*>(p->layout());
            return l->alignment();
        }
        case qy::kStacked:
        {
            QStackedLayout* l = static_cast<QStackedLayout*>(p->layout());
            return l->alignment();
        }
        default:
            break;
        }
    }
    return Qt::AlignCenter;
}

void HGView::setAlignment(Qt::Alignment align)
{
    HGView* p = static_cast<HGView*>(parent());
    if (p != NULL && p->layout() != NULL)
    {
        switch (p->layoutType())
        {
        case qy::kHBox:
        {
            break;
        }
        case qy::kVBox:
        {
            break;
        }
        case qy::kVBoxBottomTop:
        case qy::kVBoxTopBottom:
        case qy::kHBoxLeftRight:
        case qy::kHBoxRightLeft:
        {
            QBoxLayout* l = static_cast<QBoxLayout*>(p->layout());
            l->setAlignment(this,align);
            break;
        }
        case qy::kGrid:
        {
            QGridLayout* l = static_cast<QGridLayout*>(p->layout());
            l->setAlignment(this,align);
            break;
        }
        case qy::kStacked:
        {
            QStackedLayout* l = static_cast<QStackedLayout*>(p->layout());
            l->setAlignment(this,align);
            break;
        }
        default:
            break;
        }
    }
}

qy::HLayoutType HGView::layoutType() const
{
    return css()->layoutType();
}

void HGView::setLayout(qy::HLayoutType type)
{
    QLayout *layout = NULL;
    switch (type)
    {
    case qy::kVBox:
        layout = new QVBoxLayout(this);
        break;
    case qy::kHBox:
        layout = new QHBoxLayout(this);
        break;
    case qy::kVBoxBottomTop:
        layout = new QBoxLayout(QBoxLayout::BottomToTop,this);
        break;
    case qy::kVBoxTopBottom:
        layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
        break;
    case qy::kHBoxLeftRight:
        layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
        break;
    case qy::kHBoxRightLeft:
        layout = new QBoxLayout(QBoxLayout::RightToLeft,this);
        break;
    case qy::kGrid:
        layout = new QGridLayout(this);
        break;
    case qy::kStacked:
        layout = new QStackedLayout(this);
        break;
    default:
        return ;
    }
    css()->setLayout(type);
    QGraphicsView::setLayout(layout);
    setMargins(QMargins(0,0,0,0));
    setSpacing(0);
}

void HGView::resizeEvent(QResizeEvent *event)
{
    Q_D(HGView);
    d->mFrameStyle->resizeEvent(event);

    QRect rect(QPoint(0, 0), event->size());
    setSceneRect(rect);

    QRect contentRect = d->mFrameStyle->calcClientRect(rect);
    d->mWidget->setGeometry(contentRect);

    QGraphicsView::resizeEvent(event);
    emit resized();
}

bool HGView::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    return d_func()->mFrameStyle->nativeEvent(eventType,message,result);
}

