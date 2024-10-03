#pragma once
#include "13.h"

class Factory_IT_Guy
{
public:
	virtual IT_Guy* createFactory() = 0;
	virtual IT_Guy* createFactory(string FIO, double money, double exp) = 0;
	virtual string typeFactory() = 0;
};

class GFactory : public Factory_IT_Guy
{
public:
	IT_Guy* createFactory() override { return new Gamedesigner(); };
	IT_Guy* createFactory(string FIO, double money, double exp) override { return new Gamedesigner(FIO, money, exp); };
	string typeFactory() { return G; };
};

class PFactory : public Factory_IT_Guy
{
public:
	IT_Guy* createFactory() override { return new Programmer(); };
	IT_Guy* createFactory(string FIO, double money, double exp) override { return new Programmer(FIO, money, exp); };
	string typeFactory() { return P; };
};

class NFactory : public Factory_IT_Guy
{
public:
	IT_Guy* createFactory() override { return new Narrative_designer(); };
	IT_Guy* createFactory(string FIO, double money, double exp) override { return new Narrative_designer(FIO, money, exp); };
	string typeFactory() { return N; };
};

class LFactory : public Factory_IT_Guy
{
public:
	IT_Guy* createFactory() override { return new Level_designer(); };
	IT_Guy* createFactory(string FIO, double money, double exp) override { return new Level_designer(FIO, money, exp); };
	string typeFactory() { return L; };
};

class CFactory : public Factory_IT_Guy
{
public:
	IT_Guy* createFactory() override { return new Ñoncept_artist(); };
	IT_Guy* createFactory(string FIO, double money, double exp) override { return new Ñoncept_artist(FIO, money, exp); };
	string typeFactory() { return C; };
};

IT_Guy* createFactory2(string type) {
	if (type == G)
		return new Gamedesigner();
	else if(type == P)
		return new Programmer();
	else if (type == N)
		return new Narrative_designer();
	else if (type == L)
		return new Level_designer();
	else if (type == C)
		return new Ñoncept_artist();
}