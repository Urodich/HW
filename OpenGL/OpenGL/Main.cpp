#include<iostream>
#include"Header.h"
#include "RenderEngine.h"
using namespace std;

int main1() {
	char num;
	cout << "lab number";
	cin >> num;

	switch (num)
	{
	case '1':
		lab1();
	case'2':
		lab2();
	case'3':
		lab3();
	case'4':
		lab4();
	default:
		break;
	}
	return 0;
}

int main() {
	RenderEngine = new RenderEngine();
}