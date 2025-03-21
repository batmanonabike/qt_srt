#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTSRTLIB_LIB)
#  define QTSRTLIB_EXPORT Q_DECL_EXPORT
# else
#  define QTSRTLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTSRTLIB_EXPORT
#endif
