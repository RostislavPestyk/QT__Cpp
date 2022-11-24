#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bd = QSqlDatabase :: addDatabase("QSQLITE");
    bd.setDatabaseName("./testDB.db");
    if(bd.open())
    {
        qDebug("open");
    }
       else
    {
        qDebug("no open");
    }

    query = new QSqlQuery(bd);
    QString quertToCreateTable="CREATE TABLE Users("
                                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                "name VARCHAR(50) NOT NULL,"
                                "street VARCHAR(50) NOT NULL,"
                                "telephone VARHCAR(15) NOT NULL,"
                                "mail VARCHAR (50) NOT NULL);";


    if(!query->exec(quertToCreateTable)){
        qDebug()<<"Table not created";
    }
        model = new QSqlTableModel(this, bd);
        model ->  setTable("Users");
        model->select();

        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(1, 270);
        ui->tableView->setColumnWidth(2,ui->tableView->width()/4-8);
        ui->tableView->setColumnWidth(3,190);
        ui->tableView->setColumnWidth(4,ui->tableView->width()/4-8);



        ui->tableView->hideColumn(0); // приховати стовбчик id



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_Button_clicked()
{
    QString Name = ui->name->text();
    QString Street = ui->street->text();
    QString Telephone = ui->telephone->text();
    QString Mail = ui->mail->text();


    ui->name->setText("");
    ui->street->setText("");
    ui->telephone->setText("");
    ui->mail->setText("");


    query->prepare("INSERT INTO Users("
                   "name,"
                   "street,"
                   "telephone,"
                   "mail)"
                   "VALUES(?,?,?,?);");


     query->addBindValue(Name);
     query->addBindValue(Street);
     query->addBindValue(Telephone);
     query->addBindValue(Mail);


       if (!query->exec())
       {
           qDebug("error entering data");

       }

       model->select();
       ui->tableView->setModel(model);
      // ui->tableView->hideColumn(0); // приховати стовбчик id



}



void MainWindow::on_buttonDelete_clicked()
{

        model->removeRow(row);

}








void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

     row = index.row();


}




