#ifndef GIANTHACK_H
#define GIANTHACK_H

#include <QtCore/QObject>
#include <QtCore/QString>

#ifndef QT_NO_DEBUG
#define ARGSLOT(fmt, ...) qFlagLocation(QString("1" #fmt QLOCATION).arg(__VA_ARGS__).toStdString().data()
#else
#define ARGSLOT(fmt, ...) QString("1" #fmt).arg(__VA_ARGS__).toStdString().data()
#endif

#endif