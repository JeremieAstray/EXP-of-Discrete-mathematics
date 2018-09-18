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
	static mapProposition operatorPri;	//��������ȼ�

private:
	string formula;		//��ʽ��ʽ
	string formulaSuffixExpress;	//��ʽ��ʽ��׺���ʽ
	int propositionNumber;	//�������
	stackOperator operators;	//�����ջ
	stackValue	valStack;	//��ֵջ
	mapProposition values;	//������ֵ
	setProposition charSet;	//���⼯��

public:
	string DNF;	//����ȡ��ʽ
	string CNF;	//����ȡ��ʽ

private:
	void getFormulaSuffixExpress();	//��ú�׺���ʽ
	bool getValue();	//��ֵ
	void count();	//�����������
	void solve();	//������ֵ��

public:
	Calculator();
	Calculator(string &);
	void revPolish();	//�沨���㷨
	~Calculator();

	friend std::ostream & operator << (std::ostream &, Calculator &);
	friend std::istream & operator >> (std::istream &, Calculator &);
};