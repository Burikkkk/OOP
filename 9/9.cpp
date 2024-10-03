/*3. Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной области
«Аппаратное обеспечение компьютера». Функционал программы должен позволить собрать компьютер. 
На основе разработанной иерархии классов, реализованной в лабораторной работе «ОБРАБОТКА ИСКЛЮЧИТЕЛЬНЫХ СИТУАЦИЙ В
ЯЗЫКЕ С++», реализовать программу для работы с данными, используя потоки файлового ввода - вывода. Реализовать функции 
добавления данных в файл, удаления данных из файла, редактирования данных в файле, просмотра данных из файла, поиска данных 
по необходимым параметрам в файле.
Использовать функции open(), is_open(), bad(), good(), close(), eof(), fail() для анализа состояния файла, 
перегрузить операторы вывода в поток << и считывания из потока >> , использовать функции seekg(), seekp(), tellg().*/
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
const type_info& OF = typeid(ofstream);
const type_info& IF = typeid(ifstream);

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
				(wcheck[i] < '0' || wcheck[i] > '9') && wcheck[i] != '-')
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

int Length_file(string name)
{
	ifstream f;
	f.open(name, ios::in);
	int i = 0;
	if (!f.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		char a;
		while (!f.eof())
		{
			f.get(a);
			if (a == '\n') i++;
		}
	}
	f.close();
	return i;
}
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

Socket StrToSocket(string s) 
{
	if(s=="AM3") return Socket::AM3;
	if(s=="AM4") return Socket::AM4;
	if (s == "AM5") return Socket::AM5;
	if (s == "LGA1200") return Socket::LGA1200;
	if (s == "LGA1700") return Socket::LGA1700;
}

RAM_type StrToRam(string s) 
{
	if(s=="DDR3") return RAM_type::DDR3; 
	if (s == "DDR4") return RAM_type::DDR4; 
	if (s == "DDR5") RAM_type::DDR5; 
}

class Motherboard
{
public:
	Motherboard(Socket socket, int ram_slots);
	Motherboard() {};
	int GetRamSlots() const { return ram_slots; }
	Socket GetSocket() const { return socket; }
	friend ostream& operator <<(ostream& os, const Motherboard& motherboard);
	friend istream& operator >>(istream& is, Motherboard& motherboard);
private:
	
	int ram_slots;
	Socket socket;
};

Motherboard::Motherboard(Socket socket, int ram_slots)
{
	this->socket = socket;
	this->ram_slots = ram_slots;
}

ostream& operator <<(ostream& os, const Motherboard& motherboard)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << motherboard.ram_slots << endl << OutputSocketstr(motherboard.GetSocket()) << endl;
	}
	else {
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(46) << "***Материнская плата***" << setw(26) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << "Количество слотов оперативной памяти " << motherboard.ram_slots << setw(34) << "|" << endl;
		os << "|" << "Сокет " << OutputSocketstr(motherboard.GetSocket());
		if (size(OutputSocketstr(motherboard.GetSocket())) == 3)
			os << setw(63) << "|" << endl;
		else
			os << setw(59) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
	}
	return os;
}

istream& operator >>(istream& is, Motherboard& motherboard)
{
	const type_info& t = typeid(is);
	if(IF==t)
	{ 
		string s;
		is >> motherboard.ram_slots;
		is >> s;
		motherboard.socket=StrToSocket(s);
	}
	else {
		cout << "Введите количество слотов оперативной памяти" << endl;
		motherboard.ram_slots = CinIntErrorCheck(1, 4);
		motherboard.socket = ChoiceSocket();
	}
	return is;
}

class Processor
{
public:
	Processor(Socket socket, RAM_type ram_type, string name);
	Processor() {};
	Socket GetSocket() const { return socket; }
	RAM_type GetRAMType() const { return ram_type; }
	string GetName() const { return name; }
	friend ostream& operator <<(ostream& os, const Processor& processor);
	friend istream& operator >>(istream& is, Processor& processor);
private:
	
	string name;
	RAM_type ram_type;
	Socket socket;
};

ostream& operator <<(ostream& os, const Processor& processor)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << processor.name << endl << OutputRAMstr(processor.GetRAMType()) 
			<<endl<< OutputSocketstr(processor.GetSocket()) << endl;
	}
	else {
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(42) << "***Процессор***" << setw(30) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << "Название процессора " << processor.name << setw(52 - size(processor.name)) << "|" << endl;
		os << "|" << "Тип памяти " << OutputRAMstr(processor.GetRAMType()) << setw(57) << "|" << endl;
		os << "|" << "Сокет " << OutputSocketstr(processor.GetSocket());
		if (size(OutputSocketstr(processor.GetSocket())) == 3)
			os << setw(63) << "|" << endl;
		else
			os << setw(59) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
	}
	return os;
}

istream& operator >>(istream& is, Processor& processor)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		string s ,r;
		is >> processor.name;
		is >> r;
		is >> s;
		processor.ram_type = StrToRam(r);
		processor.socket = StrToSocket(s);

	}
	else 
	{
		cout << "Введите название процессора" << endl;
		processor.name = CinStringSymIntErrorCheck();
		processor.ram_type = ChoiceRam();
		processor.socket = ChoiceSocket();
	}
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
	RAM_type GetRAMType() const { return ram_type; }
	int GetMemory() const { return memory; }
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
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << ram.memory << endl << OutputRAMstr(ram.GetRAMType()) << endl;
	}
	else {
		os << ram.memory << " Гб." << " Тип памяти " << OutputRAMstr(ram.GetRAMType());
	}
	return os;
}

istream& operator >>(istream& is, RAM& ram)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		string r;
		is >> ram.memory;
		is >> r;
		ram.ram_type = StrToRam(r);

	}
	else
	{
		ram.ram_type = ChoiceRam();
		cout << "Введите объем памяти" << endl;
		is >> ram.memory;
	}
	return is;
}

class PSU //блок питания power supply unit
{
public:
	PSU(int wattage) {
		this->wattage = wattage;
	};
	PSU() {};
	int GetWattage() const { return wattage; }
	friend ostream& operator <<(ostream& os, const PSU& psu);
	friend istream& operator >>(istream& is, PSU& psu);
private:
	int wattage; //мощность
};

ostream& operator <<(ostream& os, const PSU& psu)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << psu.wattage << endl;
	}
	else {
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(45) << "***Блок питания***" << setw(27) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << "Мощность блока питания " << psu.wattage << " Вт";
		int k = 0, x = psu.wattage;
		while (x >= 1)
		{
			x /= 10;
			k++;
		}
		os << setw(46 - k) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
	}
	return os;
}

istream& operator >>(istream& is, PSU& psu)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		is >> psu.wattage;
	}
	else
	{
		cout << "Введите мощность блока питания, Вт" << endl;
		psu.wattage = CinIntErrorCheck(0, 2000);
	}
	return is;
}

class Disk
{
public:
	Disk(int memory) { this->memory = memory; };
	Disk() {};
	int GetMemory() const { return memory; }
	friend ostream& operator <<(ostream& os, const Disk& disk);
	friend istream& operator >>(istream& is, Disk& disk);
private:
	int memory;
};

ostream& operator <<(ostream& os, const Disk& disk)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << disk.memory << endl;
	}
	else {
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(40) << "***Диск***" << setw(32) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << "Объем памяти диска " << disk.memory << " Гб";
		int k = 0, x = disk.memory;
		while (x >= 1)
		{
			x /= 10;
			k++;
		}
		os << setw(50 - k) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
	}
	return os;
}

istream& operator >>(istream& is, Disk& disk)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		is >> disk.memory;
	}
	else
	{
		cout << "Введите объем памяти диска, Гб" << endl;
		disk.memory = CinIntErrorCheck(0, 10000);
	}
	return is;
}

class Fan //вентилятор
{
public:
	Fan(int RPM) { this->RPM = RPM; };
	Fan() {};
	int GetRPM() const { return RPM; }
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
	Socket GetSocket() const { return socket; }
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
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << cooler.RPM << endl<< OutputSocketstr(cooler.GetSocket())<<endl;
	}
	else {
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(40) << "***Кулер***" << setw(32) << "|" << endl;
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
		os << setw(56 - k) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
	}
	return os;
}
istream& operator >>(istream& is, Cooler& cooler)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		string s;
		is >> cooler.RPM;
		is >> s;
		cooler.socket = StrToSocket(s);
	}
	else
	{
		cooler.socket = ChoiceSocket();
		cout << "Введите RPM вентилятора" << endl;
		cooler.RPM = CinIntErrorCheck(0, 5000);
	}
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
	const type_info& t = typeid(is);
	if (IF == t)
	{
		is >> comp.motherboard;
		try
		{
			is >> comp.processor;
			if (comp.motherboard.GetSocket() != comp.processor.GetSocket())
				throw("Сокеты материнской платы и процессора не совпадают. ");
		}
		catch (const char* message) {
			cout << "Вызвано исключение. " << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
		
		string s;
		comp.ram = new RAM[comp.motherboard.GetRamSlots()];
		for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
		{
			is >> comp.ram[i];
			try {
				if (comp.ram[i].GetRAMType() != comp.processor.GetRAMType())
					throw("Типы памяти не совпадают");
			}
			catch (const char* message) {
				cout << endl << "Вызвано исключение." << message << endl;
				cout << "Компьютер сломался." << endl;
				exit(0);
			}
		}
		is >> comp.psu;
		is >> comp.disk;
		try
		{
			is >> comp.cooler;
			if (comp.motherboard.GetSocket() != comp.cooler.GetSocket())
				throw("Сокеты материнской платы и кулера не совпадают.");
		}
		catch (const char* message) {
			cout << "Вызвано исключение." << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
	}
	else
	{
		int m;
		is >> comp.motherboard;
		try
		{
			is >> comp.processor;
			if (comp.motherboard.GetSocket() != comp.processor.GetSocket())
				throw("Сокеты материнской платы и процессора не совпадают. ");
		}
		catch (const char* message) {
			cout << "Вызвано исключение. " << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
		
		is >> comp.psu;
		comp.ram = new RAM[comp.motherboard.GetRamSlots()];
		for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
		{

			cout << "Слот " << i + 1 << ". Введите объем оперативной памяти, Гб(0-если не установлена)" << endl;
			m = CinIntErrorCheck(0, 5000);
			comp.ram[i] = RAM(m, comp.processor.GetRAMType());
			try {
				if (comp.ram[i].GetRAMType() != comp.processor.GetRAMType())
					throw("Типы памяти не совпадают");
			}
			catch (const char* message) {
				cout << endl << "Вызвано исключение." << message << endl;
				cout << "Компьютер сломался." << endl;
				exit(0);
			}
		}
		is >> comp.disk;
		
		try
		{
			is >> comp.cooler;
			if (comp.motherboard.GetSocket() != comp.cooler.GetSocket())
				throw("Сокеты материнской платы и кулера не совпадают.");
		}
		catch (const char* message) {
			cout << "Вызвано исключение." << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
	}
	return is;
}

ostream& operator <<(ostream& os, const Computer& comp)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << comp.motherboard << endl;
		try
		{
			os	<< comp.processor << endl;
			if (comp.motherboard.GetSocket() != comp.processor.GetSocket())
				throw("Сокеты материнской платы и процессора не совпадают. ");
		}
		catch (const char* message) {
			cout << "Вызвано исключение. " << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
		for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
		{
			try {
				os << comp.ram[i]<<endl;
				if (comp.ram[i].GetRAMType() != comp.processor.GetRAMType())
					throw("Типы памяти не совпадают");
			}
			catch (const char* message) {
				cout << endl << "Вызвано исключение." << message << endl;
				cout << "Компьютер сломался." << endl;
				exit(0);
			}
		}
		os << comp.psu << endl; 
		os << comp.disk << endl;
		try
		{
			os << comp.cooler<<endl;
			if (comp.motherboard.GetSocket() != comp.cooler.GetSocket())
				throw("Сокеты материнской платы и кулера не совпадают.");
		}
		catch (const char* message) {
			cout << "Вызвано исключение." << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
	}
	else {
		os << "Характеристики компьютера:" << endl;
		os << comp.motherboard;
		try
		{
			os << comp.processor;
			if (comp.motherboard.GetSocket() != comp.processor.GetSocket())
				throw("Сокеты материнской платы и процессора не совпадают. ");
		}
		catch (const char* message) {
			cout << "Вызвано исключение. " << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
		os << "+-----------------------------------------------------------------------+" << endl;
		os << "|" << setw(47) << "***Оперативная память***" << setw(25) << "|" << endl;
		os << "+-----------------------------------------------------------------------+" << endl;
		for (int i = 0; i < comp.motherboard.GetRamSlots(); i++)
		{
			os << "|" << "Слот " << i + 1 << ". Объем памяти ";
			try {
				os << comp.ram[i];
				if (comp.ram[i].GetRAMType() != comp.processor.GetRAMType())
					throw("Типы памяти не совпадают");
			}
			catch (const char* message) {
				cout << endl << "Вызвано исключение." << message << endl;
				cout << "Компьютер сломался." << endl;
				exit(0);
			}
			int k = 0, x = comp.ram[i].GetMemory();
			while (x >= 1)
			{
				x /= 10;
				k++;
			}
			os << setw(31 - k) << "|" << endl;
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
			cout << "Вызвано исключение." << message << endl;
			cout << "Компьютер сломался." << endl;
			exit(0);
		}
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
	default: return("Ошибка");
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
	default: return("Ошибка");
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
	if (ch <= count || ch < 1)
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
				comp.ram[j].SetMemory(comp.ram[j + 1].GetMemory());
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
	cout << "Введите объем памяти для поиска" << endl;
	find = CinIntErrorCheck(0, 10000);
	for (int i = 0; i < n; i++)
	{
		if (find == comp.ram[i].GetMemory())
		{
			cout << "Оперативная память объема " << find << " установлена в слот " << i + 1 << endl;
			a = 1;
		}
	}
	if (!a) {
		cout << "Слот не найден." << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice, out;
	string name = "comp1.txt";
	Computer comp;
	ofstream f;
	ifstream f1;
	while (TRUE)
	{
		cout << "1-Добавление данных в файл" << endl
			<< "2-Просмотр данных из файла" << endl
			<< "3-Редактирование файла" << endl
			<< "4-Удаление данных из файла" << endl
			<< "5-Поиск данных" << endl
			<< "0-Выход" << endl;
		choice = CinIntErrorCheck(0, 5);
		switch (choice)
		{
		case 1:
			cout.setf(ios::right);
			cout.width(70);
			cout << "Давайте соберем новый компьютер!!" << endl;
			cout.unsetf(ios::right);
			cin >> comp;
			f.open(name);
			if (!f.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				f.seekp(0);
				f << comp;
				cout << "Данные были записаны в файл." << endl;
			}
			f.close();
			break;
		case 2:
			if (Length_file(name) == 0)
			{
				cout << "Файл пуст" << endl;
				break;
			}
			f1.open(name);
			if (!f1.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				
				f1.seekg(0);
				cout << "Указатель на позиции: " << f1.tellg();
				f1 >> comp;
				
			}
			f1.close();
			cout << "Данные из файла" << endl;
			cout << comp;
			break;
		case 3:
			if (Length_file(name) == 0)
			{
				cout << "Файл пуст" << endl;
				break;
			}
			f1.open(name);
			if (!f1.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				
				f1 >> comp;

			}
			f1.close();
			cout << "Вывести исходные данные? 1-Да, 2-Нет" << endl;
			out = CinIntErrorCheck(1, 2);
			if (out == 1)
				cout << comp;
			Change(comp);
			f.open(name);
			if (!f.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				f << comp;
				cout << "Данные были записаны в файл" << endl;
			}
			f.close();
			break;
		case 4:
			f.open(name, ios::trunc);
			if (!f.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				cout << "Файл очищен." << endl;
					/*<< "good()=" << f.good() << endl
					<< "bad()=" << f.bad() << endl
					<< "eof()=" << f.eof() << endl
					<< "fail()=" << f.fail() << endl;*/
				if (f.bad())
					cout << "Ошибка ввода-вывода при чтении"<<endl;
				else if (f.good())
					cout << "В потоке нет ошибок"<<endl;
				else if (f.fail())
					cout << "Неверный формат данных"<<endl;
				else if (f.eof())
					cout << "Достигнут конец файла" << endl;
			}
			f.close();
			break;
		case 5:
			if (Length_file(name) == 0) {
				cout << "Файл пуст" << endl;
				break;
			}
			f1.open(name);
			if (!f1.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				f1 >> comp;

			}
			f1.close();
			Find(comp);
			break;
		case 0: return 0;
		}
	}
	}
