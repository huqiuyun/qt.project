#ifndef HCONFIG_H
#define HCONFIG_H

#include "hctypes.h"
#include "herror.h"
#include <QObject>
#include <QtGlobal>

#define H_DECL_EXPORT Q_DECL_EXPORT
#define H_DECL_IMPORT Q_DECL_IMPORT

# ifdef HUI_DLL

#   ifdef BUILD_HUI
#     define H_API H_DECL_EXPORT
#   else
#     define H_API H_DECL_IMPORT
#   endif // BUILD_HUI

# else
#    define H_API
#endif // HUI_DLL

#define hDelete(h)  if (h) { delete (h); (h)= NULL;}
#define hDelete2(h) if (h) { delete[] (h); (h)= NULL;}
#define hfree(v)    if (v) { ::free((void*)v); v = NULL; }

#define H_D(cls) cls##Private* d = d_ptr

#define H_UNUSED2(v1,v2) Q_UNUSED(v1);Q_UNUSED(v2);
#define H_UNUSED3(v1,v2,v3) H_UNUSED2(v1,v2);Q_UNUSED(v3);
#define H_UNUSED4(v1,v2,v3,v4) H_UNUSED3(v1,v2,v3); Q_UNUSED(v4);

#endif // HCONFIG_H
