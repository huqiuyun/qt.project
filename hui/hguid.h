#ifndef HGUID_H
#define HGUID_H

#ifndef DEFINE_HGUID

#define DEFINE_HGUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    const HGuid name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#define EXTERN_HGUID(name) extern const HGuid name;

#endif // DEFINE_HGUID

typedef struct
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
}HGuid;


bool inline compareHGuid(const HGuid* left, const HGuid* right)
{
    bool bEque = (
      (left->Data1 == right->Data1) &&
      (left->Data2 == right->Data2) &&
      (left->Data3 == right->Data3)
      ) ;

    if (!bEque)
    {
        return false;
    }
    for(int i = 0; i < 8 ; i ++ )
    {
        if (left->Data4[i]  != right->Data4[i]) return false;
    }
    return true;
}

inline bool operator == (const HGuid& left,const HGuid& right)
{
    return compareHGuid(&left, &right);
}

inline bool operator != (const HGuid& left,const HGuid& right)
{
    return !compareHGuid(&left, &right);
}

inline bool operator < (const HGuid& left,const HGuid& right)
{
    bool bEque = (
      (left.Data1 < right.Data1) ||
      (left.Data2 < right.Data2) ||
      (left.Data3 < right.Data3)
      ) ;

    if (bEque)
    {
        return true;
    }
    for(int i = 0; i < 8 ; i ++ )
    {
        if (left.Data4[i]  < right.Data4[i]) return true;
    }
    return false;
}

#endif // HGUID_H
