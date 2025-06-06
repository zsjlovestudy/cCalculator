#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLayout>
#include <QTextBrowser>
#include <stack.h>
#include <math.h>
#include <QTabWidget>
#include <Operator.h>
#include <OperatorFactory.h>
#include <QGraphicsOpacityEffect>

class calculator : public QDialog
{
    Q_OBJECT

private:
    Stack<double> m_num; // 数字栈
    Stack<unique_ptr<Operator>> m_opr; // 运算符栈
    double readNum(string::iterator &it); 	// 读取操作数
    bool isNum(string::iterator &c) { // 判断字符是否为数字
        return (*c >= '0'&&*c <= '9' )|| *c == '.'||*c=='p'||*c=='i';
    }
        double doIt(QString &question);
public:
    calculator(QWidget *parent = nullptr);
    ~calculator();
    int precedence(const QString& s) const;//获取优先级
    string readsin(string::iterator& it);
    bool issin(string::iterator& c) const {
        return *c >= 'a' && *c <= 'z';
    }

private:

    QString qstr;
    QString showstr;
    QString oldshow;
    QString bstr;
    int sign;
    int finish_sign;
    int bsign;
    int errsign;
    int perrsign;
    //void history();
    void initUI();
    void initSLOTS();
    void calculate();

    //数字键

    QPushButton *num_0;
    QPushButton *num_1;
    QPushButton *num_2;
    QPushButton *num_3;
    QPushButton *num_4;
    QPushButton *num_5;
    QPushButton *num_6;
    QPushButton *num_7;
    QPushButton *num_8;
    QPushButton *num_9;
    QPushButton *pi;
    QPushButton *dot;
    
    //操作符
    QPushButton *clearh;
    QPushButton *lbracket;
    QPushButton *rbracket;
    QPushButton *msin;
    QPushButton *mcos;
    QPushButton *mtan;
    QPushButton *mod;
    QPushButton *power;
    QPushButton *mul;
    QPushButton *div;
    QPushButton *add;
    QPushButton *sub;
    QPushButton *zero;
    QPushButton *back;
    QPushButton *psqrt;
    QPushButton *equ;
    QPushButton *change;
    QPushButton *mln;
    QPushButton *mlog;
    QPushButton *em;
    QPushButton *masin;
    QPushButton *macos;
    QPushButton *matan;
    QPushButton *fact;
    QPushButton *rec;
    //test
    QPushButton *num_02;
    QPushButton *num_12;
    QPushButton *num_22;
    QPushButton *num_32;
    QPushButton *num_42;
    QPushButton *num_52;
    QPushButton *num_62;
    QPushButton *num_72;
    QPushButton *num_82;
    QPushButton *num_92;
    QPushButton *lbracket2;
    QPushButton *rbracket2;
    QPushButton *mul2;
    QPushButton *div2;
    QPushButton *add2;
    QPushButton *sub2;
    QPushButton *zero2;
    QPushButton *back2;
    QPushButton *dot2;
    QPushButton *equ2;


    //界面
    QTextBrowser *showText;
    QTextBrowser *historyText;
    QTabWidget *tab;
    QWidget *widget1;
    QWidget *widget2;
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
    void clickedmod();
    void clickeddot();
    void clickedpower();
    void clickedsqrt();
    void clickedequ();
    void clickedback();
    void clickedzero();
    void clickedleft();
    void clickedright();
    void clickedchange();
    void clickedln();
    void clickedlog();
    void clickedrec();
    void clickedfact();
    void clickedem();
    void clickedclearh();
    void clickedsin();
    void clickedcos();
    void clickedtan();
    void clickedmasin();
    void clickedmacos();
    void clickedmatan();

    //test

    void clicked02();
    void clicked12();
    void clicked22();
    void clicked32();
    void clicked42();
    void clicked52();
    void clicked62();
    void clicked72();
    void clicked82();
    void clicked92();
    void clickedmul2();
    void clickeddiv2();
    void clickedadd2();
    void clickedsub2();
    void clickeddot2();
    void clickedequ2();
    void clickedback2();
    void clickedzero2();
    void clickedleft2();
    void clickedright2();
};
#endif // CALCULATOR_H
