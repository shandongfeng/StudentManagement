/****************************************************************************
** Meta object code from reading C++ file 'teacher_coursetable.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../exe/teacher_coursetable.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teacher_coursetable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSteacher_courseTableENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSteacher_courseTableENDCLASS = QtMocHelpers::stringData(
    "teacher_courseTable"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSteacher_courseTableENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSteacher_courseTableENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSteacher_courseTableENDCLASS_t qt_meta_stringdata_CLASSteacher_courseTableENDCLASS = {
    {
        QT_MOC_LITERAL(0, 19)   // "teacher_courseTable"
    },
    "teacher_courseTable"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSteacher_courseTableENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject teacher_courseTable::staticMetaObject = { {
    QMetaObject::SuperData::link<courseTable::staticMetaObject>(),
    qt_meta_stringdata_CLASSteacher_courseTableENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSteacher_courseTableENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSteacher_courseTableENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<teacher_courseTable, std::true_type>
    >,
    nullptr
} };

void teacher_courseTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *teacher_courseTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *teacher_courseTable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSteacher_courseTableENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return courseTable::qt_metacast(_clname);
}

int teacher_courseTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = courseTable::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
