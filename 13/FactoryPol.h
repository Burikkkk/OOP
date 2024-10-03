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
		cout << "������������ ������������� ����� ����" << endl;
	}
	string getType() { return "����"; };
};

class Programm : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "����������� �������� ��� ����� ����������" << endl;
	}
	string getType() { return "���������"; };
};

class Story : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "����������� ����� ����� �����" << endl;
	}
	string getType() { return "�����"; };
};

class Level : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "�����-�������� ������� ����� ������" << endl;
	}
	string getType() { return "�������"; };
};

class Art : public IT_Project
{
public:
	void createProject(IT_Guy* Guy) override {
		Guy->createITGuy();
		cout << "�������-�������� ������ ����� ���" << endl;
	}
	string getType() { return "���"; };
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