/*3. Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной области
«Аппаратное обеспечение компьютера». Функционал программы должен позволить собрать компьютер. 
На основе иерархии классов, разработанной в лабораторной работе «ОБРАБОТКА ИСКЛЮЧИТЕЛЬНЫХ СИТУАЦИЙ В ЯЗЫКЕ С++»,
реализовать программу для работы с данными, используя потоки ввода-вывода. Реализовать функций просмотра, добавления, удаления,
редактирования, сортировки, поиска данных по необходимым параметрам. Использовать минимум 5 флагов форматирования. 
Сформировать табличный вывод всех данных. Использовать функции setf() и unsetf() для установки и сбрасывания флагов.         
Использовать функции eof(), fail(), good(), bad(), clear() для проверки состояния потока.*/
//boolalpha, dec, showpos, fixed, right
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <eh.h>
#include <fstream>
#include <iomanip>
using namespace std;
enum class Socket { AM3, AM4, AM5, LGA1200, LGA1700 }; //разъемы для процессоров
enum class RAM_type { DDR3, DDR4, DDR5 }; //типы оперативной памяти

int CinIntErrorCheck() {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ')) {
		rewind(stdin);
		cin.clear();
		cout << "Ошибка. Попробуйте ещё раз." << endl;
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
int CinIntErrorCheck(int min, int max) {
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
				(wcheck[i] < '0' || wcheck[i] > '9') && wcheck[i]!='-')
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
string OutputRAMstr(RAM_type r);
string OutputSocketstr(Socket s);

class InvalidSocket :public exception // класс исключений
{
public:
	InvalidSocket();
};

InvalidSocket::InvalidSocket() :exception()
{
	cout << "Исключение: разъемы не совпадают" << endl;
};

void TermFunc()
{
	cout << "Компьютер сломался." << endl;
	exit(0);
}

Socket ChoiceSocket() // AM3, AM4, AM5, LGA1200, LGA1700
{
	int a;
	cout << "Выберите сокет:\n1-AM3, 2-AM4, 3-AM5, 4-LGA1200, 5-LG1700" << endl;
	a = CinIntErrorCheck(1, 5);
	switch (a)
	{
	case 1: return Socket::AM3; break; //AMD
	case 2: return Socket::AM4; break;
	case 3: return Socket::AM5; break;
	case 4: return Socket::LGA1200; break; //Intel
	case 5: return Socket::LGA1700; break;
	}
}

RAM_type ChoiceRam() // DDR5, DDR4, DDR3
{
	int a;
	cout << "Выберите тип RAM:\n1-DDR3, 2-DDR4, 3-DDR5" << endl;
	a = CinIntErrorCheck(1, 3);
	switch (a)
	{
	case 1: return RAM_type::DDR3; break;
	case 2: return RAM_type::DDR4; break;
	case 3: return RAM_type::DDR5; break;
	}
}

class Motherboard
{
public:
	Motherboard(Socket socket, int ram_slots);
	Motherboard() {};
	int GetRamSlots() const{ return ram_slots; }
	void InputMotherboard();
	Socket GetSocket() const { return socket; }
	friend ostream& operator <<(ostream& os, const Motherboard& motherboard);
	friend istream& operator >>(istream& is, Motherboard& motherboard);
private:
	Socket socket;
	int ram_slots;
};

void Motherboard:: InputMotherboard() {
	int size;
	cout << "Введите количество слотов оперативной памяти" << endl;
	size = CinIntErrorCheck();
	ram_slots = size;
	Socket s;
	s = ChoiceSocket();
}

Motherboard::Motherboard(Socket socket, int ram_slots)
{
	this->socket = socket;
	this->ram_slots = ram_slots;
}

ostream& operator <<(ostream& os, const Motherboard& motherboard)
{
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|"<<setw(46) << "***Материнская плата***" << setw(26) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	os <<"|"<< "Количество слотов оперативной памяти " << motherboard.ram_slots << setw(34) << "|" << endl;
	os << "|" << "Сокет " << OutputSocketstr(motherboard.GetSocket());
	if(size(OutputSocketstr(motherboard.GetSocket()))==3)
		os<< setw(63) << "|" <<endl;
	else
		os << setw(59) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	return os;
}

istream& operator >>(istream& is, Motherboard& motherboard)
{
	cout << "Введите количество слотов оперативной памяти" << endl;
	motherboard.ram_slots=CinIntErrorCheck(1,4);
	motherboard.socket = ChoiceSocket();
	return is;
}

class Processor
{
public:
	Processor(Socket socket, RAM_type ram_type, string name);
	Processor() {};
	Socket GetSocket() const{ return socket; }
	RAM_type GetRAMType() const{ return ram_type; }
	string GetName() const{ return name; }
	friend ostream& operator <<(ostream& os, const Processor& processor);
	friend istream& operator >>(istream& is, Processor& processor);
private:
	Socket socket;
	RAM_type ram_type;
	string name;
};

ostream& operator <<(ostream& os, const Processor& processor)
{
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << setw(42)<< "***Процессор***" << setw(30) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << "Название процессора " << processor.name << setw(52-size(processor.name)) << "|" << endl;
	os << "|" << "Тип памяти " << OutputRAMstr(processor.GetRAMType()) << setw(57) << "|" <<endl;
	os << "|" << "Сокет " << OutputSocketstr(processor.GetSocket());
	if (size(OutputSocketstr(processor.GetSocket())) == 3)
		os << setw(63) << "|" << endl;
	else
		os << setw(59) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	return os;
}

istream& operator >>(istream& is, Processor& processor) 
{
	cout << "Введите название процессора" << endl;
	processor.name = CinStringSymIntErrorCheck();
	processor.ram_type = ChoiceRam();
	processor.socket = ChoiceSocket();
	return is;
}

Processor::Processor(Socket socket, RAM_type ram_type, string name)
{
	this->socket = socket;
	this->ram_type = ram_type;
	this->name = name;
}

class RAM
{
public:
	RAM(int memory, RAM_type ram_type);
	RAM() {};
	RAM_type GetRAMType() const{ return ram_type; }
	int GetMemory() const{ return memory; }
	void SetMemory(int memory) { this->memory = memory; }
	void SetRamType(RAM_type ram_type) { this->ram_type = ram_type; }
	friend ostream& operator <<(ostream& os, const RAM& ram);
	friend istream& operator >>(istream& is, RAM& ram);
private:
	double memory;
	RAM_type ram_type;
};

RAM::RAM(int memory, RAM_type ram_type)
{
	this->memory = memory;
	this->ram_type = ram_type;
}

ostream& operator <<(ostream& os, const RAM& ram)
{
	os << ram.memory <<" Гб." << " Тип памяти " << OutputRAMstr(ram.GetRAMType());
	return os;
}

istream& operator >>(istream& is, RAM& ram)
{
	ram.ram_type = ChoiceRam();
	cout << "Введите объем памяти" << endl;
	is >> ram.memory;
	return is;
}

class PSU //блок питания power supply unit
{
public:
	PSU(int wattage) {
		this->wattage = wattage;
	};
	PSU() {};
	int GetWattage() const{ return wattage; }
	friend ostream& operator <<(ostream& os, const PSU& psu);
	friend istream& operator >>(istream& is, PSU& psu);
private:
	int wattage; //мощность
};

ostream& operator <<(ostream& os, const PSU& psu)
{
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << setw(45) << "***Блок питания***" << setw(27) << "|"  << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << "Мощность блока питания " << psu.wattage << " Вт";
	int k = 0, x = psu.wattage;
	while (x >= 1)
	{
		x /= 10;
		k++;
	}
	os << setw(46-k) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	return os;
}

istream& operator >>(istream& is, PSU& psu)
{
	cout << "Введите мощность блока питания, Вт" << endl;
	psu.wattage = CinIntErrorCheck(0, 2000);
	return is;
}

class Disk
{
public:
	Disk(int memory) { this->memory = memory; };
	Disk() {};
	int GetMemory() const{ return memory; }
	friend ostream& operator <<(ostream& os, const Disk& disk);
	friend istream& operator >>(istream& is, Disk& disk);
private:
	int memory;
};

ostream& operator <<(ostream& os, const Disk& disk)
{
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << setw(40) << "***Диск***" << setw(32) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	os.setf(ios::showpos);
	os << "|" << "Объем памяти диска " << disk.memory << " Гб";
	os.unsetf(ios::showpos);
	int k = 0, x = disk.memory;
	while (x >= 1)
	{
		x /= 10;
		k++;
	}
	os << setw(49-k) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	return os;
}

istream& operator >>(istream& is, Disk& disk)
{
	cout << "Введите объем памяти диска, Гб" << endl;
	disk.memory = CinIntErrorCheck(0, 10000);
	return is;
}

class Fan //вентилятор
{
public:
	Fan(int RPM) { this->RPM = RPM; };
	Fan() {};
	int GetRPM() const{ return RPM; }
	friend ostream& operator <<(ostream& os, const Fan& fan);
	friend istream& operator >>(istream& is, Fan& fan);
protected:
	int RPM; //revolutios per minute обороты
};

ostream& operator <<(ostream& os, const Fan& fan)
{
	os << "RPM вентилятора " << fan.RPM << endl;
	return os;
}
istream& operator >>(istream& is, Fan& fan) 
{
	cout << "Введите RPM вентилятора" << endl;
	fan = CinIntErrorCheck(0, 5000);
	return is;
}

class Cooler : public Fan
{
public:
	Cooler(Socket socket, int RPM);
	Cooler() {};
	Socket GetSocket() const{ return socket; }
	friend ostream& operator <<(ostream& os, const Cooler& cooler);
	friend istream& operator >>(istream& is, Cooler& cooler);
private:
	Socket socket;
};

Cooler::Cooler(Socket socket, int RPM)
{
	this->socket = socket;
	this->RPM = RPM;
}

ostream& operator <<(ostream& os, const Cooler& cooler)
{
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|"<< setw(40) << "***Кулер***" << setw(32) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << "Сокет " << OutputSocketstr(cooler.GetSocket());
	if (size(OutputSocketstr(cooler.GetSocket())) == 3)
		os << setw(63) << "|" << endl;
	else
		os << setw(59) << "|" << endl;
	os << "|" << "RPM вентилятора " << cooler.RPM;
	int k = 0, x = cooler.RPM;
	while (x >= 1)
	{
		x /= 10;
		k++;
	}
	os<< setw(56-k) << "|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	return os;
}
istream& operator >>(istream& is, Cooler& cooler)
{
	cooler.socket = ChoiceSocket();
	cout << "Введите RPM вентилятора" << endl;
	cooler.RPM = CinIntErrorCheck(0, 5000);
	return is;
}

class Computer
{
public:
	Computer(Motherboard motherboard, Processor processor, PSU psu, Disk disk, Cooler cooler);
	Computer() {};
	~Computer();
	void Output();
	friend void Change(Computer& comp);
	friend void AddRAM(Computer& comp);
	friend void DeleteRAM(Computer& comp);
	friend void Sort(Computer& comp);
	friend void Find(Computer& comp);
	friend ostream& operator <<(ostream& os, const Computer& comp);
	friend istream& operator >>(istream& is, Computer& comp);
private:
	Motherboard motherboard; //агрегация (передается в конструктор)
	Processor processor; //агрегация
	RAM* ram; //композиция (создается в конструкторе)
	PSU psu; //агрегация
	Disk disk; //агрегация
	Cooler cooler; //агрегация
};

istream& operator >>(istream& is, Computer& comp)
{
	int m;
	is>>comp.motherboard;
	is>>comp.processor;
	is>>comp.psu;
	comp.ram = new RAM[comp.motherboard.GetRamSlots()];
	for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
	{
		cout << "Слот " << i + 1 << ". Введите объем оперативной памяти, Гб(0-если не установлена)" << endl;
		m = CinIntErrorCheck(0, 5000);
		comp.ram[i] = RAM(m, comp.processor.GetRAMType());
	}
	is>>comp.disk;
	is>>comp.cooler;
	return is;
}

ostream& operator <<(ostream& os, const Computer& comp)
{
	os << "Характеристики компьютера:" << endl;
	os << comp.motherboard;
	try 
	{
		os << comp.processor;
		if(comp.motherboard.GetSocket()!=comp.processor.GetSocket())
		throw("Сокеты материнской платы и процессора не совпадают. ");
	}
	catch (const char* message) { 
		cout << "Вызвано исключение. " << message<<endl;
		cout << "Компьютер сломался." << endl;
		exit(0);
	}
	os << "+-----------------------------------------------------------------------+" << endl;
	os << "|" << setw(47) << "***Оперативная память***" << setw(25)<<"|" << endl;
	os << "+-----------------------------------------------------------------------+" << endl;
	for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
	{
		os << "|" << "Слот " << i + 1 << ". Объем памяти ";
		try {
			os.setf(ios::fixed);
			os << setprecision(2) << comp.ram[i];
			os.unsetf(ios::fixed);
			if (comp.ram[i].GetRAMType() != comp.processor.GetRAMType())
				throw("Типы памяти не совпадают");
		}
		catch (const char* message) {
			cout <<endl<< "Вызвано исключение." << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
		int k = 0, x = comp.ram[i].GetMemory();
		while (x >= 1)
		{
			x /= 10;
			k++;
		}
		os << setw(28 -k) << "|" << endl;
	}
	os << "+-----------------------------------------------------------------------+" << endl;
	os << comp.psu;
	os << comp.disk;
	try
	{
		os << comp.cooler;
		if (comp.motherboard.GetSocket() != comp.cooler.GetSocket())
			throw("Сокеты материнской платы и кулера не совпадают.");
	}
	catch (const char* message) {
		cout << "Вызвано исключение." << message <<endl;
		cout << "Компьютер сломался." << endl;
		exit(0);
	}
	
	return os;
}

void OutputRAM(RAM_type r) // DDR5, DDR4, DDR3
{
	switch (r)
	{
	case RAM_type::DDR3: cout << "DDR3" << endl; break;
	case RAM_type::DDR4: cout << "DDR4" << endl; break;
	case RAM_type::DDR5: cout << "DDR5" << endl; break;
	}
}

string OutputRAMstr(RAM_type r) // DDR5, DDR4, DDR3
{
	switch (r)
	{
	case RAM_type::DDR3: return("DDR3"); break;
	case RAM_type::DDR4: return("DDR4"); break;
	case RAM_type::DDR5: return("DDR5"); break;
	}
}

Computer::Computer(Motherboard motherboard, Processor processor, PSU psu, Disk disk, Cooler cooler)
{
	int m;
	this->motherboard = motherboard;
	this->processor = processor;
	this->psu = psu;
	try
	{
		ram = new RAM[motherboard.GetRamSlots()];
		if (motherboard.GetRamSlots() == 0)
			throw 1;
		cout << "***Оперативная память***" << endl;
		for (int i = 0; i < motherboard.GetRamSlots(); i++)
		{
			cout << "Слот " << i + 1 << ". Введите объем оперативной памяти, Гб(0-если не установлена)" << endl;
			m = CinIntErrorCheck(0, 5000);
			try {
				ram[i] = RAM(m, ChoiceRam());
				if (ram[i].GetRAMType() != processor.GetRAMType())
					throw("Типы памяти не совпадают");
			}
			catch (const char* message) { // тип памяти не такой, как у процессора
				cout << "Вызвано исключение." << message;
				throw; //перенаправление 
			}
		}
		this->disk = disk;
		this->cooler = cooler;
	}
	catch (const int)
	{
		cout << "Исключение: в материнской плате 0 слотов для оперативной памяти" << endl;
		exit(0);
	}
	catch (bad_alloc exept) // исключение с new
	{
		cout << "Исключение: в материнской плате некорректное количество слотов для оперативной памяти" << endl;
		exit(0);
	}
	catch (...)
	{
		cout << "Компьютер сломался." << endl;
		exit(0);
	}
}

Computer::~Computer()
{
	cout << "Был вызван деструктор" << endl;
	delete[]ram;
}

void OutputSocket(Socket s)
{
	switch (s)
	{
	case Socket::AM3: cout << "AM3" << endl; break;
	case Socket::AM4: cout << "AM4" << endl; break;
	case Socket::AM5: cout << "AM5" << endl; break;
	case Socket::LGA1200: cout << "LGA1200" << endl; break;
	case Socket::LGA1700: cout << "LGA1700" << endl; break;
	}
}

string OutputSocketstr(Socket s)
{
	switch (s)
	{
	case Socket::AM3: return("AM3"); break;
	case Socket::AM4: return("AM4"); break;
	case Socket::AM5: return("AM5"); break;
	case Socket::LGA1200: return("LGA1200"); break;
	case Socket::LGA1700: return("LGA1700"); break;
	}
}

void Computer::Output()
{
	cout << "Характеристики компьютера:" << endl;
	cout << "***Материнская плата***" << endl;
	cout << "Количество слотов оперативной памяти " << motherboard.GetRamSlots() << endl;
	cout << "Разъем ";
	OutputSocket(motherboard.GetSocket());
	cout << "***Процессор***" << endl;
	cout << "Название процессора " << processor.GetName() << endl;
	cout << "Тип памяти ";
	OutputRAM(processor.GetRAMType());
	cout << "***Оперативная память***" << endl;
	for (int i = 0; i < motherboard.GetRamSlots(); i++)
	{
		cout << "Слот " << i + 1 << ". Объем памяти " << ram[i].GetMemory() << " Гб" << endl;
	}
	cout << "***Блок питания***" << endl;
	cout << "Мощность блока питания " << psu.GetWattage() << " Вт" << endl;
	cout << "***Диск***" << endl;
	cout << "Объем памяти диска " << disk.GetMemory() << " Гб" << endl;
	cout << "***Кулер***" << endl;
	cout << "RPM вентилятора " << cooler.GetRPM() << endl;
}

void Change(Computer& comp)
{
	int choice;
	cout << "Изменить:" << endl
		<< "1-Материнскую плату и озу" << endl
		<< "2-Процессор" << endl
		<< "3-Блок питания" << endl
		<< "4-Диск" << endl
		<< "5-Кулер" << endl
		<< "0-Выход" << endl;
	choice = CinIntErrorCheck(0, 5);
	switch (choice)
	{
	case 1: 
		cin >> comp.motherboard;
		comp.ram = new RAM[comp.motherboard.GetRamSlots()];
		for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
		{
			cout << "Слот " << i + 1 << ". Введите объем оперативной памяти, Гб(0-если не установлена)" << endl;
			int m = CinIntErrorCheck(0, 5000);
			comp.ram[i] = RAM(m, ChoiceRam());
		}
		break;
	case 2: 
		cin >> comp.processor; break;
	case 3: 
		cin >> comp.psu; break;
	case 4: 
		cin >> comp.disk; break;
	case 5: 
		cin >> comp.cooler; break;
	case 0: return;
	}
}

void AddRAM(Computer& comp)
{
	bool a = 0;
	for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
	{
		if (comp.ram[i].GetMemory() == 0)
		{
			cout << "Слот " << i + 1 << ". Введите объем оперативной памяти, Гб" << endl;
			int m = CinIntErrorCheck(0, 5000);
			comp.ram[i] = RAM(m, ChoiceRam());
			a = 1;
		}
	}
	if (!a)
		cout << "Все слоты заняты. Сначала освободите слот." << endl;
}

void DeleteRAM(Computer& comp)
{
	int count = comp.motherboard.GetRamSlots();
	int ch;
	while (!cin.eof()) {
		cout << "Из какого слота удалить память?" << endl;
		cin >> ch;
		cin.get();
		if (!cin.bad()) {
			rewind(stdin);
			break;
		}
		cin.clear();
		cout << "Ошибка ввода!" << endl;
		rewind(stdin);
	}
	if (ch <= count||ch<1)
	{
		comp.ram[ch - 1].SetMemory(0);
	}
	else
		cout << "Такого слота нет." << endl;
}

void Sort(Computer& comp)
{
	int n = comp.motherboard.GetRamSlots();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (comp.ram[j].GetMemory() > comp.ram[j + 1].GetMemory())
			{
				int temp_memory = comp.ram[j].GetMemory();
				RAM_type type = comp.ram[j].GetRAMType();
				comp.ram[j].SetMemory(comp.ram[j+1].GetMemory());
				comp.ram[j].SetRamType(comp.ram[j + 1].GetRAMType());
				comp.ram[j + 1].SetMemory(temp_memory);
				comp.ram[j + 1].SetRamType(type);
			}
}

void Find(Computer& comp)
{
	bool a = 0;
	int n = comp.motherboard.GetRamSlots();
	int find;
	while (!cin.eof()) {
		cout << "Введите объем памяти для поиска" << endl;
		cin >> find;
		cin.get();
		if (cin.good() && find > 0) {
			rewind(stdin);
			break;
		}
		cin.clear();
		cout << "Ошибка ввода!" << endl;
		rewind(stdin);
	}
	for (int i = 0; i < n; i++)
	{
		if (find == comp.ram[i].GetMemory())
		{
			cout << "Оперативная память объема " << find << " установлена в слот " << i + 1 << endl;
			a = 1;
		}
	}
	if (!a) {
		cout.setf(ios::boolalpha);
		cout << "Слот не найден. (" << a << ")" << endl;
		cout.unsetf(ios::boolalpha);
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice;
	cout.setf(ios::right);
	cout.width(70);
	cout << "Давайте соберем новый компьютер!!" << endl;
	cout.unsetf(ios::right);
	cout.setf(ios::dec);
	Computer comp;
	cin >> comp;
	cout.setf(ios::right);
	cout.width(70);
	cout << "Поздравляем!!! Вы собрали компьютер!!" << endl;
	cout.unsetf(ios::right);
	cout << comp;
	cout.setf(ios::right);
	cout.width(70);
	cout << endl<<"Оставьте положительный отзыв!!" << endl;
	cout.unsetf(ios::right);
	while (TRUE)
	{
		cout << "1-Функция редактирования" << endl
			<< "2-Функция добавления памяти" << endl
			<< "3-Функция удаления памяти" << endl
			<< "4-Функция сортировки" << endl
			<< "5-Функция поиска" << endl
			<< "0-Выход" << endl;
		choice = CinIntErrorCheck(0, 5);
		switch (choice)
		{
		case 1:
			Change(comp);
			break;
		case 2: 
			AddRAM(comp);
			break;
		case 3: 
			DeleteRAM(comp);
			break;
		case 4: 
			Sort(comp);
			break;
		case 5: 
			Find(comp);
			break;
		case 0: return 0;
		}
		cout << comp;
	}
}