#include"stdafx.h"

mapProposition Calculator::operatorPri = { {'(', 1}, {'!', 5}, {'&', 4}, {'|', 3}, {'>', 2}, {')', 6} };	//运算符优先级


bool isCap(char ch)
{
	if (ch < 'A' || ch > 'Z')	return false;
	else                        return true;
}

int pow(int x, int n)
{
	int res = 1;
	int base = x;
	while (n > 0)
	{
		if (n & 1)
			res *= base;
		base *= base;
		n >>= 1;
	}
	return res;
}

Calculator::Calculator()
{
}

Calculator::Calculator(string &s)
{
	formula = s;
}

Calculator::~Calculator()
{

}

void Calculator::count()
{
	charSet.clear();
	string::iterator it = formula.begin();
	while (it != formula.end())
	{
		if (isCap(*it))
			charSet.insert(*it);

		it++;
	}
	propositionNumber = charSet.size();
}

void Calculator::getFormulaSuffixExpress()
{
	string::iterator it = formula.begin();
	while (!operators.empty())	operators.pop();
	while(it != formula.end())
	{
		if (isCap(*it))
		{
			formulaSuffixExpress += *it;
		}
		else
		{
			if (!operators.empty() && *it != '(')
			{
				while (!operators.empty() && operatorPri[operators.top()] >= operatorPri[*it])
				{
					formulaSuffixExpress += operators.top();
					operators.pop();
				}
				if (*it == ')')
				{
					while (!operators.empty())
					{
						if (operators.top() != '(' && operators.top() != ')')
							formulaSuffixExpress += operators.top();
						operators.pop();
					}
				}
				else 
				{
					operators.push(*it);
				}
			}
			else
			{
				operators.push(*it);
			}
		}
		it++;
	}
	while (!operators.empty())
	{
		char ch = operators.top();
		if (ch != '(' && ch != ')')
			formulaSuffixExpress += ch;
		operators.pop();
	}
}

bool Calculator::getValue()
{
	while (!valStack.empty())	valStack.pop();
	string::iterator it = formulaSuffixExpress.begin();
	while (it != formulaSuffixExpress.end())
	{
		if (isCap(*it))
		{
			valStack.push(values[*it]);
		}
		else
		{
			bool ans1, ans2;
			switch (*it)
			{
			case '!':
				ans1 = valStack.top();
				valStack.pop();
				ans1 = !ans1;
				valStack.push(ans1);
				break;
			case '&':
				ans1 = valStack.top();
				valStack.pop();
				ans2 = valStack.top();
				valStack.pop();
				ans1 = ans1 & ans2;
				valStack.push(ans1);
				break;
			case '|':
				ans1 = valStack.top();
				valStack.pop();
				ans2 = valStack.top();
				valStack.pop();
				ans1 = ans1 | ans2;
				valStack.push(ans1);
				break;
			case '>':
				ans1 = valStack.top();
				valStack.pop();
				ans2 = valStack.top();
				valStack.pop();
				ans1 = ans1 | !ans2;
				valStack.push(ans1);
				break;
			default:
				break;
			}
		}
		it++;
	}
	return valStack.top();
}

void Calculator::solve()
{
	setProposition::iterator it;
	it = charSet.begin();
	while (it != charSet.end())
	{
		cout << *it << '\t';
		it++;
	}
	cout << formula;
	puts("");
	int sum = pow(2, propositionNumber)-1;
	for (int i = 0; i <= sum; i++)
	{
		values.clear();
		it = charSet.begin();
		int table = i;
		while (it != charSet.end())
		{
			values[*it] = table % 2;
			cout << values[*it] << '\t';
			table >>= 1;
			it++;
		}
		cout << getValue();
		puts("");
		if (getValue())
		{
			DNF = DNF +  '(';
			it = charSet.begin();
			while (it != charSet.end())
			{
				if (values[*it])
				{
					DNF = DNF +  *it + '&';
					
				}
				else
				{
					DNF = DNF +  '!' + *it + '&';
				}
				it++;
			}
			DNF[DNF.size() - 1] = ')';
			DNF = DNF +  '|';
		}
		else
		{
			CNF = CNF +  '(';
			it = charSet.begin();
			while (it != charSet.end())
			{
				if (values[*it])
				{
					CNF = CNF+ '!' + *it + '|';
				}
				else
				{
					CNF = CNF +  *it + '|';
				}
				it++;
			}
			CNF[CNF.size() - 1] = ')';
			CNF = CNF +  '&';
		}
	}
	CNF = CNF.substr(0, CNF.size() - 1);
	DNF = DNF.substr(0, DNF.size() - 1);
}

void Calculator::revPolish()
{
	getFormulaSuffixExpress();
	solve();
}
std::istream & operator >> (std::istream & is, Calculator & calculator)
{
	cout << "请输入合式公式，命题使用大写字母，运算符使用 \'(\', \')\', \'&\'（合取）, \'|\'（析取）, \'!\'（否定）, '>'（蕴含）:" << endl;
	cin >> calculator.formula;
	calculator.count();
	return is;
}

std::ostream & operator << (std::ostream & os, Calculator & calculator)
{
	cout << "合式公式：" << calculator.formula << endl;
	cout << "主合取范式" << calculator.CNF << endl;
	cout << "主析取范式" << calculator.DNF << endl;
	return os;
}