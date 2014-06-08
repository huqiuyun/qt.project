#ifndef HGCOMBOBOX_H
#define HGCOMBOBOX_H

#include "hgwidget.h"
#include <QIcon>

class HGComboBoxPrivate;
class H_API HGComboBox : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGComboBox )
    Q_DECLARE_PRIVATE( HGComboBox )

public:
    Q_PROPERTY( int maxCount READ maxCount WRITE setMaxCount )
    Q_PROPERTY( int currentIndex READ currentIndex WRITE setCurrentIndex )
    Q_PROPERTY( QString currentText READ currentText WRITE setCurrentText)
    Q_PROPERTY( QSize iconSize READ iconSize WRITE setIconSize )
    Q_PROPERTY( bool editable READ isEditable WRITE setEditable )

public:
    explicit HGComboBox(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGComboBox();

    DECLARE_GITEM_STATIC_CREATE(HGComboBox);
public:
    QSize iconSize() const;
    void setIconSize(const QSize &size);

    bool isEditable() const;
    void setEditable(bool editable);

    int count() const;
    void setMaxCount(int max);
    int maxCount() const;

    int currentIndex() const;
    void setCurrentIndex(int index);

    void setCurrentText(const QString &text);
    QString currentText() const;

    QVariant currentData(int role = Qt::UserRole) const;

    QString itemText(int index) const;
    QIcon itemIcon(int index) const;
    QVariant itemData(int index, int role = Qt::UserRole) const;

    Q_INVOKABLE inline void addItem(const QString &atext, const QVariant &auserData=QVariant());
    Q_INVOKABLE inline void addItem(const QIcon &aicon, const QString &atext, const QVariant &auserData=QVariant());
    Q_INVOKABLE inline void addItems(const QStringList &texts);
    Q_INVOKABLE inline void insertItem(int aindex, const QString &atext, const QVariant &auserData = QVariant());

    Q_INVOKABLE void insertItem(int index, const QIcon &icon, const QString &text,const QVariant &userData = QVariant());
    Q_INVOKABLE void insertItems(int index, const QStringList &texts);
    Q_INVOKABLE void insertSeparator(int index);

    Q_INVOKABLE void removeItem(int index);

    Q_INVOKABLE void setItemText(int index, const QString &text);
    Q_INVOKABLE void setItemIcon(int index, const QIcon &icon);
    Q_INVOKABLE void setItemData(int index, const QVariant &value, int role = Qt::UserRole);
protected:
};

inline void HGComboBox::addItem(const QString &atext, const QVariant &auserData)
{ insertItem(count(), atext, auserData); }

inline void HGComboBox::addItem(const QIcon &aicon, const QString &atext, const QVariant &auserData)
{ insertItem(count(), aicon, atext, auserData); }

inline void HGComboBox::addItems(const QStringList &texts)
{ insertItems(count(), texts); }

inline void HGComboBox::insertItem(int aindex, const QString &atext, const QVariant &auserData)
{ insertItem(aindex, QIcon(), atext, auserData); }

#endif // HGCOMBOBOX_H
