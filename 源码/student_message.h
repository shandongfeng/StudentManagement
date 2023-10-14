#ifndef STUDENT_MESSAGE_H
#define STUDENT_MESSAGE_H

#include <QWidget>
//引用自定义类
#include "student.h"


class student_message : public student
{
    Q_OBJECT
    const QStringList HFieldName;
    const QStringList VFieldName = {"序号","姓名","性别","年龄","班级","学号","学院","专业","年级","寝室","籍贯","联系方式"};

//数据库
    QSqlDatabase message_db;

//继承teacher虚函数    
    int SQLCount()override;
    void derive_SQL_to_model(const QString& studentID)override;
    void derive_model_to_SQL(const QString& studentID)override;

public:
    explicit student_message(student *parent = nullptr);
    ~student_message();
signals:

};

#endif // STUDENT_MESSAGE_H
