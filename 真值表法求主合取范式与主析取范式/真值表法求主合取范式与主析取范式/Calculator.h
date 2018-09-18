#pragma once
#include"stdafx.h"
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <iostream>

using std::string;
using std::map;
using std::vector;
using std::stack;
using std::set;
using std::cin;
using std::cout;
using std::endl;

typedef map<char, int> mapProposition;
typedef mapProposition::iterator mapIt;

typedef stack<char>	stackOperator;
typedef stack<bool> stackValue;

typedef set<char> setProposition;

class Calculator
{
	static mapProposition operatorPri;	//运算符优先级

private:
	string formula;		//合式公式
	string formulaSuffixExpress;	//合式公式后缀表达式
	int propositionNumber;	//命题个数
	stackOperator operators;	//运算符栈
	stackValue	valStack;	//真值栈
	mapProposition values;	//命题真值
	setProposition charSet;	//命题集合

public:
	string DNF;	//主析取范式
	string CNF;	//主合取范式

private:
	void getFormulaSuffixExpress();	//获得后缀表达式
	bool getValue();	//求值
	void count();	//计算命题个数
	void solve();	//计算真值表

public:
	Calculator();
	Calculator(string &);
	void revPolish();	//逆波兰算法
	~Calculator();

	friend std::ostream & operator << (std::ostream &, Calculator &);
	friend std::istream & operator >> (std::istream &, Calculator &);
};