#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <map>
#include <functional>
#include <memory>
#include <utility>
#include "Operator.h"

//注册Object的宏定义
#define REGISTRAR(T, Key)  Factory::RegisterClass<T> reg_##T(Key);

using namespace std;

//
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

class Factory{
private:
    static map<string, function<unique_ptr<Operator>()>> ms_operator;

public:
	template<typename T>
    struct RegisterClass
    {
        RegisterClass(string opr)
        {
            Factory::ms_operator.emplace(opr, []{return make_unique<T>();});
		}
	};

    static unique_ptr<Operator> create(string opr)
    {
		auto it = ms_operator.find(opr);
		if (it != ms_operator.end()) 
			return it->second();
        else
            return nullptr;
	}
};

#endif
