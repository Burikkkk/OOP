/*Создать класс Array (массив), в котором реализовать методы для работы с одномерными массивами : пересечение и объединение массивов.
Память под массивы выделять в конструкторе динамически.Деструктор должен освобождать динамическую память, выделенную под массивы.В
класс добавить необходимый набор полей и методов (минимум два поля и два метода) на свое усмотрение.*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int Check();

class Array
{
private:
	int* data;
	int size;
public:

	Array()
	{
		this->size = 10;
		data = new int[size];
		//cout << "Массив создан" << endl;
	}

	Array(const Array &other)
	{
		this->size = other.size;
		this->data = new int[other.size];
		for (int i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i];
		}
		//cout << "Был вызван конструктор копирования" << endl;
	}

	Array(int size)
	{
		this->size = size;
		data = new int[size];
		//cout << "Массив создан" << endl;
	}
	
	~Array()
	{
		delete[]data;
		//cout << "Был вызван деструктор" << endl;
	}

	void Input();
	void Output();
	void Infile();
	void Outfile();
	void Ob(Array mas1, Array mas2);
	bool Peresec(Array mas1, Array mas2);
};

	void Array::Input() 
	{
		for (int i = 0; i < size; i++)
		{
			cout << "a[" << i << "]=";
			data[i]=Check();
		}
	}

	void Array::Output()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "a[" << i << "]=" << data[i] << "\t";
		}
		cout << endl;
	}

	void Array::Infile()
	{
		string name="file.txt";
		/*cout << "Введите имя файла: ";
		cin >> name;*/
		ofstream f;
		f.open(name);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{
			for(int i=0; i<size; i++)
			{
				f << *(data+i);
				f << "\t";
			}
			f << "\n";
			cout << "Данные были записаны в файл" << endl;
		}
		f.close();
	}

	void Array::Outfile()
	{		
		string name = "file.txt";
		/*cout << "Введите имя файла: ";
		cin >> name;*/
		ifstream f;
		f.open(name);
		if (!f.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{
			cout << "Данные из файла:" << endl;
			char a;
			while (f.get(a))
			{
				cout << a;
			}
		}
		f.close();
	}

	void Array::Ob(Array mas1, Array mas2) {
		
		for (int i = 0; i < mas1.size; i++)
		{
			data[i] = mas1.data[i];
		}
		for (int i = 0; i < mas2.size; i++)
		{
			data[mas1.size+i] = mas2.data[i];
		}
	}

	bool Array::Peresec(Array mas1, Array mas2) 
	{
		bool b=false, a=false;
		int k = 0;
		for (int j = 0; j < mas1.size; j++)
		{
			for (int i = 0; i < mas2.size; i++)
			{
				if (mas1.data[j] == mas2.data[i])
				{
					b = true;
					a = true;
					for (int l = 0; l < k; l++)
					{
						if (data[l] == mas1.data[j])
						{
							b = false;
						}
					}
					if (b)
					{
						data[k++] = mas1.data[j];
					}
				}
			}
		}
		if (a==true) 
		{
			this->size = k;
		}
		else
		{
			cout << "Нет общих элементов в массивах" << endl;
			this->size = 0;
		}
		return a;
	}


	int main()
	{
		setlocale(LC_ALL, "Ru");
		int size1 = 0, size2 = 0, size3;
		cout << "Введите размер массива 1" << endl;
		size1=Check();
		while (size1 <= 0 || size1 > 100)
		{
			cout << "Ошибка ввода. Введите положительное значение <100" << endl;
			size1 = Check();
		}
		Array mas1(size1);
		mas1.Input();
		cout << "Массив 1: " << endl;
		mas1.Output();
		cout << "Введите размер массива 2" << endl;
		size2 = Check();
		while (size2 <= 0 || size2 > 100)
		{
			cout << "Ошибка ввода. Введите положительное значение <100" << endl;
			size2 = Check();
		}
		Array mas2(size2);
		mas2.Input();
		cout << "Массив 2: " << endl;
		mas2.Output();
		cout << "Объединение массивов 1 и 2:" << endl;
		Array mas3(size2 + size1);
		mas3.Ob(mas1, mas2);
		mas3.Output();
		mas3.Infile();
		mas3.Outfile();
		Array mas4(size1 > size2 ? size1 : size2);
		if (mas4.Peresec(mas1, mas2) == 1) 
		{
			cout << "Пересечение массивов 1 и 2:" << endl;
			mas4.Output();
			mas4.Infile();
			mas4.Outfile();
		}
	}

	int Check()
	{
		int a;
		bool er = false;
		do
		{
			cin >> a;
			if(er=cin.fail())
			{
				cout << "Ошибка ввода. Введите целое значение" << endl;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (er);
		return a;
	}



