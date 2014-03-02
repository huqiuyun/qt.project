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


#endif // HCONFIG_H
