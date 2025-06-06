#include "mainwindow.h"
#include <QBitmap>
#include <QApplication>
using namespace std;

map<string, function<unique_ptr<Operator>()>> Factory::ms_operator;

REGISTRAR(Plus, "+");
REGISTRAR(Minus, "-");
REGISTRAR(Multiply, "*");
REGISTRAR(Divide, "/");
REGISTRAR(Equal, "=");
REGISTRAR(mleft, "(");
REGISTRAR(mright, ")");
REGISTRAR(mod, "%");
REGISTRAR(power, "^");
REGISTRAR(mln, "ln");
REGISTRAR(mlog, "log");
REGISTRAR(rec, "rec");
REGISTRAR(fact, "!");
REGISTRAR(mexp, "mexp");
REGISTRAR(msqrt, "sqrt");
REGISTRAR(msin, "sin");
REGISTRAR(mcos, "cos");
REGISTRAR(mtan, "tan");
REGISTRAR(masin, "asin");
REGISTRAR(macos, "acos");
REGISTRAR(matan, "atan");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon("./logo.ico"));
    w.setWindowTitle("计算器");
    w.show();
    return a.exec();
}
