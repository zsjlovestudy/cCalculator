#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //载入样式表
    QFile file(":/qss/psblack.css");
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }

    ui->equ->setStyleSheet("background: rgb(40,90,90)");
    ui->num_0->setStyleSheet("background: rgb(50,50,50)");
    ui->num_1->setStyleSheet("background: rgb(50,50,50)");
    ui->num_2->setStyleSheet("background: rgb(50,50,50)");
    ui->num_3->setStyleSheet("background: rgb(50,50,50)");
    ui->num_4->setStyleSheet("background: rgb(50,50,50)");
    ui->num_5->setStyleSheet("background: rgb(50,50,50)");
    ui->num_6->setStyleSheet("background: rgb(50,50,50)");
    ui->num_7->setStyleSheet("background: rgb(50,50,50)");
    ui->num_8->setStyleSheet("background: rgb(50,50,50)");
    ui->num_9->setStyleSheet("background: rgb(50,50,50)");
    ui->dot->setStyleSheet("background: rgb(50,50,50)");

    connect(ui->num_1, SIGNAL(clicked(bool)), this, SLOT(clicked1()));
    connect(ui->num_2, SIGNAL(clicked(bool)), this, SLOT(clicked2()));
    connect(ui->num_3, SIGNAL(clicked(bool)), this, SLOT(clicked3()));
    connect(ui->num_4, SIGNAL(clicked(bool)), this, SLOT(clicked4()));
    connect(ui->num_5, SIGNAL(clicked(bool)), this, SLOT(clicked5()));
    connect(ui->num_6, SIGNAL(clicked(bool)), this, SLOT(clicked6()));
    connect(ui->num_7, SIGNAL(clicked(bool)), this, SLOT(clicked7()));
    connect(ui->num_8, SIGNAL(clicked(bool)), this, SLOT(clicked8()));
    connect(ui->num_9, SIGNAL(clicked(bool)), this, SLOT(clicked9()));
    connect(ui->num_0, SIGNAL(clicked(bool)), this, SLOT(clicked0()));
    connect(ui->pi, SIGNAL(clicked(bool)), this, SLOT(clickedpi()));
    connect(ui->e, SIGNAL(clicked(bool)), this, SLOT(clickedE()));
    connect(ui->lbracket, SIGNAL(clicked(bool)), this, SLOT(clickedLeft()));
    connect(ui->rbracket, SIGNAL(clicked(bool)), this, SLOT(clickedRight()));
    connect(ui->mln, SIGNAL(clicked(bool)), this, SLOT(clickedln()));
    connect(ui->mlog, SIGNAL(clicked(bool)), this, SLOT(clickedlog()));
    connect(ui->rec, SIGNAL(clicked(bool)), this, SLOT(clickedrec()));
    connect(ui->fact, SIGNAL(clicked(bool)), this, SLOT(clickedfact()));
    connect(ui->mexp, SIGNAL(clicked(bool)), this, SLOT(clickedmexp()));
    connect(ui->clcH, SIGNAL(clicked(bool)), this, SLOT(clickedclcH()));
    connect(ui->mul, SIGNAL(clicked(bool)), this, SLOT(clickedmul()));
    connect(ui->div, SIGNAL(clicked(bool)), this, SLOT(clickeddiv()));
    connect(ui->add, SIGNAL(clicked(bool)), this, SLOT(clickedadd()));
    connect(ui->sub, SIGNAL(clicked(bool)), this, SLOT(clickedsub()));
    connect(ui->mod, SIGNAL(clicked(bool)), this, SLOT(clickedMod()));
    connect(ui->dot, SIGNAL(clicked(bool)), this, SLOT(clickeddot()));
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(clickedPower()));
    connect(ui->psqrt, SIGNAL(clicked(bool)), this, SLOT(clickedSqrt()));
    connect(ui->equ, SIGNAL(clicked(bool)), this, SLOT(clickedEqu()));
    connect(ui->back, SIGNAL(clicked(bool)), this, SLOT(clickedback()));
    connect(ui->clc, SIGNAL(clicked(bool)), this, SLOT(clickedclc()));
    connect(ui->msin, SIGNAL(clicked(bool)), this, SLOT(clickedsin()));
    connect(ui->mcos, SIGNAL(clicked(bool)), this, SLOT(clickedcos()));
    connect(ui->mtan, SIGNAL(clicked(bool)), this, SLOT(clickedtan()));
    connect(ui->masin, SIGNAL(clicked(bool)), this, SLOT(clickedmasin()));
    connect(ui->macos, SIGNAL(clicked(bool)), this, SLOT(clickedmacos()));
    connect(ui->matan, SIGNAL(clicked(bool)), this, SLOT(clickedmatan()));

    //按一下clc键执行栈和变量初始化
    clickedclc();
}

MainWindow::~MainWindow()
{
    delete ui;
}





/***************** 按键槽函数 ******************/

void MainWindow::clicked1()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="1";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked2()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="2";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked3()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="3";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked4()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="4";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked5()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="5";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked6()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="6";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked7()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="7";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked8()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="8";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked9()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="9";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clicked0()
{
    if(finishFlag==1)
        clickedclc();

    QString temp="0";
    qstr+=temp;
    showstr+=temp;
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clickeddot()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
        qstr += ".";
        showstr += ".";
    }
    //只有前一个字符是数字时，才能插入"."
    auto lastInput = showstr.toStdString().end()-1;
    if(isNum(lastInput))
    {
        qstr += ".";
        showstr += ".";
    }
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedpi()
{
    if(finishFlag==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
    //如果前面是数字，自动添加一个"*"
    auto lastInput = showstr.toStdString().end()-1;
    if(isNum(lastInput))
    {
        qstr += "*";
        showstr += "*";
    }

    qstr += "(pi)";
    showstr += "π";
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedE()
{
    if(finishFlag==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
    //如果前面是数字，自动添加一个"*"
    auto lastInput = showstr.toStdString().end()-1;
    if(isNum(lastInput))
    {
        qstr += "*";
        showstr += "*";
    }

    qstr += "(e)";
    showstr += "e";
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedmul()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    qstr += "*";
    showstr += "*";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickeddiv()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    qstr += "/";
    showstr += "/";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedadd()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    qstr += "+";
    showstr += "+";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedsub()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    QString temp="-";
    qstr += "-";
    showstr += "-";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedMod()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    qstr += "%";
    showstr += "%";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedPower()
{
    if(lastQstrLength!=0)
    {
        qstr.chop(lastQstrLength);
        showstr.chop(lastShowstrLength);
    }

    qstr += "^";
    showstr += "^";
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedSqrt()
{
    if(finishFlag==1)
    {
        qstr.push_front("sqrt");
        showstr.push_front("√");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*sqrt";
            showstr += "*√";
            lastQstrLength = 5;
            lastShowstrLength = 2;
        }
        else
        {
            qstr += "sqrt";
            showstr += "√";
            lastQstrLength = 4;
            lastShowstrLength = 1;
        }

    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedclc()
{
    //清空栈和变量
    qstr.clear();
    showstr.clear();
    m_num.clear();
    m_opr.clear();
    //向符号栈底送入"#"
    m_opr.push(make_unique<Hash>());

    lastQstrLength = 0;
    lastShowstrLength = 0;
    ui->showText->setText("0");
}
void MainWindow::clickedclcH()
{
    ui->historyText->clear();
}
void MainWindow::clickedrec()
{
    qstr += "rec";
    showstr += "^-1";
    lastQstrLength = 3;
    lastShowstrLength = 3;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedln()
{
    if(finishFlag==1)
    {
        showstr.push_front("ln");
        qstr.push_front("ln");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*ln";
            showstr += "*ln";
            lastQstrLength = 3;
            lastShowstrLength = 3;
        }
        else
        {
            qstr += "ln";
            showstr += "ln";
            lastQstrLength = 2;
            lastShowstrLength = 2;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedlog()
{
    if(finishFlag==1)
    {
        showstr.push_front("log");
        qstr.push_front("log");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*log";
            showstr += "*log";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
        else
        {
            qstr += "log";
            showstr += "log";
            lastQstrLength = 3;
            lastShowstrLength = 3;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedfact()
{
    if(finishFlag==1)
    {
        showstr.push_back("!");
        qstr.push_front("!");
    }
    else
    {
        if(lastQstrLength!=0)
        {
            qstr.chop(lastQstrLength);
            showstr.chop(lastShowstrLength);
        }
        qstr += "!";
        showstr += "!";
    }
    lastQstrLength = 1;
    lastShowstrLength = 1;
    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedmexp()
{
    if(finishFlag==1)
    {
        finishFlag=0;
        qstr.push_front("mexp");
        showstr.push_front("e^");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*mexp";
            showstr += "*e^";
            lastQstrLength = 5;
            lastShowstrLength = 3;
        }
        else
        {
            qstr += "mexp";
            showstr += "e^";
            lastQstrLength = 4;
            lastShowstrLength = 2;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedsin()
{
    if(finishFlag==1)
    {
        showstr.push_front("sin");
        qstr.push_front("sin");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*sin";
            showstr += "*sin";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
        else
        {
            qstr += "sin";
            showstr += "sin";
            lastQstrLength = 3;
            lastShowstrLength = 3;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedcos()
{
    if(finishFlag==1)
    {
        showstr.push_front("cos");
        qstr.push_front("cos");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*cos";
            showstr += "*cos";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
        else
        {
            qstr += "cos";
            showstr += "cos";
            lastQstrLength = 3;
            lastShowstrLength = 3;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedtan()
{
    if(finishFlag==1)
    {
        showstr.push_front("tan");
        qstr.push_front("tan");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*tan";
            showstr += "*tan";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
        else
        {
            qstr += "tan";
            showstr += "tan";
            lastQstrLength = 3;
            lastShowstrLength = 3;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedmasin()
{
    if(finishFlag==1)
    {
        showstr.push_front("asin");
        qstr.push_front("asin");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*asin";
            showstr += "*asin";
            lastQstrLength = 5;
            lastShowstrLength = 5;
        }
        else
        {
            qstr += "asin";
            showstr += "asin";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedmacos()
{
    if(finishFlag==1)
    {
        showstr.push_front("acos");
        qstr.push_front("acos");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*acos";
            showstr += "*acos";
            lastQstrLength = 5;
            lastShowstrLength = 5;
        }
        else
        {
            qstr += "acos";
            showstr += "acos";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedmatan()
{
    if(finishFlag==1)
    {
        showstr.push_front("atan");
        qstr.push_front("atan");
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*atan";
            showstr += "*atan";
            lastQstrLength = 5;
            lastShowstrLength = 5;
        }
        else
        {
            qstr += "atan";
            showstr += "atan";
            lastQstrLength = 4;
            lastShowstrLength = 4;
        }
    }

    finishFlag=0;
    ui->showText->setText(showstr);
}
void MainWindow::clickedback()
{
    if(finishFlag==1)
    {
        finishFlag=0;
        showstr.clear();
        qstr.clear();
    }
    else if(showstr.right(2)=="π")
    {
        showstr.chop(1);
        qstr.chop(4);
    }
    else if(showstr.right(2)=="e")
    {
        showstr.chop(1);
        qstr.chop(3);
    }
    else if(showstr.right(2)=="√")
    {
        showstr.chop(1);
        qstr.chop(4);
    }
    else if(showstr.right(3)=="^-1")
    {
        showstr.chop(3);
        qstr.chop(2);
    }
    else if(showstr.right(3)=="sin"||showstr.right(3)=="cos"||showstr.right(3)=="tan"||showstr.right(3)=="log")
    {
        showstr.chop(3);
        qstr.chop(3);
    }
    else if(showstr.right(4)=="asin"||showstr.right(3)=="acos"||showstr.right(3)=="atan")
    {
        showstr.chop(4);
        qstr.chop(4);
    }
    else if(showstr.right(2)=="ln")
    {
        showstr.chop(2);
        qstr.chop(2);
    }
    else if(showstr.right(2)=="e^")
    {
        showstr.chop(2);
        qstr.chop(4);
    }
    else if(showstr.right(1)==".")
    {
        showstr.chop(1);
        qstr.chop(1);
    }
    else
    {
        showstr.chop(1);
        qstr.chop(1);
    }
    ui->showText->setText(showstr);
    lastQstrLength = 0;
    lastShowstrLength = 0;
}
void MainWindow::clickedEqu()
{
    qstr += "=";
    showstr += "=";
    ui->showText->setText(showstr);
    finishFlag=1;
    lastQstrLength = 0;
    lastShowstrLength = 0;
    //doIt(qstr);
}
void MainWindow::clickedLeft()
{
    if(finishFlag==1)
    {
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    else
    {
        //如果前面是数字，自动添加一个"*"
        auto lastInput = showstr.toStdString().end()-1;
        if(isNum(lastInput))
        {
            qstr += "*";
            showstr += "*";
        }
    }
    qstr += "(";
    showstr += "(";
    ui->showText->setText(showstr);
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
}
void MainWindow::clickedRight()
{
    if(finishFlag==1)
    {
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr += ")";
    showstr += ")";
    ui->showText->setText(showstr);
    finishFlag=0;
    lastQstrLength = 0;
    lastShowstrLength = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case(Qt::Key_Backspace):
        clickedback();
        break;
    case(Qt::Key_Delete):
        clickedclc();
        break;
    case(Qt::Key_Escape):
        clickedclc();
        break;
    case(Qt::Key_Enter):
        clickedEqu();
        break;
    case(Qt::Key_Return):
        clickedEqu();
        break;

    case(Qt::Key_Plus)://+
        clickedadd();
        break;
    case(Qt::Key_Minus)://-
        clickedsub();
        break;
    case(Qt::Key_Asterisk)://*
        clickedmul();
        break;
    case(Qt::Key_Slash)://除
        clickeddiv();
        break;

    case(Qt::Key_Percent)://%
        clickedMod();
        break;
    case(Qt::Key_AsciiCircum)://^
        clickedPower();
        break;
    case(Qt::Key_ParenLeft)://(
        clickedLeft();
        break;
    case(Qt::Key_ParenRight)://)
        clickedRight();
        break;
    case(Qt::Key_exclamdown)://"!"
        clickedfact();
        break;

    case(Qt::Key_0):
        clicked0();
        break;
    case(Qt::Key_1):
        clicked1();
        break;
    case(Qt::Key_2):
        clicked2();
        break;
    case(Qt::Key_3):
        clicked3();
        break;
    case(Qt::Key_4):
        clicked4();
        break;
    case(Qt::Key_5):
        clicked5();
        break;
    case(Qt::Key_6):
        clicked6();
        break;
    case(Qt::Key_7):
        clicked7();
        break;
    case(Qt::Key_8):
        clicked8();
        break;
    case(Qt::Key_9):
        clicked9();
        break;
    case(Qt::Key_Period):
        clickeddot();
        break;
    }
}
