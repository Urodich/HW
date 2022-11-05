#include<iostream>
#include"Header.h"
#include "RenderEngine.h"
#include <thread>
using namespace std;

int main() {
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
	case'5':
		lab5();
	default:
		break;
	}
	return 0;
}

RenderEngine* RenderEngine::Eng = NULL;
void main1() {
	
	RenderEngine* Eng = RenderEngine::GetInstance();
	Eng->Start();
    
}