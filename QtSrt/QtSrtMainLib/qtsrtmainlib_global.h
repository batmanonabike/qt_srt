#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTSRTMAINLIB_LIB)
#  define QTSRTMAINLIB_EXPORT Q_DECL_EXPORT
# else
#  define QTSRTMAINLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTSRTMAINLIB_EXPORT
#endif
