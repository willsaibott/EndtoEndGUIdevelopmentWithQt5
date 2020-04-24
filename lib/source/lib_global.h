#pragma once

#include <QtCore/qglobal.h>

#if defined(LIB_LIBRARY)
#  define CMLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CMLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

