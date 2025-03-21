#ifndef QTSRTLIB_GLOBAL_H
#define QTSRTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTSRTLIB_LIBRARY)
#define QTSRTLIB_EXPORT Q_DECL_EXPORT
#else
#define QTSRTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSRTLIB_GLOBAL_H
