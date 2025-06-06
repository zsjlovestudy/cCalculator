#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <math.h>
#include <mainwindow.h>

using namespace std;
class Operator
{
public:
    Operator(string c, int numOprd, int pre) :m_symbol(c), m_numOprand(numOprd), m_precedence(pre) { }
    string symbol() const { return m_symbol; }
    int numOprand() const { return m_numOprand; }
    int precedence() const { return m_precedence; }
    virtual double getResult(double a, double b) const = 0;
    virtual ~Operator() {}
protected:
    const string m_symbol; // 运算符符号
    const int m_numOprand;  // 运算符目数
    const int m_precedence;
};

class Plus : public Operator { // 运算符+
public:
    Plus() :Operator("+", 2, 2) {}
    double getResult(double a, double b) const {
        return a + b;
    }
};

class Minus :public Operator { // 运算符-
public:
    Minus() :Operator("-", 2, 2) {}
    double getResult(double a, double b) const {
        return a - b;
    }
};

class Multiply :public Operator { // 运算符*
public:
    Multiply() :Operator("*", 2, 3) {}
    double getResult(double a, double b) const {
        return a*b;
    }
};


class Divide :public Operator { // 运算符/
public:
    Divide() :Operator("/", 2, 3) {}
    double getResult(double a, double b) const {
        return a / b;
    }
};

class mleft :public Operator {
public:
    mleft():Operator("(", 1, 1) {}
    double getResult(double a, double b) const {
        (void) a;
        return  b;
    }
};

class mright :public Operator {
public:
    mright():Operator(")", 1, 2) {}
    double getResult(double a, double b) const {
        (void) a;
        return b; //
    }
};
class mod :public Operator {
public:
    mod() :Operator("%", 2, 3) {}
    double getResult(double a, double b) const {
        int c=a/b;
        return a-c*b;
    }
};

class power :public Operator {
public:
    power() :Operator("^", 2, 5) {}
    double getResult(double a, double b) const {
        return pow(a, b);
    }
};

class msqrt :public Operator {
public:
    msqrt() :Operator("sqrt", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return sqrt(b);
    }
};

class mln :public Operator { //
public:
    mln():Operator("ln", 1, 5) {}
    double getResult(double a, double b) const {
        (void) a;
        return log(b);
    }
};

class mlog :public Operator {
public:
    mlog():Operator("log", 1, 5) {}
    double getResult(double a, double b) const {
        (void) a;
        return log10(b);
    }
};

class rec :public Operator {
public:
    rec():Operator("rec", 1, 5) {}
    double getResult(double a, double b) const {
        (void) a;
        return 1/b;
    }
};

class fact :public Operator {
public:
    fact():Operator("!", 1, 3) {}
    double getResult(double a, double b) const {
        (void) a;
        int result=1;
        for(int i=1;i<=b;i++)
        {
            result*=i;
        }
        return result;
    }
};

class mexp :public Operator {
public:
    mexp():Operator("mexp", 1, 5) {}
    double getResult(double a, double b) const {
        (void) a;
        return exp(b);
    }
};

class Hash :public Operator {
public:
    Hash() :Operator("#", 1, 0) {}
    double getResult(double a, double b) const {
        (void) a;
        return b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};


class Equal :public Operator {
public:
    Equal() :Operator("=", 2, -1) {}
    double getResult(double a, double b) const {
        (void) b;
        return a;
    }
};
class msin :public Operator {
public:
    msin() :Operator("sin", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return sin(b);
    }
};

class mcos :public Operator {
public:
    mcos() :Operator("cos", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return cos(b);
    }
};

class mtan :public Operator {
public:
    mtan() :Operator("tan", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return tan(b);
    }
};

class masin :public Operator {
public:
    masin() :Operator("asin", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return asin(b);
    }
};

class macos :public Operator {
public:
    macos() :Operator("acos", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return acos(b);
    }
};

class matan :public Operator {
public:
    matan() :Operator("atan", 1, 6) {}
    double getResult(double a, double b) const {
        (void) a;
        return atan(b);
    }
};
#endif
