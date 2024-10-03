/*Во всех вариантах индивидуальных заданий необходимо реализовать работу с контейнерами queue, stack, priority_queue, которые будут хранить
объекты классов по предметной области каталог книг. Класс должен содержать функционал по предметной области. 
Для контейнеров реализовать добавление, удаление, редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов. 
Необходимо создать удобное пользовательское меню и табличный вывод данных.*/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <stack>
#include <queue>
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
	Book() { title = "Учение убийцы", author = "Робин Хобб", size = 384; }
	Book(string title, string author, int size) { this->title = title, this->author = author, this->size = size; }
	Book(const Book& other) {
		title = other.title;
		author = other.author;
		size = other.size;
	}
	void SetTitle(string title) { this->title = title; };
	string GetTitle()const { return title; };

	friend ostream& operator <<(ostream& os, const Book& book);
	friend istream& operator >>(istream& is, Book& book);
	friend bool operator<(Book a, Book b);
	friend bool operator==(Book a, string b);
	friend bool operator==(Book a, Book b);
};

ostream& operator <<(ostream& os, const Book& book)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		os << book.author << " " << book.title << " " << book.size;
	}
	else {

		int k = 0, x = book.size;
		while (x >= 1)
		{
			x /= 10;
			k++;
		}
		os << "|" << book.title << setw(30-size(book.title)) <<"|" << book.author << setw(29- size(book.author))<<"|" << book.size << setw(23-k) << "|";
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
		book.size = CinIntErrorCheck(0, 3000);
	}
	return is;
}
bool operator<(Book a, Book b)
{
	return a.title < b.title;
}
bool operator==(Book a, string b)
{
	return a.title == b;
}
bool operator==(Book a, Book b)
{
	return a.title == b.title;
}



void funstack() {
	int choice;
	stack<Book> st;
	ofstream sbook;
	Book temp, temp1("Лесной маг", "Хобб", 678), temp2("Сквозь зеркала", "Дабо", 560),
		temp3("Ведьмак", "Сапковский", 632);
	st.push(temp1);
	st.push(temp2);
	st.push(temp3);
	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Просмотр всех книг (удаление)" << endl
			<< "3-Редактирование последней книги" << endl
			<< "4-Поиск последней книги" << endl
			<< "5-Вывод данных в файл" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 5);

		switch (choice)
		{
		case 1:
			cin >> temp;
			st.push(temp);
			break;
		case 2:
			if (!st.empty()) {
				cout << "+-----------------------------+----------------------------+----------------------+" << endl
					<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
					<< "+-----------------------------+----------------------------+----------------------+" << endl;
				while (!st.empty())
				{
					cout << st.top() << endl;
					cout << "+-----------------------------+----------------------------+----------------------+" << endl;
					st.pop();
				}
			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 3:
			if (!st.empty()) {
				st.pop();
				cin >> temp;
				st.push(temp);
			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 4:
			if (!st.empty()) {
				cout << "+-----------------------------+----------------------------+----------------------+" << endl
					<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
					<< "+-----------------------------+----------------------------+----------------------+" << endl;
					cout << st.top() << endl;
					cout << "+-----------------------------+----------------------------+----------------------+" << endl;

			}
			else
				cout << "Книг не найдено" << endl;
			break;		
		case 5:
			if (!st.empty())
			{
				sbook.open("book.txt");
				if (!sbook.is_open())
					cout << "Ошибка открытия файла" << endl;
				else
				{
					while (!st.empty())
					{
						sbook << st.top();
						sbook << endl;
						st.pop();

					}
				}
				sbook.close();
				cout << "Данные были записаны в файл" << endl;
			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 0: return;
		}

	}

}

void funqueue() {
	int choice;
	ofstream qbook;
	queue<Book> q;
	priority_queue<Book> prq;
	Book temp, temp1("Лесной маг", "Хобб", 678), temp2("Сквозь зеркала", "Дабо", 560),
		temp3("Ведьмак", "Сапковский", 632);
	q.push(temp1);
	q.push(temp2);
	q.push(temp3);
	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Просмотр всех книг (удаление)" << endl
			<< "3-Поиск последней книги" << endl
			<< "4-Поиск первой книги" << endl
			<< "5-Вывод данных в файл" << endl
			<< "6-priority_queue (сортировка)" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 6);

		switch (choice)
		{
		case 1:
			cin >> temp;
			q.emplace(temp);
			break;
		case 2:
			if (!q.empty()) {
				cout << "+-----------------------------+----------------------------+----------------------+" << endl
					<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
					<< "+-----------------------------+----------------------------+----------------------+" << endl;
				while (!q.empty())
				{
					cout << q.front() << endl;
					cout << "+-----------------------------+----------------------------+----------------------+" << endl;
					q.pop();
				}
			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 3:
			if (!q.empty()) {
				cout << "+-----------------------------+----------------------------+----------------------+" << endl
					<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
					<< "+-----------------------------+----------------------------+----------------------+" << endl;
				cout << q.back() << endl;
				cout << "+-----------------------------+----------------------------+----------------------+" << endl;

			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 4:
			if (!q.empty()) {
				cout << "+-----------------------------+----------------------------+----------------------+" << endl
					<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
					<< "+-----------------------------+----------------------------+----------------------+" << endl;
				cout << q.front() << endl;
				cout << "+-----------------------------+----------------------------+----------------------+" << endl;

			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 5:
			if (!q.empty())
			{
			qbook.open("book.txt");
			if (!qbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				while (!q.empty())
				{
					qbook << q.front();
					qbook << endl;
					q.pop();
					
				}
			}
			qbook.close();
			cout << "Данные были записаны в файл" << endl;
			}
			else
				cout << "Книг не найдено" << endl;
			break;
		case 6:
			prq.push(temp1);
			prq.push(temp2);
			prq.push(temp3);
			cout << "+-----------------------------+----------------------------+----------------------+" << endl
				<< "|" << "Название" << setw(22) << " |" << "Автор" << setw(24) << " |" << "Количество страниц" << setw(5) << "|" << endl
				<< "+-----------------------------+----------------------------+----------------------+" << endl;
			while (!prq.empty())
			{
				cout << prq.top() << endl;
				cout << "+-----------------------------+----------------------------+----------------------+" << endl;
				prq.pop();
			}
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
		cout << "1-stack" << endl
			<< "2-queue" << endl
			<< "0-exit" << endl;
		choice = CinIntErrorCheck(0, 2);
		system("cls");
		switch (choice)
		{
		case 1:
			funstack();
			break;
		case 2:
			funqueue();
			break;
		case 0: return 0;
		}
		system("cls");
	}
}