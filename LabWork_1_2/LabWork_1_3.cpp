// LabWork_1_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h" 
#include <conio.h>//Заголовочный файл объявляет несколько библиотечных функций для работы с «консольным вводом и выводом» программы
#include <stdlib.h>//заголовочный файл стандартной библиотеки языка Си, который содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов и другие.
#include <stdio.h>// заголовочный файл стандартной библиотеки языка Си, содержащий определения макросов, константы и объявления функций и типов, используемых для различных операций стандартного ввода и вывода. 
#include <string.h>//заголовочный файл стандартной библиотеки языка Си, содержащий функции для работы с нуль-терминированными строками и различными функциями работы с памятью.
#include <windows.h>// Windows-конкретный файл заголовков для языка C программирования, который содержит заявления для всех функций в Windows API, все общие макросы, которые используются программистами окон, и все типы данных, используемых различными функциями и подсистем.


#define _CRTDBG_MAP_ALLOC// Оператор  сопоставляет базовые версии функций кучи CRT соответствующим отладочным версиям. 
#include <crtdbg.h>//Включение заголовочного файла crtdbg.h сопоставляет функции malloc и free с их отладочными версиями, _malloc_dbg и free, которые отслеживают выделение и освобождение памяти. 


//Описание структур данных
struct date
{
	int day;
	int month;
	int year;

};

struct FIO
{
	char surname[15];
	char name[15];
	char patronymic[15];
};

struct Students
{
	FIO fio;
	date birthday;
	char group[4];
	float grade;
};


// Объявление функций

int fmenu(int n); //Вывод меню и возврат пункта выбора
void inputfilename(char **ffilename, int *fendsimbol);
void filereader(int rFileType, char **rfilename, Students **fstud, int *fsize, int *rferror); //Функция чтения из файла
int obrabotka(); // Обработка и вывод результата
int filewriter(); // Запись в файл
void sort(); // Сортировка 
void printResult(int *a, int size); //  вывод данных на экран


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//Вызов функции _CrtSetDbgFlag в начале приложения приведет к автоматическому вызову функции _CrtDumpMemoryLeaks в каждой точке выхода, при установки этих битовых полей


	SetConsoleCP(1251);			//Подключаем кодировку русского языка
	SetConsoleOutputCP(1251);

	//Описание переменных
	int menu = 0;//Переменная основного меню
	int submenu1 = 0;//Переменная подменю
	int submenu2 = 0;//Переменная подменю
	int WasEntered = 0;//Переменная отражающая факт ввода данных
	int Metod = 0;//Переменная отражающая метод открытия файла (чтение/запись)
	int FileType = 0;//Переменная отражающа тип файла
	int Correct = 0;//Переменная отражающая выбор корректировки
	int Del = 0;//Переменная отражающая выбор удаления записи
	Students *stud; //Массив структур данных
	int size = 0;//Размер массива данных
	int ferror = 0;//переменная сигнализирующая об ошибке открытия файла
	char *filename = NULL;//Указатель на имя файла
	int endsimbol = 0;//Переменна фикирующая символ окончания ввода


	// Тело основной программы

	do // Цикл повторения программы, при желании пользователя
	{
		menu = fmenu(1);
		switch (menu)
		{
		case 1://Ввод данных
			do
			{
				submenu1 = fmenu(2);
				switch (submenu1)
				{
				case 1:
					//Функция ввода данных с клавиатуры
					if (size != 0)
					{
						WasEntered = 1;
					}
					break;
				case 2:
					do
					{
						submenu2 = fmenu(4);
						switch (submenu2)
						{
						case 1:
							FileType = 0;
							break;
						case 2:
							FileType = 1;
							break;					
						case 0:
							break;
						default:
							printf("Не верный выбор пункта меню.\n");
							break;
						}

					} while (submenu2 != 0);

					//Функция ввода имени файла
					inputfilename(&filename, &submenu2);
					if (submenu2 != 27)
					{
						//Функция чтения данных из файла
						filereader(FileType, &filename, &stud, &size, &ferror);
						if (size != 0)
						{
							WasEntered = 1;
						}
					}
					break;
				case 0:
					break;
				default:
					printf("Не верный выбор пункта меню.\n");
					break;
				}
			} while (submenu1 != 0);
						
			break;
		case 2://Обработка данных (добавление, удаление, сортировка)
			if (WasEntered)
			{
				submenu1 = fmenu(3);

			}
			else
			{
				printf("Сначала нужно ввести данные!\n");
			}
			break;
		case 3://Сохранение файла
			if (WasEntered)
			{
				Metod = 1;
				submenu2 = fmenu(4);
				//Функция сохранения данных в файл

			}
			else
			{
				printf("Сначала нужно ввести данные!\n");
			}
			break;
		case 4://Формирование и сохранение файла отчета
			if (WasEntered)
			{
				FileType = 1;
				//Функция сохранения отчета в файл

			}
			else
			{
				printf("Сначала нужно ввести данные!\n");
			}
			break;
		case 0:
			break;
		default:
			printf("Не верный пункт выбора меню!\n");
			break;
		}



	} while (menu != 0);

	_CrtDumpMemoryLeaks();//выводит отчет об утечке памяти в область Отладка окна Вывод.
    return 0;
}

// Описание функций

// Функция меню
int fmenu(int n)
{
	if (n == 1)
	{
		printf("Программа предназначена для хранения и обработки данных стуентов.\n");
		printf("1. Ввод данных.\n");
		printf("2. Обработка данных. \n");
		printf("3. сохранение данных.\n");
		printf("4. Формирование отчета.\n");
		printf("___________________________\n");
		printf("0. Выход.\n\n");


	}
	else if (n == 2)
	{
		printf("Определите метод ввода данных:\n");
		printf("1. Ввод данных с клавиатуры\n");
		printf("2. Ввод данных из файла.\n");
		printf("_________________________________\n");
		printf("0. Возврат в предыдущее меню.\n");
	}
	else if (n == 3)
	{
		printf("Выберете действие:\n");
		printf("1. Сортировка записей и просмотр.\n");
		printf("2. Корректировка записи.\n");
		printf("3. Добавление новой записи.\n");
		printf("4. Удаление записи.\n");
		printf("_________________________________\n");
		printf("0. Возврат в предыдущее меню.\n");
	}
	else if (n == 4)
	{
		printf("Выберите тип файла:\n");
		printf("1. Бинарный.\n");
		printf("2. Текстовый.\n");
		printf("______________________________\n");
		printf("0. Возврат в предыдущее меню.\n");
	}
	else if (n == 5)
	{
		printf("Введите поля для сортировки:\n");
		printf("1. ФИО \n");
		printf("2. Номер зачетной книжки \n");
		printf("3. Год рождения \n");
		printf("4. Средний бал \n");
		printf("______________________________");
		printf("0. Возврат в предыдущее меню.\n");
	}
	else if (n == 6)
	{
		printf("Выберете порядок сортировки:\n");
		printf("1. По возрастанию.\n");
		printf("2. По убыванию.\n");
		printf("______________________________");
		printf("0. Возврат в предыдущее меню.\n");
	}
	int m;
	scanf("%d", &m);
	getchar();

	return m;
}

void inputfilename(char ** ffilename, int * fendsimbol)
{
}

void filereader(int rFileType, char **rfilename, Students ** fstud, int * fsize, int * rferror)
{
}


