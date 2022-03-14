#ifndef QUTER_GLOBAL_H
#define QUTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QUTER_LIBRARY)
#  define QUTER_EXPORT Q_DECL_EXPORT
#else
#  define QUTER_EXPORT Q_DECL_IMPORT
#endif

#endif // QUTER_GLOBAL_H
