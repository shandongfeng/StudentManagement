#ifndef STUDENT_SCORE_H
#define STUDENT_SCORE_H

#include <QWidget>
//引用自定义类
#include "student.h"


class student_score : public student
{
    Q_OBJECT

    const QStringList HFieldName;
    const QStringList VFieldName = {"序号","姓名","班级","学号","人工智能","嵌入式","Linux","网络编程","C++高级编程","Python"};

//数据库
    QSqlDatabase score_db;

//继承teacher虚函数
    int SQLCount()override;
    void derive_SQL_to_model(const QString& studentID)override;
    void derive_model_to_SQL(const QString& studentID)override;


public:
    explicit student_score(student *parent = nullptr);
    ~student_score();
signals:

};

#endif // STUDENT_SCORE_H
