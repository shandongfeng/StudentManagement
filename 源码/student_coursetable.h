#ifndef STUDENT_COURSETABLE_H
#define STUDENT_COURSETABLE_H

#include <QWidget>
//引用自定义类
#include "coursetable.h"


class student_courseTable : public courseTable
{
    Q_OBJECT

    const QStringList HFieldName ={"周一","周二","周三","周四","周五","周六","周日"};
    const QStringList VFieldName ={"早自习","第一、二节","第三、四节","第五、六节","第七、八节","晚自习"};

//数据库
    //QSqlDatabase courseTable_db;

//继承teacher虚函数
    int SQLCount()override;
    void derive_SQL_to_model()override;
    void derive_model_to_SQL()override;


public:
    explicit student_courseTable(courseTable *parent = nullptr);
    ~student_courseTable();
signals:

};

#endif // STUDENT_COURSETABLE_H
