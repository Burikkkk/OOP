#pragma once
#include "13.h"

class IT_Project {
public:
	virtual void createProject(IT_Guy* Guy) = 0;
	virtual string getType() = 0;
};

class Game : public IT_Project 
{
public:
	void createProject(IT_Guy* Guy) override{
		Guy->createITGuy();
		cout << "Геймдизайнер разрабатывает новую игру" << endl;
	}
	string getType() { return "Игра"; };
};

class Programm : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "Программист работает над новой программой" << endl;
	}
	string getType() { return "Программа"; };
};

class Story : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "Нарративщик пишет новый сюжет" << endl;
	}
	string getType() { return "Сюжет"; };
};

class Level : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "Левел-дизайнер создает новые уровни" << endl;
	}
	string getType() { return "Уровень"; };
};

class Art : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "Концепт-художник рисует новый арт" << endl;
	}
	string getType() { return "Арт"; };
};

class Factory_Project {
public:
	virtual IT_Project* createProject(IT_Guy* Guy) = 0;
};

class Factory_Projectmaker :public Factory_Project {
public:
	IT_Project* createProject(IT_Guy* Guy) override {
		if (Guy->getType() == G)
			return new Game();
		else if (Guy->getType() == P)
			return new Programm();
		else if (Guy->getType() == N)
			return new Story();
		else if (Guy->getType() == L)
			return new Level();
		else if (Guy->getType() == C)
			return new Art();
	};
};