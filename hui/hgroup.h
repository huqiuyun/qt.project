#ifndef HGROUP_H
#define HGROUP_H

#include "hbase.h"

class HGButton;
class HGroupPrivate;
class H_API HGroup : public QObject, public HObject
{
    Q_OBJECT
public:
    explicit HGroup(QObject* parent= 0);
    explicit HGroup(const HObjectInfo& objinfo,QObject* parent= 0);
    virtual ~HGroup();

    DECLARE_OBJECT_STATIC_CREATE(HGroup);
public:
    void addButton(const QString& groupId,  HGButton* button);
    void removeButton(const QString& groupId, HGButton* button);

private slots:
    void onButtonStated();

private:
    HGroupPrivate* d_ptr;
};

#endif // HGROUP_H
