#ifndef TEACHER_SCORE_H
#define TEACHER_SCORE_H

#include <QWidget>
//引用自定义类
#include "teacher.h"

class teacher_score : public teacher
{
    Q_OBJECT
    const QStringList HFieldName ={"序号","姓名","班级","学号","人工智能","嵌入式","Linux","网络编程","C++高级编程","Python"};
    const QStringList VFieldName;

//数据库
    QSqlDatabase message_db_tmp;
    QSqlDatabase score_db;

//继承teacher虚函数
    void createTable()override;
    int SQLCount()override;
    void derive_SQL_to_model()override;
    void derive_model_to_SQL()override;
    void mySort(const int column,const bool order)override;
//自定义函数
    void modelSort();
public:
    explicit teacher_score(teacher *parent = nullptr);
    ~teacher_score();
signals:

};

#endif // TEACHER_SCORE_H
