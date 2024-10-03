/*Создать класс Matrix, в котором перегрузить операторы «* » для перемножения матриц, « + » для сложения матриц.Создать методы доступа к
полям класса.Память под матрицы выделять в конструкторе и освобождать в деструкторе.Реализовать конструкторы(по умолчанию, с параметрами,
копирования).Реализовать friend - функции для операторов ввода / вывода в поток для созданного класса.*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Matrix
{
private:
    int n, m, **a;
public:
    Matrix()
    {
        n = m = 2;
        a = new int* [n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[m];
        }
        //cout << "Был вызван конструктор по умолчанию" << endl;
    }

    Matrix(int n, int m)
    {
        this->n = n;
        this->m = m;
        a = new int* [n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[m];
        }
        //cout << "Был вызван конструктор c параметрами" << endl;
    }

   Matrix(const Matrix& other)
    {
        n = other.n;
        m = other.m;
        a = new int *[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int [m];
            for (int j = 0; j < m; j++)
            {
                a[i][j] = other.a[i][j];
            }
        }
        //cout << "Был вызван конструктор копирования" << endl;
    }

    ~Matrix()
    {
        for (int i = 0; i < n; i++)
        {
            delete []a[i];
        }
        delete[]a;
        //cout << "Был вызван деструктор" << endl;
    }

    friend void Input(Matrix& a);
    friend void Output(Matrix& a);
    void Infile(string name);
    void Outfile(string name);


    Matrix operator + (const Matrix& other)
    {
        int size_n = this->n, size_m = this->m;
        Matrix temp(size_n, size_m);
        for (int i = 0; i < size_n; i++)
        {
            for (int j = 0; j < size_m; j++)
            {
                temp.a[i][j] = this->a[i][j] + other.a[i][j];
            }
        }
        return temp;
    }

    Matrix operator * (const Matrix& other)
    {
        int size_n = this->n, size_m = other.m;
        Matrix temp(size_n, size_m);
        for (int i = 0; i < size_n; i++)
        {
            for (int j = 0; j < size_m; j++)
            {
                temp.a[i][j] = 0;
                for (int k = 0; k < this->m; k++)
                {
                    temp.a[i][j] += this->a[i][k] * other.a[k][j];
                }
            }
        }
        return temp;
    }

};

int Check()
{
    int a;
    while (!(cin >> a) || cin.get() != '\n') {
        cout << "Ошибка ввода. Введите целое число: " << endl;
        cin.clear();
        while (cin.get() != '\n');
    }
    return a;
}

void Input(Matrix &a)
{
    int k = 0;
    for (int i = 0; i < a.n; i++)
    {
        for (int j = 0; j < a.m; j++)
        {
            cout << "a[" << k << "]: ";
            a.a[i][j]=Check();
            k++;
        }
    }
}

void Output(Matrix& a)
{
    for (int i = 0; i < a.n; i++)
    {
        for (int j = 0; j < a.m; j++)
        {
            cout<<a.a[i][j] << "\t";
        }
        cout << endl;
    }
}

void Matrix::Infile(string name)
{
    ofstream f;
    f.open(name);
    if (!f.is_open())
    {
        cout << "Ошибка открытия файла" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                f << a[i][j];
                f << "\t";
            }
        }
        cout << "Данные были записаны в файл" << endl;
    }
    f.close();
}

void Matrix::Outfile(string name)
{
    ifstream f;
    f.open(name);
    if (!f.is_open())
    {
        cout << "Ошибка открытия файла" << endl;
    }
    else
    {
        cout << "Данные из файла:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                f >> a[i][j];
                cout << a[i][j] << "\t";
            }
            cout << endl;
        }
    }
    f.close();
}


int main()
{
    setlocale(LC_ALL, "Ru");
    int n1, n2, m1, m2;
    cout << "Введите количество строк матрицы 1: ";
    n1 = Check();
    while (n1 <= 0 || n1 > 99) 
    {
        cout << "Ошибка ввода. Введите положительное значение <100" << endl;
        n1 = Check();
    }
    cout << "Введите количество столбцов матрицы 1: ";
    m1 = Check();
    while (m1 <= 0 || m1 > 99)
    {
        cout << "Ошибка ввода. Введите положительное значение <100" << endl;
        m1 = Check();
    }
    cout << "Введите количество строк матрицы 2: ";
    n2 = Check();
    while (n2 <= 0 || n2 > 99)
    {
        cout << "Ошибка ввода. Введите положительное значение <100" << endl;
        n2 = Check();
    }
    cout << "Введите количество столбцов матрицы 2: ";
    m2 = Check();
    while (m2 <= 0 || m2 > 99)
    {
        cout << "Ошибка ввода. Введите положительное значение <100" << endl;
        m2 = Check();
    }
    Matrix k(n1, m1), l(n2, m2);
    cout << "Введите элементы первой матрицы: " << endl;
    Input(k);
    cout << "Введите элементы второй матрицы: " << endl;
    Input(l);
    cout << "Матрица 1: " << endl;
    Output(k);
    cout << "Матрица 2: " << endl;
    Output(l);
    
    if (m1 == n2) //Количество столбцов м1 = количеству строк м2
    {
        Matrix pr=k*l;
        cout << "Произведение матриц 1 и 2: " << endl;
        Output(pr);
        pr.Infile("pr.txt");
        cout << "-----------------------------------------" << endl;
        pr.Outfile("pr.txt");
        cout << "-----------------------------------------" << endl;
    }
    else
        cout << "Умножение невозможно" << endl;


    if (n1 == n2 && m1 == m2) //одинаковые по размеру матрицы
    {
        Matrix sum = k + l;
        cout << "Сложение матриц 1 и 2: " << endl;
        Output(sum);
        sum.Infile("sum.txt");
        cout << "-----------------------------------------" << endl;
        sum.Outfile("sum.txt");
        cout << "-----------------------------------------" << endl;
    }
    else
        cout << "Сложение невозможно" << endl;
}

