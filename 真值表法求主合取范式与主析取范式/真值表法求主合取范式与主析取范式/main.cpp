// 真值表法求主合取范式与主析取范式.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

Calculator calculate;
int main()
{
	
	cin >> calculate;
	calculate.revPolish();
	cout << calculate;
    return 0;
}