#include "calculator.h"

calculator::calculator(QWidget *parent)
    : QDialog(parent)
{
    finish_sign=0;
    m_opr.push(make_unique<Hash>());
    initUI();
    initSLOTS();
}
void calculator::initUI()
{
    this -> setWindowTitle("计算器20171004306");
    //数字pi.
    num_0 = new QPushButton(tr("0"));
    num_1 = new QPushButton(tr("1"));
    num_2 = new QPushButton(tr("2"));
    num_3 = new QPushButton(tr("3"));
    num_4 = new QPushButton(tr("4"));
    num_5 = new QPushButton(tr("5"));
    num_6 = new QPushButton(tr("6"));
    num_7 = new QPushButton(tr("7"));
    num_8 = new QPushButton(tr("8"));
    num_9 = new QPushButton(tr("9"));
    pi  = new QPushButton(tr("pi"));
    dot = new QPushButton(tr("."));
    //操作符
    clearh = new QPushButton(tr("CHistory"));
    lbracket = new QPushButton(tr("("));
    rbracket = new QPushButton(tr(")"));
    msin = new QPushButton(tr("sin"));
    mcos = new QPushButton(tr("cos"));
    mtan = new QPushButton(tr("tan"));
    mod  = new QPushButton(tr("%"));
    power = new QPushButton(tr("^"));
    mul = new QPushButton(tr("*"));
    div = new QPushButton(tr("/"));
    add = new QPushButton(tr("+"));
    sub = new QPushButton(tr("-"));
    zero  = new QPushButton(tr("ce"));
    back  = new QPushButton(tr("c"));
    psqrt = new QPushButton(tr("√"));
    equ  = new QPushButton(tr("="));
    equ2 = new QPushButton(tr("="));
    change = new QPushButton(tr("+/-"));
    mln  = new QPushButton(tr("ln"));
    mlog = new QPushButton(tr("log"));
    em = new QPushButton(tr("exp()"));
    masin = new QPushButton(tr("asin"));
    macos = new QPushButton(tr("acos"));
    matan = new QPushButton(tr("atan"));
    fact  = new QPushButton(tr("n!"));
    rec = new QPushButton(tr("1/x"));

    //大小设置
    QSizePolicy police= num_0->sizePolicy();
    police.setVerticalPolicy(QSizePolicy::Minimum);
    num_1->setSizePolicy(police);
    num_2->setSizePolicy(police);
    num_3->setSizePolicy(police);
    num_4->setSizePolicy(police);
    num_5->setSizePolicy(police);
    num_6->setSizePolicy(police);
    num_7->setSizePolicy(police);
    num_8->setSizePolicy(police);
    num_9->setSizePolicy(police);
    num_0->setSizePolicy(police);
    lbracket->setSizePolicy(police);
    rbracket->setSizePolicy(police);
    pi->setSizePolicy(police);
    msin->setSizePolicy(police);
    mcos->setSizePolicy(police);
    mtan->setSizePolicy(police);
    mod->setSizePolicy(police);
    power->setSizePolicy(police);
    add->setSizePolicy(police);
    sub->setSizePolicy(police);
    mul->setSizePolicy(police);
    div->setSizePolicy(police);
    zero->setSizePolicy(police);
    back->setSizePolicy(police);
    dot->setSizePolicy(police);
    psqrt->setSizePolicy(police);
    equ->setSizePolicy(police);
    equ2->setSizePolicy(police);
    change->setSizePolicy(police);
    mln->setSizePolicy(police);
    mlog->setSizePolicy(police);
    em->setSizePolicy(police);
    masin->setSizePolicy(police);
    macos->setSizePolicy(police);
    matan->setSizePolicy(police);
    rec->setSizePolicy(police);
    fact->setSizePolicy(police);
    clearh->setSizePolicy(police);

    //test
    num_02 = new QPushButton(tr("0"));
    num_12 = new QPushButton(tr("1"));
    num_22 = new QPushButton(tr("2"));
    num_32 = new QPushButton(tr("3"));
    num_42 = new QPushButton(tr("4"));
    num_52 = new QPushButton(tr("5"));
    num_62 = new QPushButton(tr("6"));
    num_72 = new QPushButton(tr("7"));
    num_82 = new QPushButton(tr("8"));
    num_92 = new QPushButton(tr("9"));
    dot2 = new QPushButton(tr("."));
    lbracket2 = new QPushButton(tr("("));
    rbracket2 = new QPushButton(tr(")"));
    mul2 = new QPushButton(tr("*"));
    div2 = new QPushButton(tr("/"));
    add2 = new QPushButton(tr("+"));
    sub2 = new QPushButton(tr("-"));
    zero2 = new QPushButton(tr("ce"));
    back2 = new QPushButton(tr("c"));
    equ2  = new QPushButton(tr("="));
    num_12->setSizePolicy(police);
    num_22->setSizePolicy(police);
    num_32->setSizePolicy(police);
    num_42->setSizePolicy(police);
    num_52->setSizePolicy(police);
    num_62->setSizePolicy(police);
    num_72->setSizePolicy(police);
    num_82->setSizePolicy(police);
    num_92->setSizePolicy(police);
    num_02->setSizePolicy(police);
    lbracket2->setSizePolicy(police);
    rbracket2->setSizePolicy(police);
    add2->setSizePolicy(police);
    sub2->setSizePolicy(police);
    mul2->setSizePolicy(police);
    div2->setSizePolicy(police);
    zero2->setSizePolicy(police);
    back2->setSizePolicy(police);
    dot2->setSizePolicy(police);
    
    QGridLayout *test_cal = new QGridLayout;
    test_cal->addWidget(num_02, 4, 1, 1, 1);
    test_cal->addWidget(num_12, 3, 1, 1, 1);
    test_cal->addWidget(num_22, 3, 2, 1, 1);
    test_cal->addWidget(num_32, 3, 3, 1, 1);
    test_cal->addWidget(num_42, 2, 1, 1, 1);
    test_cal->addWidget(num_52, 2, 2, 1, 1);
    test_cal->addWidget(num_62, 2, 3, 1, 1);
    test_cal->addWidget(num_72, 1, 1, 1, 1);
    test_cal->addWidget(num_82, 1, 2, 1, 1);
    test_cal->addWidget(num_92, 1, 3, 1, 1);
    test_cal->addWidget(dot2, 4, 2, 1, 1);
    test_cal->addWidget(equ2, 4, 3, 1, 1);
    test_cal->addWidget(back2, 0, 3, 1, 1);
    test_cal->addWidget(zero2, 0, 2, 1, 1);
    test_cal->addWidget(rbracket2, 0, 1, 1, 1);
    test_cal->addWidget(lbracket2, 0, 0, 1, 1);
    test_cal->addWidget(add2, 1, 0, 1, 1);
    test_cal->addWidget(sub2, 2, 0, 1, 1);
    test_cal->addWidget(mul2, 3, 0, 1, 1);
    test_cal->addWidget(div2, 4, 0, 1, 1);
    //数字基础颜色更改
    num_0->setStyleSheet("background: rgb(169,169,169)");
    num_1->setStyleSheet("background: rgb(169,169,169)");
    num_2->setStyleSheet("background: rgb(169,169,169)");
    num_3->setStyleSheet("background: rgb(169,169,169)");
    num_4->setStyleSheet("background: rgb(169,169,169)");
    num_5->setStyleSheet("background: rgb(169,169,169)");
    num_6->setStyleSheet("background: rgb(169,169,169)");
    num_7->setStyleSheet("background: rgb(169,169,169)");
    num_8->setStyleSheet("background: rgb(169,169,169)");
    num_9->setStyleSheet("background: rgb(169,169,169)");
    dot->setStyleSheet("background: rgb(169,169,169)");

    //中部栅格
    QGridLayout *num = new QGridLayout;
    num->addWidget(num_0, 4, 2, 1, 2);
    num->addWidget(num_1, 3, 2, 1, 1);
    num->addWidget(num_2, 3, 3, 1, 1);
    num->addWidget(num_3, 3, 4, 1, 1);
    num->addWidget(num_4, 2, 2, 1, 1);
    num->addWidget(num_5, 2, 3, 1, 1);
    num->addWidget(num_6, 2, 4, 1, 1);
    num->addWidget(num_7, 1, 2, 1, 1);
    num->addWidget(num_8, 1, 3, 1, 1);
    num->addWidget(num_9, 1, 4, 1, 1);
    num->addWidget(zero, 0, 4, 1, 1);
    num->addWidget(dot, 4, 4, 1, 1);
    num->addWidget(rbracket,0,3,1,1);
    num->addWidget(lbracket,0,2,1,1);
    num->addWidget(add, 0, 1, 1, 1);
    num->addWidget(sub, 1, 1, 1, 1);
    num->addWidget(mul, 2, 1, 1, 1);
    num->addWidget(div, 3, 1, 1, 1);
    num->addWidget(change, 4, 1, 1, 1);
    num->addWidget(power, 0, 0, 1, 1);
    num->addWidget(mod, 1, 0, 1, 1);
    num->addWidget(fact, 2, 0, 1, 1);
    num->addWidget(rec, 3, 0, 1, 1);
    num->addWidget(em, 4, 0, 1, 1);

    //顶部水平布局
    QHBoxLayout *trangle = new QHBoxLayout;
    trangle->addWidget(msin);
    trangle->addWidget(mcos);
    trangle->addWidget(mtan);
    trangle->addWidget(masin);
    trangle->addWidget(macos);
    trangle->addWidget(matan);
    trangle->addWidget(clearh);
    //左部垂直布局
    QVBoxLayout *tleft = new QVBoxLayout;
    tleft->addWidget(psqrt);
    tleft->addWidget(pi);
    tleft->addWidget(mln);
    tleft->addWidget(mlog);
    //右部垂直布局
    QVBoxLayout *tright = new QVBoxLayout;
    tright->addWidget(back);
    tright->addWidget(equ);
    //常用界面
    QHBoxLayout *usual = new QHBoxLayout;
    usual->addLayout(tleft);
    usual->addLayout(num);
    usual->addLayout(tright);
    usual->setStretchFactor(tleft,1);
    usual->setStretchFactor(num,5);
    usual->setStretchFactor(tright,1);
    //垂直组合
    QVBoxLayout *al = new QVBoxLayout;
    al->addLayout(trangle);
    al->addLayout(usual);
    al->setStretchFactor(trangle,1);
    al->setStretchFactor(usual,5);
    //子窗口显示
    widget1 = new QWidget;
    widget1->setLayout(al);
    tab = new QTabWidget;
    tab->addTab(widget1,"计算");
    QVBoxLayout *t = new QVBoxLayout;
    t->addLayout(test_cal);
    t->setStretchFactor(test_cal,5);
    widget2 = new QWidget;
    widget2->setLayout(t);
    tab->addTab(widget2,"实时");
    showText = new QTextBrowser;
    showText->setText("");
    //主窗口设置
    //字体设置
    QFont font=showText->font(); //获取字体
    font.setPointSize(20);//修改字体大小
    showText->setFont(font);//设置字体
    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(showText);
    main->addWidget(tab);
    main->setStretchFactor(showText,1);
    main->setStretchFactor(tab,5);
    historyText = new QTextBrowser;
    historyText->setFont(font);//设置字体
    QHBoxLayout *all = new QHBoxLayout;
    all->addLayout(main);
    all->addWidget(historyText);
    all->setStretchFactor(main,5);
    all->setStretchFactor(historyText,2);
    tab = new QTabWidget;
    setLayout(all);

    setWindowOpacity(0.95);
}
void calculator::initSLOTS()
{
    QObject::connect(num_1, SIGNAL(clicked(bool)), this, SLOT(clicked1()));
    QObject::connect(num_2, SIGNAL(clicked(bool)), this, SLOT(clicked2()));
    QObject::connect(num_3, SIGNAL(clicked(bool)), this, SLOT(clicked3()));
    QObject::connect(num_4, SIGNAL(clicked(bool)), this, SLOT(clicked4()));
    QObject::connect(num_5, SIGNAL(clicked(bool)), this, SLOT(clicked5()));
    QObject::connect(num_6, SIGNAL(clicked(bool)), this, SLOT(clicked6()));
    QObject::connect(num_7, SIGNAL(clicked(bool)), this, SLOT(clicked7()));
    QObject::connect(num_8, SIGNAL(clicked(bool)), this, SLOT(clicked8()));
    QObject::connect(num_9, SIGNAL(clicked(bool)), this, SLOT(clicked9()));
    QObject::connect(num_0, SIGNAL(clicked(bool)), this, SLOT(clicked0()));
    QObject::connect(pi, SIGNAL(clicked(bool)), this, SLOT(clickedpi()));
    QObject::connect(lbracket, SIGNAL(clicked(bool)), this, SLOT(clickedleft()));
    QObject::connect(rbracket, SIGNAL(clicked(bool)), this, SLOT(clickedright()));
    QObject::connect(change, SIGNAL(clicked(bool)), this, SLOT(clickedchange()));
    QObject::connect(mln, SIGNAL(clicked(bool)), this, SLOT(clickedln()));
    QObject::connect(mlog, SIGNAL(clicked(bool)), this, SLOT(clickedlog()));
    QObject::connect(rec, SIGNAL(clicked(bool)), this, SLOT(clickedrec()));
    QObject::connect(fact, SIGNAL(clicked(bool)), this, SLOT(clickedfact()));
    QObject::connect(em, SIGNAL(clicked(bool)), this, SLOT(clickedem()));
    QObject::connect(clearh, SIGNAL(clicked(bool)), this, SLOT(clickedclearh()));
    QObject::connect(mul, SIGNAL(clicked(bool)), this, SLOT(clickedmul()));
    QObject::connect(div, SIGNAL(clicked(bool)), this, SLOT(clickeddiv()));
    QObject::connect(add, SIGNAL(clicked(bool)), this, SLOT(clickedadd()));
    QObject::connect(sub, SIGNAL(clicked(bool)), this, SLOT(clickedsub()));
    QObject::connect(mod, SIGNAL(clicked(bool)), this, SLOT(clickedmod()));
    QObject::connect(dot, SIGNAL(clicked(bool)), this, SLOT(clickeddot()));
    QObject::connect(power, SIGNAL(clicked(bool)), this, SLOT(clickedpower()));
    QObject::connect(psqrt, SIGNAL(clicked(bool)), this, SLOT(clickedsqrt()));
    QObject::connect(equ, SIGNAL(clicked(bool)), this, SLOT(clickedequ()));
    QObject::connect(equ2, SIGNAL(clicked(bool)), this, SLOT(clickedequ()));
    QObject::connect(back, SIGNAL(clicked(bool)), this, SLOT(clickedback()));
    QObject::connect(zero, SIGNAL(clicked(bool)), this, SLOT(clickedzero()));
    QObject::connect(msin, SIGNAL(clicked(bool)), this, SLOT(clickedsin()));
    QObject::connect(mcos, SIGNAL(clicked(bool)), this, SLOT(clickedcos()));
    QObject::connect(mtan, SIGNAL(clicked(bool)), this, SLOT(clickedtan()));
    QObject::connect(masin, SIGNAL(clicked(bool)), this, SLOT(clickedmasin()));
    QObject::connect(macos, SIGNAL(clicked(bool)), this, SLOT(clickedmacos()));
    QObject::connect(matan, SIGNAL(clicked(bool)), this, SLOT(clickedmatan()));

    //test
    QObject::connect(num_12, SIGNAL(clicked(bool)), this, SLOT(clicked12()));
    QObject::connect(num_22, SIGNAL(clicked(bool)), this, SLOT(clicked22()));
    QObject::connect(num_32, SIGNAL(clicked(bool)), this, SLOT(clicked32()));
    QObject::connect(num_42, SIGNAL(clicked(bool)), this, SLOT(clicked42()));
    QObject::connect(num_52, SIGNAL(clicked(bool)), this, SLOT(clicked52()));
    QObject::connect(num_62, SIGNAL(clicked(bool)), this, SLOT(clicked62()));
    QObject::connect(num_72, SIGNAL(clicked(bool)), this, SLOT(clicked72()));
    QObject::connect(num_82, SIGNAL(clicked(bool)), this, SLOT(clicked82()));
    QObject::connect(num_92, SIGNAL(clicked(bool)), this, SLOT(clicked92()));
    QObject::connect(num_02, SIGNAL(clicked(bool)), this, SLOT(clicked02()));
    QObject::connect(mul2, SIGNAL(clicked(bool)), this, SLOT(clickedmul2()));
    QObject::connect(div2, SIGNAL(clicked(bool)), this, SLOT(clickeddiv2()));
    QObject::connect(add2, SIGNAL(clicked(bool)), this, SLOT(clickedadd2()));
    QObject::connect(sub2, SIGNAL(clicked(bool)), this, SLOT(clickedsub2()));
    QObject::connect(dot2, SIGNAL(clicked(bool)), this, SLOT(clickeddot2()));
    QObject::connect(equ2, SIGNAL(clicked(bool)), this, SLOT(clickedequ2()));
    QObject::connect(back2, SIGNAL(clicked(bool)), this, SLOT(clickedback2()));
    QObject::connect(zero2, SIGNAL(clicked(bool)), this, SLOT(clickedzero2()));
    QObject::connect(lbracket2, SIGNAL(clicked(bool)), this, SLOT(clickedleft2()));
    QObject::connect(rbracket2, SIGNAL(clicked(bool)), this, SLOT(clickedright2()));
}
calculator::~calculator()
{

}
void calculator::clicked1()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="1";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked2()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="2";
   qstr+=temp;
   showstr+=temp;
    finish_sign=0;
    errsign=0;
   showText->setText(showstr);
}
void calculator::clicked3()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="3";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked4()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="4";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked5()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="5";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked6()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="6";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked7()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="7";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked8()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="8";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked9()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="9";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clicked0()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="0";
   qstr+=temp;
   showstr+=temp;
   finish_sign=0;
   errsign=0;
   showText->setText(showstr);
}
void calculator::clickeddot(){

    if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
        QString temp=".";
        qstr+=temp;
        showstr+=temp;
    }
    if(perrsign!=1){
        QString temp=".";
        qstr+=temp;
        showstr+=temp;
    }
    finish_sign=0;
    errsign=1;
    perrsign=1;
    showText->setText(showstr);
}
void calculator::clickedpi()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
    QString temp="pi";
    showstr+=temp;
    temp="(pi)";
    qstr+=temp;
    finish_sign=0;
    errsign=0;
     showText->setText(showstr);
}
void calculator::clickedmul()
{   if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    errsign=1;
    QString temp="*";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    perrsign=0;
     showText->setText(showstr);
}
void calculator::clickeddiv()
{   if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    errsign=1;
    QString temp="/";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedadd()
{
    if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    QString temp="+";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    errsign=1;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedsub()
{
    if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    QString temp="-";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    errsign=1;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedmod()
{
    if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    QString temp="%";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    errsign=1;
    perrsign=0;
    showText->setText(showstr);
}

void calculator::clickedpower()
{
    if(errsign==1){
        qstr.chop(1);
        showstr.chop(1);
    }
    errsign=1;
    QString temp="^";
    qstr+=temp;
    showstr+=temp;
    finish_sign=0;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedsqrt()
{
    QString temp="sqrt";
    if(finish_sign==1){
        showstr.push_front("√");
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+="√";
        }
    finish_sign=0;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedzero()
{
    qstr.clear();
    showstr.clear();
    m_num.clear();
    perrsign=0;
    errsign=0;
    showText->setText("0");
}
void calculator::clickedclearh()
{
    qstr.clear();
    showstr.clear();
    m_num.clear();
    perrsign=0;
    historyText->clear();
}
void calculator::clickedrec()
{
    QString temp="rec";
    qstr+=temp;
    showstr+="^-1";
    finish_sign=0;
    perrsign=0;
    showText->setText(showstr);
}
void calculator::clickedln()
{
    QString temp="ln";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
    perrsign=0;
     showText->setText(showstr);
}
void calculator::clickedlog()
{
    QString temp="log";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
    perrsign=0;
     showText->setText(showstr);
}
void calculator::clickedfact()
{
    QString temp="!";
    if(finish_sign==1){
        showstr.push_back(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
    perrsign=0;
     showText->setText(showstr);
}
void calculator::clickedem()
{
    QString temp="em";
    if(finish_sign==1){
        finish_sign=0;
        showstr.push_front("e^");
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+="e^";
        }
    finish_sign=0;
    perrsign=0;
     showText->setText(showstr);
}
void calculator::clickedsin()
{
    QString temp="sin";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedcos()
{
    QString temp="cos";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedtan()
{
    QString temp="tan";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedmasin()
{
    QString temp="asin";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedmacos()
{
    QString temp="acos";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedmatan()
{
    QString temp="atan";
    if(finish_sign==1){
        showstr.push_front(temp);
        qstr.push_front(temp);
        }
    else{
        qstr+=temp;
        showstr+=temp;
        }
    finish_sign=0;
     showText->setText(showstr);
}
void calculator::clickedback()
{
    if(finish_sign==1)
    {
        finish_sign=0;
        showstr.clear();
        qstr.clear();
    }
    else if(showstr.right(2)=="pi")
    {
        showstr.chop(2);
        qstr.chop(4);
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
    else if(showstr.right(2)=="ln"||showstr.right(2)=="e^")
    {
        showstr.chop(2);
        qstr.chop(2);
    }
    else if(showstr.right(1)=="."){
        showstr.chop(1);
        qstr.chop(1);
        perrsign=0;
    }
    else
    {
        showstr.chop(1);
        qstr.chop(1);
    }
    showText->setText(showstr);
    errsign=0;
}
void calculator::clickedequ()
{

    QString temp="=";
    qstr+=temp;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=1;
    perrsign=0;
    doIt(qstr);
}
void calculator::clickedleft()
{
    QString temp="(";
    if(finish_sign==1){
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr+=temp;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=0;
    perrsign=0;
    bsign=1;
}
void calculator::clickedright()
{
    QString temp=")";
    if(finish_sign==1){
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr+=temp;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=0;
    perrsign=0;
}
void calculator::clickedchange()
{
    QString temp="@";
    if(finish_sign==1){
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr+=temp;
    showstr+="-";
    showText->setText(showstr);
    finish_sign=0;
    perrsign=0;
}

double calculator::doIt(QString &question) {
    unique_ptr<Operator> oo;
    historyText->append(showstr);
    string exp;
    exp= question.toStdString();
    auto it = exp.begin();
    if(!isNum(it))
        exp="0"+exp;
    for (auto it = exp.begin(); it != exp.end();) {
        // 如果是操作数, 压栈之
        if (isNum(it))
            m_num.push(readNum(it));
        else {// 如果是运算符, 压栈或计算
              // 将readOpr得到的string转化为Operator
            if(issin(it))
                oo=Factory::create(readsin(it));
            else
            {
                string s;
                s+=*it++;
                oo=Factory::create(s);
            }
            // 如果栈顶优先级高, 则计算
            if(oo->symbol()!="(")
            {
                while (oo->precedence() <= m_opr.top()->precedence()) {
                if (m_opr.top()->symbol() == "#")
                    break;
                calculate();
                }
            }
            // "="从不入栈
            if (oo->symbol() != "=")
                m_opr.push(std::move(oo));
        }
    }
    double result = m_num.top();
    double a=m_num.top();
    showText->append(QString::number(a));
    historyText->append(QString::number(a));
    question.clear();
    showstr.clear();
    showstr+=QString::number(a);
    return result;
}

double calculator::readNum(string::iterator& it){
    string t;
    while (isNum(it))
        t += *it++;
    if (t == "pi")
    {
        return acos(-1);
    }
    return stod(t);
}
string calculator::readsin(string::iterator& it){
    string t;
    while (issin(it))
        t += *it++;
    return t;
}
void calculator::calculate() {
    // 操作数出栈并传入Operator进行计算, 在此只考虑单目和双目运算符
    double a[2] = { 0 };
    for (auto i = 0; i < m_opr.top()->numOprand(); ++i) {
        a[i] = m_num.top();
        m_num.pop();
    }
    m_num.push(m_opr.top()->get(a[1], a[0]));
    m_opr.pop();
}

void calculator::clicked02()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="0";
   qstr+=temp;
   showstr+=temp;
   oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked12()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="1";
   qstr+=temp;
   showstr+=temp;
   oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked22()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="2";
   qstr+=temp;
   showstr+=temp;
   oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked32()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="3";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked42()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked52()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="5";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked62()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="6";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked72()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="7";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked82()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="8";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clicked92()
{
    if(finish_sign==1)
    {
        qstr.clear();
        showstr.clear();
        m_num.clear();
    }
   QString temp="9";
   qstr+=temp;
   showstr+=temp;oldshow=showstr;
   finish_sign=0;
   showText->setText(showstr);
}
void calculator::clickeddot2(){
    QString temp=".";
    qstr+=temp;
    showstr+=temp;oldshow=showstr;
    finish_sign=0;
    showText->setText(showstr);
}
void calculator::clickedadd2()
{
    double nowequ;
    QString dostr;
    oldshow=showstr;
    if (sign==0){
        QString temp="+";
        qstr+=temp;
        showstr+=temp;
        showText->setText(showstr);
        showText->append("0");
    }
    else{
        QString shownum;
        dostr=qstr+"=";
        nowequ=doIt(dostr);
        showText->clear();
        showstr=oldshow+"+";
        QString fequ=QString::number(nowequ);
        showText->setText(showstr);
        shownum=fequ;
        showText->append(shownum);
        qstr+="+";
    }
    finish_sign=0;
    sign=1;
}
void calculator::clickedsub2()
{
    double nowequ;
    QString dostr;
    oldshow=showstr;
    if (sign==0){
        QString temp="-";
        qstr+=temp;
        showstr+=temp;
        showText->setText(showstr);
        showText->append("0");
    }
    else{
        QString shownum;
        dostr=qstr+"=";
        nowequ=doIt(dostr);
        showText->clear();
        showstr=oldshow+"-";
        QString fequ=QString::number(nowequ);
        showText->setText(showstr);
        shownum=fequ;
        showText->append(shownum);
        qstr+="-";
    }
    finish_sign=0;
    sign=1;
}
void calculator::clickedmul2()
{
    double nowequ;
    QString dostr;
    oldshow=showstr;
    if (sign==0){
        QString temp="*";
        qstr+=temp;
        showstr+=temp;
        showText->setText(showstr);
        showText->append("0");
    }
    else{
        QString shownum;
        dostr=qstr+"=";
        nowequ=doIt(dostr);
        showText->clear();
        showstr=oldshow+"*";
        QString fequ=QString::number(nowequ);
        showText->setText(showstr);
        shownum=fequ;
        showText->append(shownum);
        qstr+="*";
    }
    finish_sign=0;
    sign=1;
}
void calculator::clickeddiv2()
{
    double nowequ;
    QString dostr;
    oldshow=showstr;
    if (sign==0){
        QString temp="/";
        qstr+=temp;
        showstr+=temp;
        showText->setText(showstr);
        showText->append("0");
    }
    else{
        QString shownum;
        dostr=qstr+"=";
        nowequ=doIt(dostr);
        showText->clear();
        showstr=oldshow+"/";
        QString fequ=QString::number(nowequ);
        showText->setText(showstr);
        shownum=fequ;
        showText->append(shownum);
        qstr+="/";
    }
    finish_sign=0;
    sign=1;
}
void calculator::clickedback2()
{
    if(finish_sign==1)
    {
        finish_sign=0;
        showstr.clear();
        qstr.clear();
    }
    else if(showstr.right(2)=="pi")
    {
        showstr.chop(2);
        qstr.chop(4);
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
    else if(showstr.right(2)=="ln"||showstr.right(2)=="e^")
    {
        showstr.chop(2);
        qstr.chop(2);
    }
    else
    {
        showstr.chop(1);
        qstr.chop(1);
    }
    showText->setText(showstr);
}
void calculator::clickedequ2()
{
    QString temp="=";
    qstr+=temp;
    showstr=oldshow;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=1;
    doIt(qstr);
}
void calculator::clickedleft2()
{
    QString temp="(";
    if(finish_sign==1){
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr+=temp;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=0;
}
void calculator::clickedright2()
{
    QString temp=")";
    if(finish_sign==1){
        showstr.clear();
        qstr.clear();
        m_num.clear();
    }
    qstr+=temp;
    showstr+=temp;
    showText->setText(showstr);
    finish_sign=0;
}

void calculator::clickedzero2()
{
    qstr.clear();
    showstr.clear();
    m_num.clear();
    showText->setText("0");
}
