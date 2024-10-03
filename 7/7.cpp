/*3. Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной области
«Аппаратное обеспечение компьютера». Функционал программы должен позволить собрать компьютер. Сгенерировать минимум пять типов
исключительных ситуаций. Реализовать перенаправление исключительных ситуаций. Сгенерировать минимум одну исключительную ситуацию с
оператором new. Создать исключительную ситуацию в конструкторе и продемонстрировать вызов конструкторов и деструкторов. Задать
собственную функцию завершения. Создать собственный (пользовательский) класс исключения, сгенерировать исключение этого типа и обработать его.*/
#include <iostream>
#include <string>
#include <windows.h>
#include <eh.h>
using namespace std;
enum class Socket {AM3, AM4, AM5, LGA1200, LGA1700}; //разъемы для процессоров
enum class RAM_type {DDR3, DDR4, DDR5}; //типы оперативной памяти

int CinIntErrorCheck() {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ')) {
		rewind(stdin);
		cin.clear();
		//cin.ignore(100, '\n');
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
		//cin.ignore(100, '\n');
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

class InvalidSocket:public exception // класс исключений
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

class Motherboard
{
public:
	Motherboard(Socket socket, int ram_slots);
	Motherboard(){};
	int GetRamSlots() { return ram_slots; }
	Socket GetSocket() { return socket; }
private:
	Socket socket;
	int ram_slots;
};

Motherboard::Motherboard(Socket socket, int ram_slots)
{
	this->socket = socket;
	this->ram_slots = ram_slots;
}

class Processor
{
public:
	Processor(Socket socket, RAM_type ram_type, string name);
	Processor() {};
	Socket GetSocket() { return socket; }
	RAM_type GetRAMType() { return ram_type; }
	string GetName() { return name; }
private:
	Socket socket;
	RAM_type ram_type;
	string name;
};

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
	RAM_type GetRAMType() { return ram_type; }
	int GetMemory() { return memory; }
private:
	int memory;
	RAM_type ram_type;
};

RAM::RAM(int memory, RAM_type ram_type)
{
	this->memory = memory;
	this->ram_type = ram_type;
}

class PSU //блок питания power supply unit
{
public:
	PSU(int wattage) {
		this->wattage = wattage;};
	PSU() {};
	int GetWattage() { return wattage; }
private:
	int wattage; //мощность
};


class Disk
{
public:
	Disk(int memory) { this->memory = memory; };
	Disk() {};
	int GetMemory() { return memory; }
private:
	int memory;
};


class Fan //вентилятор
{
public:
	Fan(int RPM) { this->RPM = RPM; };
	Fan() {};
	int GetRPM() { return RPM; }
protected:
	int RPM; //revolutios per minute обороты
};


class Cooler: public Fan
{
public:
	Cooler(Socket socket, int RPM);
	Cooler() {};
	Socket GetSocket() { return socket; }
private:
	Socket socket;
};

Cooler::Cooler(Socket socket, int RPM)
{
	this->socket = socket;
	this->RPM = RPM;
}


class Computer
{
public:
	Computer(Motherboard motherboard, Processor processor, PSU psu, Disk disk, Cooler cooler);
	Computer() {};
	~Computer();
	void Output();
private: 
	Motherboard motherboard; //агрегация (передается в конструктор)
	Processor processor; //агрегация
	RAM *ram; //композиция (создается в конструкторе)
	PSU psu; //агрегация
	Disk disk; //агрегация
	Cooler cooler; //агрегация
};

RAM_type ChoiceRam() // DDR5, DDR4, DDR3
{
	int a;
	cout << "Выберите тип RAM:\n1-DDR3, 2-DDR4, 3-DDR5" << endl;
	a=CinIntErrorCheck(1,3);
	switch (a)
	{
	case 1: return RAM_type::DDR3; break;
	case 2: return RAM_type::DDR4; break;
	case 3: return RAM_type::DDR5; break;
	}
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
		m = CinIntErrorCheck(0, 3000);
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

Socket ChoiceSocket() // AM3, AM4, AM5, LGA1200, LGA1700
{
	int a;
	cout << "Выберите сокет:\n1-AM3, 2-AM4, 3-AM5, 4-LGA1200, 5-LG1700" << endl;
	a=CinIntErrorCheck(1,5);
	switch (a)
	{
	case 1: return Socket::AM3; break; //AMD
	case 2: return Socket::AM4; break;
	case 3: return Socket::AM5; break;
	case 4: return Socket::LGA1200; break; //Intel
	case 5: return Socket::LGA1700; break;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Давайте соберем новый компьютер!!" << endl;
	cout << "***Материнская плата***" << endl;
	Socket s;
	RAM_type r;
	s = ChoiceSocket();
	int size;
	string name;
	cout << "Введите количество слотов оперативной памяти" << endl;
	size=CinIntErrorCheck();
	rewind(stdin);
	cin.clear();
	Motherboard m(s, size);
	cout << "***Процессор***" << endl;
	cout << "Введите название процессора" << endl;
	name=CinStringSymIntErrorCheck();
	try {
		s = ChoiceSocket();
		if (m.GetSocket() != s)
			throw InvalidSocket();
	}
	catch (InvalidSocket) {
		cout << "Компьютер сломался." << endl;
		exit(0);
	}
	r = ChoiceRam();
	Processor p(s,r,name);
	cout << "***Блок питания***" << endl;
	cout << "Введите мощность блока питания, Вт" << endl;
	size=CinIntErrorCheck(0,2000);
	PSU psu(size);
	cout << "***Диск***" << endl;
	cout << "Введите объем памяти диска, Гб" << endl;
	size=CinIntErrorCheck(0,10000);
	Disk d(size);
	cout << "***Кулер***" << endl;
	cout << "Введите RPM вентилятора" << endl;
	size=CinIntErrorCheck(0,5000);
	s = ChoiceSocket();
	Cooler c(s, size);
	Computer comp(m, p, psu, d, c);
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "Поздравляем!!! Вы собрали компьютер!!" << endl;
	comp.Output();
	cout << "Оставьте положительный отзыв!!" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "Особое предложение только сегодня!! Попробуйте разделить на ноль.\n(Введите делитель)" << endl;
	double q, w;
	w = CinIntErrorCheck();
	set_terminate(TermFunc);
	try {
		if (w == 0||w=='0') throw "Деление на ноль";
		q = 1 / w;
		cout << "Результат: " << q << endl;
		
	}
	catch (int)
	{
		cout << "Попытка была хорошая." << endl;
	}
}