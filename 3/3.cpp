/*Создать класс «Человек», включающий в себя ФИО, год рождения, паспортные данные. 
Создать классы «Предприниматель» с полями «номер лицензии», «адрес регистрации», «УНН», «данные о налоговых платежах»;
«Турист» с полями «данные о пересечении границы». 
Создать массив объектов базового класса и заполнить этот массив объектами базового и производных классов.
Написать программу, которая определяет самого старшего из созданных объектов и выводит данные о созданных объектах в файл.
Классы должны содержать методы получения и изменения значений всех полей.
Все поля классов должны быть объявлены с атрибутами private или protected.*/
#include <fstream>
#include <iostream>
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
			if (!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'a' && wcheck[i] <= 'z')&& !(wcheck[i] >= 'А' && wcheck[i] <= 'Я') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z'))
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
			if ((!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'a' && wcheck[i] <= 'z') && !(wcheck[i] >= 'А' && wcheck[i] <= 'Я') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z')) && (wcheck[i] < '0' || wcheck[i] > '9'))
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

class Human {
private:
	string FIO, pass_id;
	int year;
public:
	Human()
	{
		string f, i, o, name;
		char c = ' ';
		cout << "Введите фамилию:" << endl;
		f=CinStringSymErrorCheck();
		cout << "Введите имя:" << endl;
		i = CinStringSymErrorCheck();
		cout << "Введите отчество:" << endl;
		o = CinStringSymErrorCheck();
		name.append(f);
		name.push_back(c);
		name.append(i);
		name.push_back(c);
		name.append(o);
		FIO = name;
		cout << "Введите год рождения:" << endl;
		year = CinIntErrorCheck(1923,2023);
		cout << "Введите номер паспорта:" << endl;
		pass_id=CinStringSymIntErrorCheck();
	}
	void Change()
	{
		int a;
		string f, i, o, name;
		char c = ' ';
		do {
			cout << "-----------------------" << endl
				<< "Изменить:" << endl
				<< "1-Фио;" << endl
				<< "2-Год рождения;" << endl
				<< "3-Номер паспорта;" << endl
				<< "0-Выход;" << endl
				<< "-----------------------" << endl;
			cin >> a;
			switch (a)
			{
			case 1: 
				
				cout << "Введите фамилию:" << endl;
				f = CinStringSymErrorCheck();
				cout << "Введите имя:" << endl;
				i = CinStringSymErrorCheck();
				cout << "Введите отчество:" << endl;
				o = CinStringSymErrorCheck();
				name.append(f);
				name.push_back(c);
				name.append(i);
				name.push_back(c);
				name.append(o);
				FIO = name;
				break;
			case 2: 
				cout << "Введите год рождения:" << endl;
				year = CinIntErrorCheck(1923, 2023);
				break;
			case 3: 
				cout << "Введите номер паспорта:" << endl;
				pass_id = CinStringSymIntErrorCheck();
				break;
			case 0: return; break;
			}
		} while (true);
	}
	virtual void Output() const
	{
		cout << setw(20) << FIO << setw(10) << year << setw(15) << pass_id;
	}
	string GetFIO() { return FIO; }
	string GetPass() { return pass_id; }
	int GetYear() { return year; }
	void SetFIO(string Fio) { FIO = Fio; }
	void SetPass(string pass) { pass_id=pass; }
	void SetYear(int y) { year=y; }
	virtual void Infile(string name) const
	{
		ofstream f;
		f.open(name, ios::app);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{
			f << FIO << endl << pass_id << endl << year << endl;
		}
		f.close();
	}
	
};

class Employer : public Human{
private:
	int number, unn;
	string address;
	bool nalog;
public:
	Employer()
	{
		cout << "Введите номер лицензии (7 цифр):" << endl;
		number = CinIntErrorCheck(1000000, 9999999);
		cout << "Введите адрес регистрации" << endl;
		address = CinStringSymIntErrorCheck();
		cout << "Введите учетный номер налогоплательщика (7 цифр):" << endl;
		unn = CinIntErrorCheck(1000000, 9999999);
		cout << "1-Налоги уплачены\n0-Налоги не уплачены" << endl;
		nalog = CinIntErrorCheck(0, 1);
	}
	void ChangeE()
	{
		int a, size;
		do {
			cout << "-----------------------" << endl
				<< "Изменить:" << endl
				<< "1-Номер лицензии;" << endl
				<< "2-Адрес регистрации;" << endl
				<< "3-УНН;" << endl
				<< "4-Налоги;" << endl
				<< "0-Выход;" << endl
				<< "-----------------------" << endl;
			a = CinIntErrorCheck(0, 4);
			switch (a)
			{
			case 1:
				cout << "Введите номер лицензии (7 цифр):" << endl;
				number = CinIntErrorCheck(1000000, 9999999);
				break;
			case 2:
				cout << "Введите адрес регистрации" << endl;
				address= CinStringSymIntErrorCheck();
				break;
			case 3:
				cout << "Введите учетный номер налогоплательщика (7 цифр):" << endl;
				unn = CinIntErrorCheck(1000000, 9999999);
				break;
			case 4:
				cout << "1-Налоги уплачены\n0-Налоги не уплачены" << endl;
				nalog=CinIntErrorCheck(0,1);
				break;
			case 0: return; break;
			}
		} while (true);
	}
	void Output() const
	{
		Human::Output();
		cout << setw(15) << number << setw(15) << address << setw(20) << unn << setw(25);
		if (nalog == 0) cout << "Налоги не уплачены";
		else cout << "Налоги уплачены";
		cout << endl;
	}
	void Infile(string name) const
	{
		Human::Infile(name);
		ofstream f;
		f.open(name, ios::app);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{
			f << number << endl << unn << endl << address << endl << nalog << endl;
		}
		f.close();
	}
};

class Tourist : public Human{
private:
	string *country;
	int size;
public:
	Tourist(int n)
	{
		size = n;
		country = new string[n];
		cout << "Введите страны" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "[" << i+1 << "]: ";
			country[i]=CinStringSymErrorCheck();
		}
	}
	~Tourist()
	{
		delete[]country;
	}
	void ChangeT()
	{
		cout << "Введите " << size << "стран" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "[" << i+1 << "]: ";
			country[i] = CinStringSymErrorCheck();
		}
	}
	void Output() const
	{
		Human::Output();
		cout << setw(20) << country[0] << endl;
		for (int i = 1; i < size; i++)
		{
			cout << setw(65) << country[i] << endl;
		}
	}
	void Infile(string name) const
	{
		Human::Infile(name);
		ofstream f;
		f.open(name, ios::app);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{ 
			f << size << endl;
			for (int i = 0; i < size; i++)
			{
				f << country[i] << endl;
			}
		}
		f.close();
	}
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Human *arr[2];
	int a, b;
	cout << "Данные о предпринимателе: " << endl;
	arr[0] = new Employer();
	cout << "Данные о туристе: " << endl;
	cout << "Введите количество стран, которые посетил турист 1: " << endl;
	a= CinIntErrorCheck(1,100);
	arr[1] = new Tourist(a);
	cout << "О ком вы хотите изменить данные: 1-Предприниматель, 2-Турист" << endl;
	b = CinIntErrorCheck(1, 2);
	if (b == 1) arr[0]->Change();
	else arr[1]->Change();
	cout << "Данные о предпринимателе: " << endl;
	cout << setw(20) << "ФИО:" << setw(10) << "Год:" << setw(15) << "Паспорт" << setw(15) 
		<< "Лицензия:" << setw(15) << "Адрес:" << setw(20) << "УНН:" << setw(25)<<"Налог:\n";
	arr[0]->Output();
	cout << "\nДанные о туристе: " << endl;
	cout << setw(20) << "ФИО:" << setw(10) << "Год:" << setw(15) << "Паспорт:" << setw(20) << "Страны:" << endl;
	arr[1]->Output();
	/*ofstream f;
	f.open("employer.txt");
	f.close();
	ofstream k;
	k.open("tourist.txt");
	k.close();*/
	arr[0]->Infile("employer.txt");
	arr[1]->Infile("tourist.txt");
	cout << "Данные были записаны в файл" << endl;
	if (arr[0]->GetYear() < arr[1]->GetYear())
	{
		cout << "\n\nСтарше предприниматель " << endl;
		cout << setw(20) << "ФИО:" << setw(10) << "Год:" << setw(15) << "Паспорт" << setw(15)
			<< "Лицензия:" << setw(15) << "Адрес:" << setw(20) << "УНН:" << setw(25) << "Налог:";
		
		arr[0]->Output();
	}
	else if (arr[0]->GetYear() == arr[1]->GetYear())
		cout << "\nУ туриста и предпринимателя одинаковый возраст" << endl;
	else
	{
		cout << "\n\nСтарше турист " << endl;
		cout << setw(20) << "ФИО:" << setw(10) << "Год:" << setw(15) << "Паспорт:" << setw(20) << "Страны:" << endl;
		arr[1]->Output();
	}
}