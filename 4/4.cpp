/*Написать программу учета наличия различных транспортных средств в автопарке. Разработать абстрактный базовый класс и набор
дочерних классов содержащий поля с информацией о транспортных средствах.Классы должны содержать следующие поля : тип транспортного
средства, количество мест для пассажиров и данные о водителе. По запросу выдавать необходимую информацию о транспортных средствах.
Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования.В класс добавить необходимый набор полей и
методов (минимум два поля и два метода) на свое усмотрение. Предусмотреть метод для записи полученных данных в файл.*/
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include<iomanip>
using namespace std;

int CinIntErrorCheck(int min, int max) {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		//cin.ignore(100, '\n');
		cout << "Ошибка. Попробуйте ещё раз." << endl;
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
			if (!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'А' && wcheck[i] <= 'Я'))
			{
				a = 0;
				cout << "Ошибка. Попробуйте ещё раз." << endl;
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
			if ((!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'a' && wcheck[i] <= 'z') && 
				!(wcheck[i] >= 'А' && wcheck[i] <= 'Я') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z')) && 
				(wcheck[i] < '0' || wcheck[i] > '9'))
			{
				a = 0;
				cout << "Ошибка. Попробуйте ещё раз." << endl;
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

class Autopark {
public:
	virtual void Type() = 0;
	virtual void Output() = 0;
	virtual void Infile(int i) = 0;
};

class Transport : public Autopark {
protected:
	string fio;
	int mesta, nomer;
public:
	Transport()
	{
		cout << "Введите номер транспортa:" << endl;
		nomer = CinIntErrorCheck(1, 999);
		string f, i, o, name;
		char c = ' ';
		cout << "Введите фамилию водителя:" << endl;
		f = CinStringSymErrorCheck();
		cout << "Введите имя водителя:" << endl;
		i = CinStringSymErrorCheck();
		cout << "Введите отчество водителя:" << endl;
		o = CinStringSymErrorCheck();
		name.append(f);
		name.push_back(c);
		name.append(i);
		name.push_back(c);
		name.append(o);
		fio = name;
		cout << "Введите количество мест в транспорте:" << endl;
		mesta = CinIntErrorCheck(9, 30);
		
	}
	Transport(string fio, int nomer, int mesta)
	{
		this->fio = fio;
		this->mesta = mesta;
		this->nomer = nomer;
	}
	Transport(const Transport &other)
	{
		this->fio = other.fio;
		this->mesta = other.mesta;
		this->nomer = other.nomer;
	}

	void Output()
	{
		cout << setw(15) << nomer << setw(25) << fio << setw(15) << mesta << endl;
	}
	void Infile(int i) {
		ofstream f;
		f.open("transport.txt", ios::app);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{ 
			if (i == 0)
				f << "Автобус";
			else if (i == 1)
				f << "Троллейбус";
			else
				f << "Трамвай";
			f << endl << fio << endl << nomer << endl << mesta << endl;
		}
		f.close();
	};
};

class Bus : public Transport {
public:
	void Type() { cout << "Автобус:" << endl; };
	Bus() : Transport() {};
};

class Trol : public Transport {
public:
	void Type() { cout << "Троллейбус:" << endl; }
	Trol() : Transport() {};
};

class Tram : public Transport {
public:
	void Type() { cout << "Трамвай:" << endl; }
	Tram() : Transport() {};
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Autopark *p[3];
	cout << "Введите данные автобуса: " << endl;
	Bus a;
	cout << "Введите данные троллейбуса: " << endl;
	Trol b;
	cout << "Введите данные трамвая: " << endl;
	Tram c;
	p[0] = &a; p[1] = &b; p[2] = &c;
	cout << setw(15) << "Номер:" << setw(25) << "ФИО:" << setw(15) << "Кол-во мест:" << endl;
	for (int i = 0; i < 3; i++)
	{
		p[i]->Type();
		p[i]->Output();
		p[i]->Infile(i);
	}
	cout << "Данные были записаны в файл" << endl;
}

