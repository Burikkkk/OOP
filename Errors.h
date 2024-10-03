#pragma once
#include <iostream>
#include <windows.h>
using namespace std;
int CinIntErrorCheck(int, int );
double CinDoubleErrorCheck(double min, double max);
string CinStringSymErrorCheck();
string CinStringSymIntErrorCheck();


int CinIntErrorCheck(int min, int max) {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		cout << "������. ���������� ��� ���." << endl;
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
double CinDoubleErrorCheck(double min, double max) {
	double wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		cout << "������. ���������� ��� ���.\n";
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
string CinStringSymErrorCheck() {
	string wcheck;
	int n, ch;
	bool a = 0;
	cin >> wcheck;
	rewind(stdin);
	n = wcheck.size();
	do {

		for (int i = 0; i < n; i++)
		{
			if (!(wcheck[i] >= '�' && wcheck[i] <= '�') && !(wcheck[i] >= '�' && wcheck[i] <= '�'))
			{
				a = 0;
				cout << "������. ���������� ��� ���." << endl;
				cin >> wcheck;
				rewind(stdin);
				n = wcheck.size();
				break;
			}
			else a = 1;
		}
	} while (a == 0);
	return wcheck;
}
string CinStringSymIntErrorCheck() {
	string wcheck;
	int n, ch;
	bool a = 0;
	cin >> wcheck;
	rewind(stdin);
	n = wcheck.size();
	do {

		for (int i = 0; i < n; i++)
		{
			if ((!(wcheck[i] >= '�' && wcheck[i] <= '�') && !(wcheck[i] >= 'a' && wcheck[i] <= 'z') && !(wcheck[i] >= '�' && wcheck[i] <= '�') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z')) && (wcheck[i] < '0' || wcheck[i] > '9'))
			{
				a = 0;
				cout << "������. ���������� ��� ���." << endl;
				cin >> wcheck;
				rewind(stdin);
				n = wcheck.size();
				break;
			}
			else a = 1;
		}
	} while (a == 0);
	return wcheck;
}