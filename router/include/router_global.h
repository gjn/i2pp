/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#ifndef I2PP_ROUTER_GLOBAL_H
#define I2PP_ROUTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(I2PP_ROUTER_LIBRARY)
#  define I2PP_ROUTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define I2PP_ROUTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // I2PP_ROUTER_GLOBAL_H
