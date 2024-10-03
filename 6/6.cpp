/*3. Разработать набор классов (минимум 5) по теме «учет сотрудников ИТ-компании». Корректно реализовать связи между классами.
Использовать smart-указатели для создания программы учета сведений о сотрудниках и расчета для них заработной платы. В разработанном наборе классов
должен быть хотя бы один шаблонный класс. Все классы должны иметь методы получения и установки значений полей. Реализовать механизм транзакций,
который позволит откатывать изменения, внесенные в сведения о сотрудниках ИТ-организации. Предусмотреть возможность автоматического «отката»
к предыдущему состоянию данных о сотруднике, если текущее состояние является неудовлетворительным. Смоделировать данную ситуацию.
Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.*/
#include <iostream>
#include <string>
#include <windows.h>
#include<iomanip>
#include <memory>
using namespace std;
enum State { begin, middle };
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
			if ((!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'a' && wcheck[i] <= 'z') 
				&& !(wcheck[i] >= 'А' && wcheck[i] <= 'Я') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z')))
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

class Projects
{
public:
	Projects() {
		size = 3;
		names = new string[size];
		names[0] = "Зайчик";
		names[1] = "Ёлка";
		names[2] = "Лес";
	}
	Projects(int size, string& mas) {
		this->size = size;
		names = new string[size];
		for (int i = 0; i < size; i++)
		{
			names[i] = mas[i];
		}
	}
	Projects(const Projects& other) {
		this->size = other.size;
		names = new string[size];
		for (int i = 0; i < size; i++)
		{
			names[i] = other.names[i];
		}
	}

	void Input() {
		cout << "Введите количество текущих проектов" << endl;
		size = CinIntErrorCheck(1, 100);
		cout << "Введите название проектов" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << "  ";
			names[i] = CinStringSymErrorCheck();

		}
	}
	void Output() {
		cout << "Текущие проекты:" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << names[i] << endl;
		}
	}

	~Projects() {
		delete[]names;
	}
	int GetSize() { return size; }
	string GetNames(int i) { return names[i]; }
private:
	int size;
	string* names;
};


class Human
{
public:
	Human() {
		FIO = "Иванов Петр Петрович";
		birth_year = 2000;
	}
	Human(string FIO, int year) {
		this->FIO = FIO;
		birth_year = year;
	}
	Human(const Human& other) {
		FIO = other.FIO;
		birth_year = other.birth_year;
	}
	virtual void Input() {
		cout << "Введите ФИО сотрудника" << endl;
		FIO = CinStringSymErrorCheck();
		cout << "Введите год рождения" << endl;
		birth_year = CinIntErrorCheck(1923, 2005);
	}
	virtual void Output() {
		cout << "ФИО:" << setw(30) << "Год рождения:" << endl;
		cout << FIO << setw(30) << birth_year << endl;
	}
	void SetFIO(string FIO) { this->FIO = FIO; }
	void SetBirthYear(int birth_year) { this->birth_year = birth_year; }
	string GetFIO() { return FIO; }
	int GetBirthYear() { return birth_year; }

protected:
	string FIO;
	int birth_year;
};

class Employee : public Human
{
public:
	Employee() {
		position = "Junior";
		project = "Зайчик";
	}
	Employee(string pos, string pr) {
		position = pos;
		project = pr;
	}
	Employee(string pos, string pr, string FIO, int birth_year) {
		position = pos;
		project = pr;
		this->FIO = FIO;
		this->birth_year = birth_year;
	}
	Employee(const Employee& other) {
		position = other.position;
		project = other.project;
		FIO = other.FIO;
		birth_year = other.birth_year;
	}
	void Input(Projects& a) {
		Human::Input();
		cout << "Введите должность сотрудника" << endl;
		position = CinStringSymErrorCheck();
		cout << "Просмотреть текущие проекты? 1-Да, 2-Нет" << endl;
		int ch = CinIntErrorCheck(1, 2);
		if (ch == 1)
		{
			a.Output();
		}
		cout << "Введите проект" << endl;
		project = CinStringSymErrorCheck();
		bool check = 0;
		do {
			for (int i = 0; i < a.GetSize(); i++)
			{
				if (project == a.GetNames(i))
				{
					check = 1;
					break;
				}
			}
			if (check == 0) {
				cout << "Вы ввели несуществующий проект, повторите попытку" << endl;
				project = CinStringSymErrorCheck();
			}
		} while (check == 0);
	}
	void Output() {
		Human::Output();
		cout << "Должность:" << setw(25) << "Проект:" << endl;
		cout << position << setw(30) << project << endl;
	}
	void SetPosition(string pos) { this->position = pos; }
	void SetProject(string project) { this->project = project; }
	string GetPosition() { return position; }
	string GetProject() { return project; }
private:
	string position, project;
};



class Salary
{
public:
	Salary() {
		*moneyperday = 100;
		days = 21;
		years = 1;
	}
	Salary(double* perday, double days, double years)
	{
		*moneyperday = *perday;
		this->days = days;
		this->years = years;
	}
	Salary(const Salary& other)
	{
		*moneyperday = *other.moneyperday;
		days = other.days;
		years = other.years;
	}
	void Input() {
		cout << "Введите зарплату сотрудника в день" << endl;
		*moneyperday = CinDoubleErrorCheck(1, 500);
		cout << "Введите количество рабочих дней" << endl;
		days = CinDoubleErrorCheck(0, 31);
		cout << "Введите стаж работы" << endl;
		years = CinDoubleErrorCheck(0, 10);
	}
	void Output() {
		cout << "З/п:" << setw(30) << "Рабочие дни" << setw(30) << "Стаж:" << endl;
		cout << *moneyperday << setw(30) << days << setw(30) << years << endl;
		cout << "Зарплата за месяц составляет: " << (*moneyperday) * days * 0.2 * years << "$" << endl;
	}
	void SetDays(double days) { this->days = days; }
	void SetYears(double years) { this->years = years; }
	void SetMoney(double* money) { *moneyperday = (*money); }
	double GetDays() { return days; }
	double GetYears() { return years; }
	double* GetMoney() { return moneyperday.get(); }
private:
	double days, years;
	unique_ptr<double> moneyperday = make_unique<double>();
};

template <class T>
class Transaction {
public:
	Transaction() {
		prev = current = NULL;
	}
	Transaction(const Transaction& other) {
		current(new T(*(other.current)));
		prev(NULL);
	}
	~Transaction() {
		delete current;
		delete prev;
	}
	Transaction& operator=(const Transaction& obj)
	{
		if (this != &obj)
		{
			delete current;
			current = new T(*(obj.current));
		}
		return *this;
	}
	T* operator->() {
		return current;
	}
	int NewTransaction(Employee e) {
		delete prev;
		prev = current;
		current = new T(e);
		if (!current) return 0;
		return 1;

	}
	void Ok() {
		delete prev;
		prev = NULL;
	}
	void DeleteTransaction() {
		if (prev != NULL) {
			delete current;
			current = prev;
			prev = NULL;
		}
	}
	void ShowState(State state) {
		cout << "Данные ";
		if (!state) cout << "до начала транзакции: " << endl;
		else cout << "после выполнения транзакции: " << endl;
		if (prev)
		{
			cout << "prev:" << endl;
			prev->Output();
			cout << "current:" << endl;
			current->Output();
			cout << endl;
		}
		else
		{
			cout << "prev = NULL" << endl;
			cout << "current:" << endl;
			current->Output();
			cout << endl;
		}
	}
private:
	T* prev, * current;
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Projects a;
	a.Input();
	Employee first;
	first.Input(a);
	first.Output();
	Salary x;
	x.Input();
	x.Output();
	Transaction <Employee> y;
	cout << "--------------------------------------------------" << endl;
	y.NewTransaction(first);
	y.ShowState(State::begin);
	cout << "НАЧАЛЬНАЯ ИНИЦИАЛИЗАЦИЯ ПРОШЛА УСПЕШНО" << endl;
	cout << "--------------------------------------------------" << endl;
	Employee second("Senior", "Ёжик", "Ilya", 2004);
	cout << "ПЕРВАЯ ТРАНЗАКЦИЯ НАЧАТА СО ЗНАЧЕНИЕМ " << endl;
	second.Output();
	cout << "--------------------------------------------------" << endl;
	if (y.NewTransaction(second)) {
		y.ShowState(State::middle);
	}
	cout << "ПЕРВАЯ ТРАНЗАКЦИЯ ПРОШЛА УСПЕШНО" << endl;
	cout << "--------------------------------------------------" << endl;
	y.DeleteTransaction();
	cout << "ПЕРВАЯ ТРАНЗАКЦИЯ БЫЛА ОТМЕНЕНА" << endl;
	y.Ok();
	y.ShowState(State::middle);
	cout << "--------------------------------------------------" << endl;

	Employee third("Boss", "OOPIP", "Sasha Buraya", 2004);
	cout << "ВТОРАЯ ТРАНЗАКЦИЯ НАЧАТА CO ЗНАЧЕНИЕМ " << endl;
	third.Output();
	cout << "--------------------------------------------------" << endl;
	if (y.NewTransaction(third)) {
		y.ShowState(State::begin);
		cout << "--------------------------------------------------" << endl;
		y.Ok();
	}
	cout << "ВТОРАЯ ТРАНЗАКЦИЯ ПРОШЛА УСПЕШНО" << endl;
	y.ShowState(State::middle);
}