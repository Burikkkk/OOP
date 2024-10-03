#include "13.h"
#include "Factory.h"
#include "FactoryPol.h"

void setGuy(string& fio, double& exp, double& money) {
	cout << "Введите ФИО сотрудника" << endl;
	getline(cin, fio);
	rewind(stdin);
	fio[0] = toupper(fio[0]);
	for (int i = 0; i < fio.size() - 1; i++)
		if (fio[i] == ' ')
			fio[i + 1] = toupper(fio[i + 1]);
	cout << "Введите стаж работы" << endl;
	exp = cinDoubleErrorCheck(1, 100);
	cout << "Введите зарплату" << endl;
	money = cinDoubleErrorCheck(1, 100000000);
}

void newGuys(vector <IT_Guy*>& Guys)
{
	int choice, ch;
	double exp, money;
	string type,fio;
	Factory_IT_Guy* factory_guy=0;
	IT_Guy* guy=0;
	IT_Guy* guy_copy = 0;
	GFactory game;
	PFactory prog;
	NFactory nar;
	LFactory lev;
	CFactory con;
	IT_Project* project=0;
	Factory_Projectmaker* projectmaker=0;
	string menu2 = "1-Геймдизайнер\n2-Программист\n3-Нарративщик\n4-Левел-дизайнер\n5-Концепт-художник\n\n";
	string menu1 = "Выберите подход создания объекта:\n1-Фабрика\n2-Фабричный метод с аргументами\n3-Фабричный конструктор\n4-Полиморфная фабрика\n5-Полиморфное копирование\n0-Назад\n\n";
	vector <IT_Project*> Projects;
	while (TRUE)
	{
		system("cls");
		cout << menu1;
		choice = cinIntErrorCheck(0, 5);
		switch (choice)
		{
		case 1:
			cout << menu2;
			ch = cinIntErrorCheck(1, 5);
			switch (ch)
			{
				case 1:
					factory_guy = new GFactory();
					break;
				case 2:
					factory_guy = new PFactory();
					break;
				case 3:
					factory_guy = new NFactory();
					break;
				case 4:
					factory_guy = new LFactory();
					break;
				case 5:
					factory_guy = new CFactory();
					break;
			}
			guy = factory_guy->createFactory();
			guy->createITGuy();
			Guys.push_back(guy);
			delete factory_guy;
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			break;
		case 2:
			cout << menu2;
			ch = cinIntErrorCheck(1, 5);
			switch (ch)
			{
			case 1:
				type = game.typeFactory();
				break;
			case 2:
				type = prog.typeFactory();
				break;
			case 3:
				type = nar.typeFactory();
				break;
			case 4:
				type = lev.typeFactory();
				break;
			case 5:
				type = con.typeFactory();
				break;
			}
			guy = createFactory2(type);
			guy->createITGuy();
			Guys.push_back(guy);
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			break;
		case 3:
			cout << menu2;
			ch = cinIntErrorCheck(1, 5);
			setGuy(fio, exp, money);
			switch (ch)
			{
			case 1:
				factory_guy = new GFactory();
				break;
			case 2:
				factory_guy = new PFactory();
				break;
			case 3:
				factory_guy = new NFactory();
				break;
			case 4:
				factory_guy = new LFactory();
				break;
			case 5:
				factory_guy = new CFactory();
				break;
			}
			guy = factory_guy->createFactory(fio, money, exp);
			guy->createITGuy();
			Guys.push_back(guy);
			delete factory_guy;
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			break;
		case 4:
			cout << menu2;
			ch = cinIntErrorCheck(1, 5);
			setGuy(fio, exp, money);
			switch (ch)
			{
			case 1:
				guy = new Gamedesigner(fio,exp,money);
				break;
			case 2:
				guy = new Programmer(fio, exp, money);
				break;
			case 3:
				guy = new Narrative_designer(fio, exp, money);
				break;
			case 4:
				guy = new Level_designer(fio, exp, money);
				break;
			case 5:
				guy = new Сoncept_artist(fio, exp, money);
				break;
			}
			projectmaker = new Factory_Projectmaker;
			project = projectmaker->createProject(guy);
			project->createProject(guy);
			Guys.push_back(guy);
			Projects.push_back(project);
			cout << endl << "Существующие проекты:" << endl;
			for (int i = 0; i < Projects.size(); i++)
			{
				cout << Projects[i]->getType() << endl;
			}
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();

			break;
		case 5:
			cout << menu2;
			ch = cinIntErrorCheck(1, 5);
			setGuy(fio, exp, money);
			switch (ch)
			{
			case 1:
				factory_guy = new GFactory();
				break;
			case 2:
				factory_guy = new PFactory();
				break;
			case 3:
				factory_guy = new NFactory();
				break;
			case 4:
				factory_guy = new LFactory();
				break;
			case 5:
				factory_guy = new CFactory();
				break;
			}
			guy = factory_guy->createFactory(fio, money, exp);
			guy->createITGuy();
			Guys.push_back(guy);
			guy_copy = guy->cloneIT_Guy();
			Guys.push_back(guy_copy);
			delete factory_guy;
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			break;
		case 0:
			return;
		}
	}
}


void changeGuys(vector <IT_Guy*>& Guys)
{
	if (Guys.empty())
	{
		cout << "Сначала добавьте сотрудников" << endl;
		_getch();
		return;
	}
	IT_Guy* guy;
	Factory_IT_Guy* factory_guy = 0;
	string fio, type;
	double exp, money;
	bool a=0;
	cout << "Какого сотрудника редактировать? (Введите ФИО)" << endl;
	getline(cin, fio);
	rewind(stdin);
	fio[0] = toupper(fio[0]);
	for (int i = 0; i < fio.size() - 1; i++)
		if (fio[i] == ' ')
			fio[i + 1] = toupper(fio[i + 1]);
	for (auto i = Guys.begin(); i != Guys.end(); ++i)
	{		
		if ((*i)->getFIO() == fio)
		{
			a = 1;
			type = (*i)->getType();
			setGuy(fio, exp, money);
			if (type == G)
				factory_guy = new GFactory();
			else if (type == P)
				factory_guy = new PFactory();
			else if (type == N)
				factory_guy = new NFactory();
			else if (type == L)
				factory_guy = new LFactory();
			else if (type == C)
				factory_guy = new CFactory();
			guy = factory_guy->createFactory(fio, money, exp);
			guy->createITGuy();
			Guys.erase(i);
			Guys.push_back(guy);
			delete factory_guy;
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			return; 
		}
	}
	if (a == 0)
		cout << "Сотрудник не найден" << endl;
	_getch();
}

void deleteGuys(vector <IT_Guy*>& Guys)
{
	if (Guys.empty())
	{
		cout << "Сначала добавьте сотрудников" << endl;
		_getch();
		return;
	}
	string fio, type;
	bool a=0;
	cout << "Какого сотрудника уволить? (Введите ФИО)" << endl;
	getline(cin, fio);
	rewind(stdin);
	fio[0] = toupper(fio[0]);
	for (int i = 0; i < fio.size() - 1; i++)
		if (fio[i] == ' ')
			fio[i + 1] = toupper(fio[i + 1]);
	for (auto i = Guys.begin(); i != Guys.end(); ++i)
	{
		if ((*i)->getFIO() == fio)
		{
			a = 1;
			Guys.erase(i);
			cout << "Сотрудник был удален из бд" << endl;
			cout << endl << "Нажмите любую клавишу для продолжения..." << endl;
			_getch();
			return;
		}
	}
	if (a == 0)
		cout << "Сотрудник не найден" << endl;
}

void fileGuys(vector <IT_Guy*>& Guys)
{
	ofstream file;
	if (Guys.empty())
	{
		cout << "Сначала добавьте сотрудников" << endl;
		_getch();
		return;
	}
	file.open("Guys.txt");
	if (!file.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		for (int i = 0; i < Guys.size(); i++)
		{
			file << Guys[i]->getFIO() << endl << Guys[i]->getExp() << "\t" << Guys[i]->getMoney() << endl;
		}
	}
	file.close();
	cout << "Данные были записаны в файл" << endl;
	_getch();
}

void viewGuys(vector <IT_Guy*>& Guys)
{
	if (Guys.empty())
	{
		cout << "Сотрудников нет" << endl;
		_getch();
		return;
	}
	cout << "+------------------------------------------------+------------------+-----------------+" << endl
		<< "|" << "ФИО" << setw(46) << "|" << "Стаж работы" << setw(8) << "|" << "Зарплата" << setw(10) << "|" << endl
		<< "+------------------------------------------------+------------------+-----------------+" << endl;
	for (int i = 0; i < Guys.size(); i++)
	{
		int m = 0, e = 0;
		double exp = Guys[i]->getExp(), money=Guys[i]->getMoney();
		while (exp >= 1)
		{
			exp /= 10;
			e++;
		}
		while (money >= 1)
		{
			money /= 10;
			m++;
		}
		cout << "|" << Guys[i]->getFIO() << setw(49 - size(Guys[i]->getFIO())) << "|"
			<< Guys[i]->getExp() << setw(17 - e) << "|" << Guys[i]->getMoney() << setw(16 - m) << "|" << endl;
	}
	cout << "+------------------------------------------------+------------------+-----------------+" << endl;
	_getch();
}

int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	vector <IT_Guy*> Guys;
	int choice;
	string menu1 = "1-Создание\n2-Редактирование\n3-Удаление\n4-Запись в файл\n5-Просмотр\n0-Выход\n\n";
	while (TRUE)
	{
		system("cls");
		cout << fixed << setprecision(1) << menu1;
		choice = cinIntErrorCheck(0, 5);
		system("cls");
		switch (choice)
		{
		case 1:
			newGuys(Guys);
			break;
		case 2:
			changeGuys(Guys);
			break;
		case 3:
			deleteGuys(Guys);
			break;
		case 4:
			fileGuys(Guys);
			break;
		case 5:
			viewGuys(Guys);
			break;
		case 0:
			return 0;
			break;
		}
	}

}

