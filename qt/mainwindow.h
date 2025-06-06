#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QKeyEvent>
#include <stack.h>
#include <math.h>
#include <Operator.h>
#include <factory.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int precedence(const QString& s) const;//获取优先级
    string readSig(string::iterator& it);
    bool isSig(string::iterator& c) const {
        return *c >= 'a' && *c <= 'z';
    }

private:
    Ui::MainWindow *ui;

    Stack<double> m_num; // 数字栈
    Stack<unique_ptr<Operator>> m_opr; // 运算符栈
    double readNum(string::iterator &it); 	// 读取操作数
    bool isNum(string::iterator &c) { // 判断字符是否为数字
        return (*c >= '0'&&*c <= '9' ) || *c == '.' || *c=='p' || *c=='i' || *c=='e';
    }
    double doIt(QString &question);

    QString qstr;
    QString showstr;
    QString oldshow;
    int finishFlag;
    int lastQstrLength,lastShowstrLength;
    void initSLOTS();
    void calculate();

private slots:
    void clicked0();
    void clicked1();
    void clicked2();
    void clicked3();
    void clicked4();
    void clicked5();
    void clicked6();
    void clicked7();
    void clicked8();
    void clicked9();
    void clickedpi();
    void clickedmul();
    void clickeddiv();
    void clickedadd();
    void clickedsub();
    void clickedMod();
    void clickeddot();
    void clickedPower();
    void clickedSqrt();
    void clickedEqu();
    void clickedback();
    void clickedclc();
    void clickedLeft();
    void clickedRight();
    void clickedE();
    void clickedln();
    void clickedlog();
    void clickedrec();
    void clickedfact();
    void clickedmexp();
    void clickedclcH();
    void clickedsin();
    void clickedcos();
    void clickedtan();
    void clickedmasin();
    void clickedmacos();
    void clickedmatan();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
};
#endif // MAINWINDOW_H
