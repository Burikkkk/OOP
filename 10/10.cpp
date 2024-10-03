/*В каждом индивидуальном задании необходимо создать контейнеры list, vector, array, которые будут хранить объекты классов по предметной
области каталог книг.Для контейнера реализовать добавление, удаление, редактирование, вывод содержимого контейнера на экран и в файл, поиск и
сортировку элементов.Необходимо создать удобное пользовательское меню.*/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <windows.h>
#include <fstream>
using namespace std;
const type_info& OF = typeid(ofstream);
const type_info& IF = typeid(ifstream);
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

class Book {
private:
	string title, author;
	int size;
public:
	Book() { title = "None", author = "None", size = 0; }
	Book(string title, string author, int size) { this->title = title, this->author = author, this->size = size; }
	Book(const Book& other){
		title = other.title;
		author = other.author;
		size = other.size;
	}
	friend ostream& operator <<(ostream& os, const Book& book);
	friend istream& operator >>(istream& is, Book& book);
	friend bool operator<(Book a, Book b);
	friend bool operator==(Book a, string b);
};

ostream& operator <<(ostream& os, const Book& book)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << book.author << " " << book.title << " " << book.size;
	}
	else {
		os << "Название: " << book.title << endl << "Автор: " << book.author << endl << "Количество страниц: " << book.size << endl;
	}
	return os;
}
istream& operator >>(istream& is, Book& book)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		
	}
	else
	{
		cout << "Введите название книги" << endl;
		getline(is, book.title);
		book.title[0] = toupper(book.title[0]);
		cout << "Введите автора книги" << endl;
		getline(is, book.author);
		book.author[0] = toupper(book.author[0]);
		cout << "Введите количество страниц" << endl;
		book.size = CinIntErrorCheck(1, 5000);
	}
	return is;
}
bool operator<(Book a, Book b)
{
	return a.author < b.author;
}
bool operator==(Book a, string b)
{
	return a.title == b;
}

void FunVector()
{
	vector<Book> vbook;
	vector<Book>::iterator it = vbook.begin();
	ofstream fbook;
	Book temp;
	int choice = 0, size = 0, index = 0, min;
	bool a = 0;
	string title;
	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Удаление" << endl
			<< "3-Вставка" <<endl
			<< "4-Просмотр" << endl
			<< "5-Запись в файл" << endl
			<< "6-Поиск" << endl
			<< "7-Сортировка" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 7);
		switch (choice)
		{
		case 1:
			cout << "Сколько элементов добавить?" << endl;
			size = CinIntErrorCheck(0, 100);
			for (int i = 0; i < size; i++)
			{
				cin >> temp;
				vbook.push_back(Book(temp));
			}
			break;
		case 2:
			if (vbook.empty())
			{
				cout << "Сначала добавьте книги" << endl;
				break;
			}
			cout << "На какой позиции удалить книгу?" << endl;
			it = vbook.begin();
			index = CinIntErrorCheck(0,100);
			if (index > vbook.size()-1)
			{
				cout << "В векторе всего " << vbook.size()<< " книг/а/и" << endl;
			}
			else
			{
				vbook.erase(it+index);
				cout << "Книга удалена" << endl;
			}

			break;
		case 3:
			cout << "На какую позицию вставить книгу?" << endl;
			it = vbook.begin();
			index = CinIntErrorCheck(0,100);
			if (index > vbook.size())
			{
				cout << "В векторе всего " << vbook.size() << " книг/а/и" << endl;
			}
			else
			{
				cin >> temp;
				vbook.insert(it+index, temp);
			}
			break;
		case 4:
			for (int i = 0; i < vbook.size(); i++)
			{
				cout << vbook[i];
				cout << endl;
			}
			break;
		case 5:
			
			fbook.open("book.txt");
			if (!fbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				for (int i = 0; i < vbook.size(); i++)
				{
					fbook << vbook[i];
					fbook << endl;
				}
			}
			fbook.close();
			cout << "Данные были записаны в файл" << endl;
			break;
		case 6:
			cout << "Введите название искомой книги" << endl;
			getline(cin, title);
			for (int i = 0; i < vbook.size(); i++)
			{
				if(vbook[i] == title)
				{
					a = 1;
					cout << "Книга найдена" << endl;
					cout << vbook[i] << endl;
					
				}
			}
			if(a==0)
				cout << "Книга не найдена" << endl;
			break;
		case 7:
			size = vbook.size();
			for (int i = 0; i < size - 1; i++)
			{
				min = i;
				for (int j = i + 1; j < size; j++)
				{
					if (vbook[j] < vbook[min])
						min = j;
				}
				temp = vbook[i];
				vbook[i] = vbook[min];
				vbook[min] = temp;
			}
			cout << "Вектор отсортирован" << endl;
			break;
		case 0: return;
		}
	}
}

void FunList()
{
	list<Book> lbook;
	list<Book>::iterator it = lbook.begin();
	ofstream fbook;
	Book temp;
	int choice = 0, size = 0, index = 0;
	bool a = 0;
	string title;
	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Удаление" << endl
			<< "3-Вставка" << endl
			<< "4-Просмотр" << endl
			<< "5-Запись в файл" << endl
			<< "6-Поиск" << endl
			<< "7-Сортировка" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 7);
		switch (choice)
		{
		case 1:
			cout << "Сколько элементов добавить?" << endl;
			size = CinIntErrorCheck(0, 100);
			for (int i = 0; i < size; i++)
			{
				cin >> temp;
				lbook.push_back(Book(temp));
			}
			break;
		case 2:
			if (lbook.empty())
			{
				cout << "Сначала добавьте книги" << endl;
				break;
			}
			cout << "На какой позиции удалить книгу?" << endl;
			it = lbook.begin();
			index = CinIntErrorCheck(0, 100);
			if (index > lbook.size() - 1)
			{
				cout << "В списке всего " << lbook.size() << " книг/а/и" << endl;
			}
			else
			{
				advance(it, index);
				lbook.erase(it);
				cout << "Книга удалена" << endl;
			}
			break;
		case 3:
			cout << "На какую позицию вставить книгу?" << endl;
			it = lbook.begin();
			index = CinIntErrorCheck(0, 100);
			if (index > lbook.size())
			{
				cout << "В списке всего " << lbook.size() << " книг/а/и" << endl;
			}
			else
			{
				advance(it, index);
				cin >> temp;
				lbook.insert(it, temp);
			}
			break;
		case 4:
			it = lbook.begin();
			while (it != lbook.end()) {
				cout << *it << endl;
				it++;
			}
			break;
		case 5:
			it = lbook.begin();
			fbook.open("book.txt");
			if (!fbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				while (it != lbook.end())
				{
					fbook << *it;
					fbook << endl;
					it++;
				}
			}
			fbook.close();
			cout << "Данные были записаны в файл" << endl;
			break;
		case 6:
			it = lbook.begin();
			cout << "Введите название искомой книги" << endl;
			getline(cin, title);
			while (it != lbook.end())
			{
				if (*it == title)
				{
					a = 1;
					cout << "Книга найдена" << endl;
					cout << *it << endl;

				}
				it++;
			}
			if (a == 0)
				cout << "Книга не найдена" << endl;
			break;
		case 7:
			lbook.sort();
			cout << "Список отсортирован" << endl;
			break;
		case 0: return;
		}
	}
}

void FunArray()
{
	array<Book,5> abook;
	ofstream fbook;
	Book temp, temp1("None", "None", 0);
	int choice = 0, size = 0, index = 0, min=0;
	bool a = 0;
	string title;
	cout << "Заполните массив 5 элементами" << endl;
	for (int i = 0; i < abook.size(); i++)
	{
		cin >> temp;
		abook[i] = temp;
	}
	while (TRUE)
	{
		cout << "1-Удаление" << endl
			<< "2-Изменение" << endl
			<< "3-Просмотр" << endl
			<< "4-Запись в файл" << endl
			<< "5-Поиск" << endl
			<< "6-Сортировка" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 6);
		switch (choice)
		{
		case 1:
			cout << "Контейнер array не поддерживает удаление." << endl;
			break;
		case 2:
			cout << "На какой позиции изменить книгу?" << endl;
			index = CinIntErrorCheck(0, 100);
			if (index > abook.size()-1)
			{
				cout << "В массиве всего " << abook.size() << " книг/а/и" << endl;
			}
			else
			{
				cin >> temp;
				abook[index] = temp;
			}
			break;
		case 3:
			for (int i = 0; i < abook.size(); i++)
			{
				cout << abook[i];
				cout << endl;
			}
			break;
		case 4:

			fbook.open("book.txt");
			if (!fbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				for (int i = 0; i < abook.size(); i++)
				{
					fbook << abook[i];
					fbook << endl;
				}
			}
			fbook.close();
			cout << "Данные были записаны в файл" << endl;
			break;
		case 5:
			cout << "Введите название искомой книги" << endl;
			getline(cin, title);
			for (int i = 0; i < abook.size(); i++)
			{
				if (abook[i] == title)
				{
					a = 1;
					cout << "Книга найдена" << endl;
					cout << abook[i] << endl;

				}
			}
			if (a == 0)
				cout << "Книга не найдена" << endl;
			break;
		case 6:
			size = abook.size();
			for (int i = 0; i < size - 1; i++)
			{
				min = i;
				for (int j = i + 1; j < size; j++)
				{
					if (abook[j] < abook[min])
						min = j;
				}
				temp = abook[i];
				abook[i] = abook[min];
				abook[min] = temp;
			}
			cout << "Массив отсортирован" << endl;
			break;
		case 0: return;
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	int choice;
	while (TRUE)
	{
		cout << "1-vector" << endl << "2-list" << endl << "3-array" << endl << "0-Выход" << endl;
		choice = CinIntErrorCheck(0,3);
		system("cls");
		switch (choice)
		{
		case 1:
			FunVector();
			break;
		case 2: 
			FunList();
			break;
		case 3: 
			FunArray();
			break;
		case 0: return 0;
		}
		system("cls");
	}
}