/*В каждом индивидуальном задании необходимо создать контейнеры, которые будут хранить объекты классов по предметной области,каталог книг.
Для контейнера реализовать добавление, удаление, редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов.
Необходимо создать удобное пользовательское меню. Во всех вариантах индивидуальных заданий необходимо реализовать работу с контейнерами 
map, set, multimap, multiset, unordered_map, unordered_set, unordered_multimap, unordered_multiset.*/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
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


class MyHash
{
public:
	size_t operator()(const Book& b) const
	{
		string temp= b.GetTitle();
		int res=0;
		char* asci = new char[size(temp) + 1];
		int i;
		for (i = 0; i < size(temp); i++)
		{
			asci[i] = temp[i];
			res += int(asci[i]);
		}
		return res;
	}
	size_t operator()(const string& b) const
	{
		string temp = b;
		int res = 0;
		char* asci = new char[size(temp) + 1];
		int i;
		for (i = 0; i < size(temp); i++)
		{
			asci[i] = temp[i];
			res += int(asci[i]);
		}
		return res;
	}
};

void funset() {
	int choice;
	bool a=0;
	set<Book> setbook;
	set<Book>::iterator it = setbook.begin();
	multiset<Book> multisetbook;
	unordered_set<Book, MyHash> unordered_setbook;
	unordered_multiset<Book, MyHash> unordered_multisetbook;
	ofstream sbook;
	string name;
	Book temp,temp1("Лесной маг","Хобб",678), temp2("Сквозь зеркала", "Дабо", 560), 
		temp3("Ведьмак", "Сапковский", 632);
	setbook.insert(temp1);
	setbook.insert(temp2);
	setbook.insert(temp3);
	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Удаление" << endl
			<< "3-Редактирование" << endl
			<< "4-Просмотр" << endl
			<< "5-Поиск" << endl
			<< "6-Запись в файл" << endl
			<< "7-multiset" << endl
			<< "8-unordered_set" << endl
			<< "9-unordered_multiset" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 9);
	
		switch (choice)
		{
		case 1:
			cin >> temp;
			setbook.insert(temp);
			break;
		case 2:
			cout << "Введите название книги" << endl;
			getline(cin, name);
			temp.SetTitle(name);
			it = setbook.find(temp);
			if (it != setbook.end())
			{
				setbook.erase(it);
				cout << "Книга удалена" << endl;
				break;
			}
			else
				cout << "Книга не найдена" << endl;
			break;
		case 3:
			cout << "Введите название книги" << endl;
			getline(cin, name);
			temp.SetTitle(name);
			it = setbook.find(temp);
			if (it != setbook.end())
			{
				setbook.erase(it);
				cout << "Новые данные" << endl;
				cin >> temp;
				setbook.insert(temp);
				break;
			}
			else
				cout << "Книга не найдена" << endl;
			break;
		case 4:
			for (const auto& element : setbook)
			{
				cout << element << endl;
			}
			break;
		case 5:
			it = setbook.begin();
			cout << "Введите название книги" << endl;
			getline(cin, name);
			temp.SetTitle(name);
			it = setbook.find(temp);
			if (it != setbook.end())
			{
				cout << "Книга найдена" << endl;
				cout << *it << endl;
			}
			else
				cout << "Книга не найдена" << endl;
			break;
		case 6:
			it = setbook.begin();
			sbook.open("book.txt");
			if (!sbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				while (it != setbook.end())
				{
					sbook << *it;
					sbook << endl;
					it++;
				}
			}
			sbook.close();
			cout << "Данные были записаны в файл" << endl;
			break;
		case 7:
			cout << "Ассортимент книжного магазина" << endl;
			multisetbook.insert(temp1);
			multisetbook.insert(temp2);
			multisetbook.insert(temp3);
			multisetbook.insert(temp1);
			multisetbook.insert(temp2);
			multisetbook.insert(temp3);
			for (const auto& element : multisetbook)
			{
				cout << element << endl;
			}
			break;
		case 8:
			cout << "Ассортимент книжного магазина" << endl;
			unordered_setbook.insert(temp1);
			unordered_setbook.insert(temp2);
			unordered_setbook.insert(temp3);
			unordered_setbook.insert(temp1);
			unordered_setbook.insert(temp2);
			unordered_setbook.insert(temp3);
			for (const auto& element : unordered_setbook)
			{
				cout << element << endl;
			}
			break;
		case 9:
			cout << "Ассортимент книжного магазина" << endl;
			unordered_multisetbook.insert(temp1);
			unordered_multisetbook.insert(temp2);
			unordered_multisetbook.insert(temp3);
			unordered_multisetbook.insert(temp1);
			unordered_multisetbook.insert(temp2);
			unordered_multisetbook.insert(temp3);
			for (const auto& element : unordered_multisetbook)
			{
				cout << element << endl;
			}
			break;
		case 0: return;
		}
		
	}

}

void funmap() {
	int choice;
	bool a = 0;
	map<string,Book> mapbook;
	map<string,Book>::iterator it = mapbook.begin();
	multimap<string,Book> multimapbook;
	unordered_map<string, Book, MyHash> unordered_mapbook;
	unordered_multimap<string, Book, MyHash> unordered_multimapbook;
	ofstream sbook;
	string name;
	Book temp, temp1("Лесной маг", "Хобб", 678), temp2("Сквозь зеркала", "Дабо", 560),
		temp3("Ведьмак", "Сапковский", 632);
	
	mapbook.insert(pair<string, Book>(temp1.GetTitle(),temp1));
	mapbook.insert(pair<string, Book>(temp2.GetTitle(), temp2));
	mapbook.insert(pair<string, Book>(temp3.GetTitle(), temp3));

	while (TRUE)
	{
		cout << "1-Добавление" << endl
			<< "2-Удаление" << endl
			<< "3-Редактирование" << endl
			<< "4-Просмотр" << endl
			<< "5-Поиск" << endl
			<< "6-Запись в файл" << endl
			<< "7-multiset" << endl
			<< "8-unordered_set" << endl
			<< "9-unordered_multiset" << endl
			<< "0-Назад" << endl;
		choice = CinIntErrorCheck(0, 9);

		switch (choice)
		{
		case 1:
			cin >> temp;
			mapbook.emplace(temp.GetTitle(), temp);
			break;
		case 2:
			cout << "Введите название книги" << endl;
			getline(cin, name);
			temp.SetTitle(name);
			it = mapbook.find(temp.GetTitle());
			if (it != mapbook.end())
			{
				mapbook.erase(it);
				cout << "Книга удалена" << endl;
				break;
			}
			else
				cout << "Книга не найдена" << endl;
			break;
		case 3:
			cout << "Введите данные для редактирования" << endl;
			cin >> temp;
			mapbook[temp.GetTitle()] = temp;
			break;
		case 4:
			for (const auto& element : mapbook)
			{
				cout << element.second << endl;
			}
			break;
		case 5:
			cout << "Введите название книги" << endl;
			getline(cin, name);
			temp.SetTitle(name);
			it = mapbook.find(temp.GetTitle());
			if (it != mapbook.end())
			{
				cout << "Книга найдена" << endl;
				cout << it->second << endl;
			}
			else
				cout << "Книга не найдена" << endl;
			break;
		case 6:
			it = mapbook.begin();
			sbook.open("book.txt");
			if (!sbook.is_open())
				cout << "Ошибка открытия файла" << endl;
			else
			{
				while (it != mapbook.end())
				{
					sbook << it->second;
					sbook << endl;
					it++;
				}
			}
			sbook.close();
			cout << "Данные были записаны в файл" << endl;
			break;
		case 7:
			cout << "Ассортимент книжного магазина" << endl;
			multimapbook.emplace(temp1.GetTitle(), temp1);
			multimapbook.emplace(temp2.GetTitle(), temp2);
			multimapbook.emplace(temp3.GetTitle(), temp3);
			multimapbook.emplace(temp1.GetTitle(), temp1);
			multimapbook.emplace(temp2.GetTitle(), temp2);
			multimapbook.emplace(temp3.GetTitle(), temp3);
			for (const auto& element : multimapbook)
			{
				cout << element.second << endl;
			}
			break;
		case 8:
			cout << "Ассортимент книжного магазина" << endl;
			unordered_mapbook.emplace(temp1.GetTitle(), temp1);
			unordered_mapbook.emplace(temp2.GetTitle(), temp2);
			unordered_mapbook.emplace(temp3.GetTitle(), temp3);
			unordered_mapbook.emplace(temp1.GetTitle(), temp1);
			unordered_mapbook.emplace(temp2.GetTitle(), temp2);
			unordered_mapbook.emplace(temp3.GetTitle(), temp3);
			for (const auto& element : unordered_mapbook)
			{
				cout << element.second << endl;
			}
			break;
		case 9:
			cout << "Ассортимент книжного магазина" << endl;
			unordered_multimapbook.emplace(temp1.GetTitle(), temp1);
			unordered_multimapbook.emplace(temp2.GetTitle(), temp2);
			unordered_multimapbook.emplace(temp3.GetTitle(), temp3);
			unordered_multimapbook.emplace(temp1.GetTitle(), temp1);
			unordered_multimapbook.emplace(temp2.GetTitle(), temp2);
			unordered_multimapbook.emplace(temp3.GetTitle(), temp3);
			for (const auto& element : unordered_multimapbook)
			{
				cout << element.second << endl;
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
		cout << "1-set" << endl
			<< "2-map" << endl
			<< "0-exit" << endl;
		choice = CinIntErrorCheck(0,2);
		system("cls");
		switch (choice)
		{
		case 1:
			funset();
			break;
		case 2:
			funmap();
			break;
		case 0: return 0;
		}
		system("cls");
	}
}