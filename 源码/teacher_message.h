#ifndef TEACHER_MESSAGE_H
#define TEACHER_MESSAGE_H

#include <QWidget>
//引用自定义类
#include "teacher.h"

class teacher_message : public teacher
{
    Q_OBJECT
    const QStringList HFieldName ={"序号","姓名","性别","年龄","班级","学号","学院","专业","年级","寝室","籍贯","联系方式"};
    const QStringList VFieldName;

//数据库
    QSqlDatabase message_db;

//继承teacher虚函数
    void createTable()override;
    int SQLCount()override;
    void derive_SQL_to_model()override;
    void derive_model_to_SQL()override;
    void mySort(const int column,const bool order)override;
//自定义函数
    void modelSort();

public:
    explicit teacher_message(teacher *parent = nullptr);
    ~teacher_message();
signals:

};

#endif // TEACHER_MESSAGE_H
