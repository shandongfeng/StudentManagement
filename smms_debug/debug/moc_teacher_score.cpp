/****************************************************************************
** Meta object code from reading C++ file 'teacher_score.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../exe/teacher_score.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teacher_score.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSteacher_scoreENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSteacher_scoreENDCLASS = QtMocHelpers::stringData(
    "teacher_score"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSteacher_scoreENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSteacher_scoreENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSteacher_scoreENDCLASS_t qt_meta_stringdata_CLASSteacher_scoreENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13)   // "teacher_score"
    },
    "teacher_score"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSteacher_scoreENDCLASS[] = {

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

Q_CONSTINIT const QMetaObject teacher_score::staticMetaObject = { {
    QMetaObject::SuperData::link<teacher::staticMetaObject>(),
    qt_meta_stringdata_CLASSteacher_scoreENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSteacher_scoreENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSteacher_scoreENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<teacher_score, std::true_type>
    >,
    nullptr
} };

void teacher_score::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *teacher_score::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *teacher_score::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSteacher_scoreENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return teacher::qt_metacast(_clname);
}

int teacher_score::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = teacher::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
