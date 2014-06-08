#include "hgcombobox.h"
#include "private/hgwidget_p.h"

class HGComboBoxPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGComboBoxPrivate)
    Q_DECLARE_PUBLIC( HGComboBox )
public:
    HGComboBoxPrivate():
        HGWidgetPrivate()
    {
    }
    ~HGComboBoxPrivate()
    {
    }
};

IMPLEMENT_GITEM_STATIC_CREATE(HGComboBox,HGComboBox)
HGComboBox::HGComboBox(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGComboBoxPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGComboBox);
    setAcceptHoverEvents(true);
    openGItemFlag(ItemClipsChildrenToShape);
    connect(this,SIGNAL(enabledChanged()),SLOT(on_enabledChanged()));
}

HGComboBox::~HGComboBox()
{
}

QSize HGComboBox::iconSize() const
{
    return QSize();
}

void HGComboBox::setIconSize(const QSize &size)
{
    Q_UNUSED(size);
}

bool HGComboBox::isEditable() const
{
    return false;
}

void HGComboBox::setEditable(bool editable)
{
    Q_UNUSED(editable);
}

int HGComboBox::count() const
{
    return 0;
}

void HGComboBox::setMaxCount(int max)
{
    Q_UNUSED(max);
}

int HGComboBox::maxCount() const
{
    return 0;
}

void HGComboBox::setCurrentIndex(int index)
{
    Q_UNUSED(index);
}

void HGComboBox::setCurrentText(const QString &text)
{
    Q_UNUSED(text);
}

int HGComboBox::currentIndex() const
{
    return -1;
}

QString HGComboBox::currentText() const
{
    return QString();
}

QVariant HGComboBox::currentData(int role) const
{
    Q_UNUSED(role);
    return QVariant();
}

QString HGComboBox::itemText(int index) const
{
    Q_UNUSED(index);
    return QString();
}

QIcon HGComboBox::itemIcon(int index) const
{
    Q_UNUSED(index);
    return QIcon();
}

QVariant HGComboBox::itemData(int index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return QVariant();
}

void HGComboBox::insertItem(int index, const QIcon &icon,
                            const QString &text,const QVariant &userData)
{
    Q_UNUSED(index);
    Q_UNUSED(icon);
    Q_UNUSED(text);
    Q_UNUSED(userData);
}

void HGComboBox::insertItems(int index, const QStringList &texts)
{
    Q_UNUSED(index);
    Q_UNUSED(texts);
}

void HGComboBox::insertSeparator(int index)
{
    Q_UNUSED(index);
}

void HGComboBox::removeItem(int index)
{
    Q_UNUSED(index);
}

void HGComboBox::setItemText(int index, const QString &text)
{
    Q_UNUSED(index);
    Q_UNUSED(text);
}

void HGComboBox::setItemIcon(int index, const QIcon &icon)
{
    Q_UNUSED(index);
    Q_UNUSED(icon);
}

void HGComboBox::setItemData(int index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
}
