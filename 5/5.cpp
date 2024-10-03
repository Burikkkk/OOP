/*Имеется два класса: «Данные о работнике» (поля класса: фамилия, массив зарплат за квартал), «Налоговые данные» (поля класса: процент
подоходного налога). Разработать класс «Платежная форма» для вывода итоговых данных (данных о работке и о его налоговых вычетах). При
необходимости самостоятельно добавить классы для реализации множественного наследования.*/
#include <iostream>
#include <string>
#include <windows.h>
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
double CinDoubleErrorCheck(double min, double max) {
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

class Inf_employee
{
public:
	Inf_employee();
	~Inf_employee();
	void Input();
	void Output();
	double Sum();

private:
	string name;
	int kol;
	double *mas;
};

Inf_employee::Inf_employee()
{
	name = "Иванов";
	kol = 3;
	mas = new double[kol];
	mas[0] = mas[1] = mas[2] = 1;
}

void Inf_employee::Output()
{
	cout << "Фамилия работника:" << name << endl;
	cout << "Зарплаты за квартал:" << endl;
	for (int i = 0; i < kol; i++)
	{
		cout << mas[i] << "\t";
	}
	cout << endl;
}


void Inf_employee::Input()
{
	cout << "Введите фамилию работника:" << endl;
	name = CinStringSymErrorCheck();
	cout << "Введите количество зарплат:" << endl;
	kol = CinIntErrorCheck(1,3);
	for (int i = 0; i < kol; i++)
	{
		cout << "Введите зарплату" << endl;
		mas[i]=CinDoubleErrorCheck(0, 10000);
	}
}

double Inf_employee::Sum()
{
	double sum=0;
	for (int i = 0; i < kol; i++)
	{
		sum += mas[i];
	}
	return sum;
}


Inf_employee::~Inf_employee()
{
	delete[] mas;
}

class Inf_tax
{
public:
	Inf_tax() { tax = 13; }
	void Inputtax();
	void Outputtax();
	double GetTax()
	{
		return tax;
	}

private:
	double tax;
};

void Inf_tax::Inputtax()
{
	cout << "Введите процент подоходного налога" << endl;
	tax = CinDoubleErrorCheck(1, 100);
}

void Inf_tax::Outputtax()
{
	cout << "Процент подоходного налога: " << tax << endl;
}

class Tax_form : public Inf_employee, public Inf_tax
{
public:
	double Result()
	{
		return Sum() * GetTax() / 100;
	}

private:
	double res;
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tax_form a;
	a.Input();
	a.Inputtax();
	a.Output();
	a.Outputtax();
	cout << "Налоговые выплаты за квартал составили: " << a.Result() << endl;
}