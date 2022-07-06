#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnExit_clicked();

    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void on_btnMarket_clicked();

    void on_pushButton_clicked();

    void on_btnInfo_clicked();

private:
    Ui::MainWindow *ui;


};

class Stock{
private:
QString symbol,name;
double price,market_cap;
public:
};

class Account{
private:
bool validated;
bool info;
QString name,id,acc_num,shaba,username,password;
double debt,balance,stock_total;
QVector<Stock> stocks;

public:
 Account(QString u,QString p);
 Account();

 void setInfo(QString n,QString i,QString a,QString s);
 void accStock(Stock st);
 void deposit(double val);
 void withdrawal(double val);
 friend class AccountList;
};

class AccountList{
    private:
    QVector<Account> accounts;
    public:
    void addAccount(Account acc);
    bool register_check(QString user);
    bool login_check(Account acc);

};


#endif // MAINWINDOW_H
