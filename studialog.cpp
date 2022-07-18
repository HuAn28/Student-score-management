#include "studialog.h"
#include "ui_studialog.h"

StuDialog::StuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StuDialog)
{
    ui->setupUi(this);
    createDB();
    createTable();
    queryTable();
}

StuDialog::~StuDialog()
{
    delete ui;
}

// 创建数据库
void StuDialog::createDB()
{
    // 添加数据库驱动库
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库名字(文件名)
    db.setDatabaseName("student.db");
    // 打开数据库
    if (db.open() == true) {
        qDebug() << "创建/打开数据库成功！";
    }
    else {
        qDebug() << "创建/打开数据库失败！";
    }
}

// 创建数据表
void StuDialog::createTable()
{
    QSqlQuery query;
    QString str = QString("CREATE TABLE student ("
                          "id INT PRIMARY KEY NOT NULL,"
                          "name TEXT NOT NULL,"
                          "score REAL NOT NULL)");
    // 执行sql语句失败后打印失败语句，成功则不作处理
    if(query.exec(str) == false) {
        qDebug() << str;
    }
}

// 查询
void StuDialog::queryTable()
{
    QString str = QString("SELECT * FROM student");
    model.setQuery(str);
    ui->tableView->setModel(&model);
}

// 插入操作对应的槽函数
void StuDialog::on_insert_button_2_clicked()
{
    QSqlQuery query;
    int id = ui->id_edit->text().toInt();
    if(id == 0) {
        QMessageBox::critical(this, "Error", "ID输入错误！");
        return;
    }
    QString name = ui->name_edit->text();
    if(name == "") {
        QMessageBox::critical(this, "Error", "姓名输入错误！");
        return;
    }
    double score = ui->score_edit->text().toDouble();
    if(score < 0 || score > 100) {
        QMessageBox::critical(this, "Error", "分数输入错误！");
        return;
    }
    QString str = QString("INSERT INTO student VALUES(%1, '%2', %3)").arg(id).arg(name).arg(score);
    if(query.exec(str) == false) {
        qDebug() << str;
    }
    else {
        qDebug() << "插入数据成功！";
        queryTable();
    }
}

// 删除操作对应的槽函数:根据ID删除一条数据
void StuDialog::on_delete_button_clicked()
{
    QSqlQuery query;
    int id = ui->id_edit->text().toInt();
    QString str = QString("DELETE FROM student WHERE id = %1").arg(id);
    if(query.exec(str) == false) {
        qDebug() << str;
    }
    else {
        qDebug() << "删除数据成功！";
        queryTable();
    }
}

// 修改操作对应的槽函数:根据ID修改成绩
void StuDialog::on_update_button_clicked()
{
    QSqlQuery query;
    int id = ui->id_edit->text().toInt();
    double score = ui->score_edit->text().toDouble();
    QString str = QString("UPDATE student SET score = %1 WHERE id = %2").arg(score).arg(id);
    if(query.exec(str) == false) {
        qDebug() << str;
    }
    else {
        qDebug() << "修改数据成功！";
        queryTable();
    }
}

// 排序操作对应的槽函数
void StuDialog::on_sort_button_clicked()
{
    // 获取排序列名
    QString value = ui->value_comboBox->currentText();
    // 获取排序方式
    QString condition;
    if(ui->cond_comboBox->currentIndex() == 0) {
        condition = "ASC";  // 升序
    }
    else {
        condition = "DESC";  // 降序
    }
    QString str = QString("SELECT * FROM student ORDER BY %1 %2").arg(value).arg(condition);

    // 查询和显示
    model.setQuery(str);
    ui->tableView->setModel(&model);
}
