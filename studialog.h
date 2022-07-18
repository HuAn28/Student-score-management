#ifndef STUDIALOG_H
#define STUDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class StuDialog; }
QT_END_NAMESPACE

class StuDialog : public QDialog
{
    Q_OBJECT

public:
    StuDialog(QWidget *parent = nullptr);
    ~StuDialog();

private:
    // 创建数据库
    void createDB();
    // 创建数据表
    void createTable();
    // 查询
    void queryTable();

private slots:
    // 插入操作对应的槽函数
    void on_insert_button_2_clicked();
    // 删除操作对应的槽函数
    void on_delete_button_clicked();
    // 修改操作对应的槽函数
    void on_update_button_clicked();
    // 排序操作对应的槽函数
    void on_sort_button_clicked();

private:
    Ui::StuDialog *ui;
    QSqlDatabase db;  // 建立Qt和数据库链接
    QSqlQueryModel model;  // 保存结果集
};
#endif // STUDIALOG_H
