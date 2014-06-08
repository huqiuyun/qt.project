#include "hgroup.h"
#include "hcore.h"
#include "hgbutton.h"

template <class T>
class HGroupList
{
public:
    HGroupList()
    {
    }

    void add(T* w)
    {
        mList.push_back(w);
    }

    bool remove(T* w)
    {
        return mList.removeOne(w);
    }

    bool find(T* w)
    {
        for (int i = 0; i < mList.size(); ++i)
        {
            T* w1 =  mList[i] ;

            if (w1 == w)
            {
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const
    {
        return mList.size()==0;
    }

    typedef QList<T*> OBJList;
    OBJList mList;
};
typedef HGroupList<HGButton> ButtonGroup;
typedef QMap<QString,ButtonGroup> ButtonMap;

class HGroupPrivate
{
public:
    HGroupPrivate()
    {
    }
    ButtonMap mButtons;
};

IMPLEMENT_OBJECT_STATIC_CREATE(HGroup)
HGroup::HGroup(QObject* parent) :
    QObject(parent),
    d_ptr(new HGroupPrivate())
{
    mObjType = USEOBJTYPE(HGroup);
}

HGroup::HGroup(const HObjectInfo& objinfo,QObject *parent) :
    QObject(parent),
    HObject(objinfo.mStyleId),
    d_ptr(new HGroupPrivate())
{
    mObjType = USEOBJTYPE(HGroup);
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName.latin1());
}

HGroup::~HGroup()
{
    delete d_ptr;
}

void HGroup::addButton(const QString& groupId, HGButton* button)
{
    ButtonMap::iterator iter = d_ptr->mButtons.find(groupId);
    if (iter != d_ptr->mButtons.end()) {
        if (!iter.value().find(button)) {
            iter.value().add(button);
            //todo connect signal
            QObject::connect(button,SIGNAL(stateChanged()),this,SLOT(onButtonStated()));
        }
    }
    else{
        ButtonMap::iterator iter = d_ptr->mButtons.insert(groupId,HGroupList<HGButton>());
        iter.value().add(button);
        //todo connect signal
        QObject::connect(button,SIGNAL(stateChanged()),this,SLOT(onButtonStated()));
    }
}

void HGroup::removeButton(const QString& groupId, HGButton* button)
{
    ButtonMap::iterator iter = d_ptr->mButtons.find(groupId);
    if (iter != d_ptr->mButtons.end()) {

        if (iter.value().remove(button)) {
            //todo disconnect signal
            disconnect(button);
        }
        if (d_ptr->mButtons.isEmpty())
            d_ptr->mButtons.erase(iter);
    }
}

void HGroup::onButtonStated()
{
    const HGButton *button = qobject_cast<const HGButton*>(sender());
    if (!button->checked()) return;

    ButtonMap::iterator iter = d_ptr->mButtons.find(button->groupId());
    if (iter == d_ptr->mButtons.end()) return ;

    ButtonGroup& buttons = iter.value();
    for (int i=0; i< buttons.mList.size();i++) {
        HGButton* b = buttons.mList[i];
        if (b!= button)
            b->setChecked(false);
    }
}
