#pragma once
/*Во всех вариантах индивидуальных заданий необходимо создать возможность конструирования 5 ОБЪЕКТОВ РАЗЛИЧНЫХ ТИПОВ с использованием подходов
«ФАБРИКА», «ФАБРИЧНЫЙ МЕТОД С АРГУМЕНТАМИ», «ФАБРИЧНЫЙ КОНСТРУКТОР», «ПОЛИМОРФНАЯ ФАБРИКА», «ПОЛИМОРФНОЕ КОПИРОВАНИЕ».
Для всех типов необходимо реализовать возможность их добавления, удаления, редактирования,
вывода содержимого объектов на экран в табличном виде и в файл. «Учет сотрудников ИТ-компании»*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#define G "Геймдизайнер" 
#define P "Программист"
#define N "Нарративщик"
#define L "Левел-дизайнер"
#define C "Концепт-художник"
using namespace std;
int cinIntErrorCheck(int min, int max) {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		cout << "Ошибка. Попробуйте ещё раз." << endl;
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
double cinDoubleErrorCheck(double min, double max) {
	double wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		//cin.ignore(100, '\n');
		cout << "Ошибка. Попробуйте ещё раз.\n";
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
void setGuy(string& fio, double& exp, double& money);
class IT_Guy
{
protected:
	string FIO;
	double money, exp;
public:
	virtual void createITGuy() = 0;
	virtual IT_Guy* cloneIT_Guy() const = 0;
	virtual string getFIO() = 0;
	virtual double getExp() = 0;
	virtual double getMoney() = 0;
	virtual string getType() = 0;

};

class Gamedesigner :public IT_Guy
{
public:
	Gamedesigner() {
		FIO = "Бурая Александра Константиновна";
		money = 2000000;
		exp = 2;
	};
	Gamedesigner(string FIO, double money, double exp)
	{
		this->FIO = FIO;
		this->money = money;
		this->exp = exp;
	}
	void createITGuy() override {
		cout << "Зарегистрирован геймдизайнер" << endl
			<< "ФИО: " << FIO << endl << "Опыт работы: " << exp << endl << "Зарплата: " << money << endl;
	}
	IT_Guy* cloneIT_Guy() const override
	{
		return new Gamedesigner(*this);
	}
	string getFIO() { return this->FIO; };
	double getExp() { return this->exp; };
	double getMoney() { return this->money; };
	string getType() { return G; }
};

class Programmer :public IT_Guy
{
public:
	Programmer() {
		FIO = "Яньчук Илья Николаевич";
		money = 1000000;
		exp = 7;
	};
	Programmer(string FIO, double money, double exp)
	{
		this->FIO = FIO;
		this->money = money;
		this->exp = exp;
	}
	void createITGuy() override { 
		cout << "Зарегистрирован программист" << endl
			<< "ФИО: " << FIO << endl << "Опыт работы: " << exp << endl << "Зарплата: " << money << endl;
	}
	IT_Guy* cloneIT_Guy() const override
	{
		return new Programmer(*this);
	}
	string getFIO() { return this->FIO; };
	double getExp() { return this->exp; };
	double getMoney() { return this->money; };
	string getType() { return P; }
};

class Narrative_designer :public IT_Guy
{
public:
	Narrative_designer() {
		FIO = "Альховик Данила Игоревич";
		money = 700000;
		exp = 3;
	};
	Narrative_designer(string FIO, double money, double exp)
	{
		this->FIO = FIO;
		this->money = money;
		this->exp = exp;
	}
	void createITGuy() override { 
		cout << "Зарегистрирован нарративщик" << endl
			<< "ФИО: " << FIO << endl << "Опыт работы: " << exp << endl << "Зарплата: " << money << endl;
	}
	IT_Guy* cloneIT_Guy() const override
	{
		return new Narrative_designer(*this);
	}
	string getFIO() { return this->FIO; };
	double getExp() { return this->exp; };
	double getMoney() { return this->money; };
	string getType() { return N; }
};

class Level_designer :public IT_Guy
{
public:
	Level_designer() {
		FIO = "Баранова Янина Сергеевна";
		money = 500000;
		exp = 2;
	};
	Level_designer(string FIO, double money, double exp)
	{
		this->FIO = FIO;
		this->money = money;
		this->exp = exp;
	}
	void createITGuy() override { 
		cout << "Зарегистрирован левел-дизайнер" << endl
			<< "ФИО: " << FIO << endl << "Опыт работы: " << exp << endl << "Зарплата: " << money << endl;
	}
	IT_Guy* cloneIT_Guy() const override
	{
		return new Level_designer(*this);
	}
	string getFIO() { return this->FIO; };
	double getExp() { return this->exp; };
	double getMoney() { return this->money; };
	string getType() { return L; }
};

class Сoncept_artist :public IT_Guy
{
public:
	Сoncept_artist() {
		FIO = "Рутковская Дарья Андреевна";
		money = 300000;
		exp = 4;
	};
	Сoncept_artist(string FIO, double money, double exp)
	{
		this->FIO = FIO;
		this->money = money;
		this->exp = exp;
	}
	void createITGuy() override { 
		cout << "Зарегистрирован концепт-художник" << endl
			<< "ФИО: " << FIO << endl << "Опыт работы: " << exp << endl << "Зарплата: " << money << endl;
	}
	IT_Guy* cloneIT_Guy() const override
	{
		return new Сoncept_artist(*this);
	}
	string getFIO() { return this->FIO; };
	double getExp() { return this->exp; };
	double getMoney() { return this->money; };
	string getType() { return C; }
};

void newGuys(vector <IT_Guy* >& Guys);
void changeGuys(vector <IT_Guy*>& Guys);
void deleteGuys(vector <IT_Guy*>& Guys);
void fileGuys(vector <IT_Guy*>& Guys);
void viewGuys(vector <IT_Guy*>& Guys);