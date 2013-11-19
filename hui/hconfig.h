#ifndef HCONFIG_H
#define HCONFIG_H

#include "hctypes.h"
#include "herror.h"
#include <QObject>

#if defined(WIN32)

#ifdef QT_DLL
    #include <QtGlobal>
    #define H_DECL_EXPORT Q_DECL_EXPORT
    #define H_DECL_IMPORT Q_DECL_IMPORT
#else
    #define H_DECL_EXPORT __declspec(dllexport)
    #define H_DECL_IMPORT __declspec(dllimport)
#endif

#else // other platform
    #define H_DECL_EXPORT
    #define H_DECL_IMPORT
#endif

#  ifdef BUILD_HUI
#    define H_API H_DECL_EXPORT
#  else
#    define H_API H_DECL_IMPORT
#  endif // BUILD_HUI

#define hDelete(h)  if (h) { delete (h); (h)= NULL;}
#define hDelete2(h) if (h) { delete[] (h); (h)= NULL;}
#define hfree(v)    if (v) { ::free((void*)v); v = NULL; }

#define H_D(cls) cls##Private* d = d_ptr


#endif // HCONFIG_H
