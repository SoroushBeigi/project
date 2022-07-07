#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


Account::Account(QString u,QString p): username(u),password(p){

    validated=false;
    info=false;
    debt=0; balance=0;stock_total=0;
}
Account::Account(){}
void Account::setInfo(QString n,QString i,QString a,QString s){
    name=n; id=i; acc_num=a; shaba=s;
    validated=true;
}
void Account::accStock(Stock st){
    stocks.push_back(st);
}
void Account::deposit(double val){
    if(validated) balance+=val;
   // else cout<<"Please enter your info"<<endl;
}
void Account::withdrawal(double val){
    if(validated) balance-=val;
    //else cout<<"Please enter your info"<<endl;
}


void AccountList::addAccount(Account acc){
    accounts.push_back(acc);
}

bool AccountList::register_check(QString user){
    for(int i=0; i<accounts.size();i++){
        if(user==accounts[i].username){
            return false;
        }
    }
    return true;
}
bool AccountList::login_check(Account acc){
    for(int i=0; i<accounts.size();i++){
        if(acc.username==accounts[i].username && acc.password==accounts[i].password){
            return true;
        }
    }
    return false;
}

AccountList accList;
bool isLoggedIn=false;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame2->hide();
    ui->frame3->hide();
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnExit_clicked(){
    QApplication::quit();
}


void MainWindow::on_btnRegister_clicked(){
    QString user=ui->etUser->text();
    QString pass=ui->etPass->text();

    if(accList.register_check(user)){
        Account acc(user,pass);
        accList.addAccount(acc);
        QMessageBox::information(this,"Congratulations!","Your Account is Created.");
    }else{
        QMessageBox::information(this,"Error!","This username is already used! please choose another username.");
    }
    ui->etUser->setText("");
    ui->etPass->setText("");
}


void MainWindow::on_btnLogin_clicked(){
    QString user=ui->etUser->text();
    QString pass=ui->etPass->text();
    Account acc(user,pass);
    if(accList.login_check(acc)){
                    QMessageBox::information(this,"","You're Logged in!");
                    isLoggedIn=true;
                    QString welcomeMSG= "Welcome %1!";
                    ui->label1->setText(welcomeMSG.arg(user));
                    ui->frame->hide();
                    ui->frame2->show();
                    ui->frame3->show();
      }else{
                QMessageBox::information(this,"Error!","Username or Password is wrong! please enter them again.");
           }
    ui->etUser->setText("");
    ui->etPass->setText("");

}


void MainWindow::on_btnMarket_clicked(){
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_clicked(){
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_btnInfo_clicked()
{
    QMessageBox::information(this,"","Information Added.");
    ui->btnInfo->setText("Edit Info");
}

