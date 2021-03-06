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
	char surname[21];
	char name[21];
	char patronymic[21];
};

struct Students
{
	FIO fio;
	date birthday;
	char group[11];
	float grade;
};


// Объявление функций

int fmenu(int n); //Вывод меню и возврат пункта выбора
void inputstring(char **ffilename, int *ffilenamesize, char *fendsimbol);
void filereader(int rFileType, char **rfilename, Students **fstud, int *fsize, int *rferror); //Функция чтения из файла
int obrabotka(); // Обработка и вывод результата
int filewriter(); // Запись в файл
void sort(); // Сортировка 
void printResult(int *a, int size); //  вывод данных на экран
void setdatacon(Students **fstud, int *fsize, char *fendsimbol);




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
	Students *stud = NULL; //Массив структур данных
	int size = 0;//Размер массива данных
	int filenamesize = 0;//длина имени файла
	int ferror = 0;//переменная сигнализирующая об ошибке открытия файла
	char *filename = NULL;//Указатель на имя файла
	char endsimbol = 0;//Переменна фикирующая символ окончания ввода


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
					if (stud != NULL)
					{
						delete[] stud;
					}
					size = 0;
					//stud = new Students [size];

					setdatacon(&stud, &size, &endsimbol);
					if (endsimbol == 27)
					{
						if (stud != NULL)
						{
							delete[] stud;
						}
						size = 0;
					}
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
						if (submenu2 == 1 or submenu2 == 2)
						{
							//Функция ввода имени файла
							inputstring(&filename, &filenamesize, &endsimbol);
							if (endsimbol != 27)
							{
								//Функция чтения данных из файла
								filereader(FileType, &filename, &stud, &size, &ferror);
								//if ((!ferror) and (size != 0))
								if (!ferror)
								{
									printf("\n Ввод данных выполнен! \n\n"); 
									WasEntered = 1;
									submenu2 = 0;
									submenu1 = 0;
								}
							}
							
						}

					} while (submenu2 != 0);
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
				do
				{
					submenu2 = fmenu(3);
					switch (submenu2)
					{
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 0:
						break;
					default:
						printf("Не верный выбор пункта меню.\n");
						break;
					}
				} while (submenu2 != 0);
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
	//scanf("%*[^\n]");
	
	return m;
}

void inputstring (char **ftxtptr, int *fsize, char *fch)
{
	char ch = 0;
	int m = 0;
	*fsize = m;
	//Инициализация массива данных	
	*ftxtptr = new  char[1];
	(*ftxtptr)[0] = '\0';
	m = 1;
	//Ввод текста и запись символов в массив
	while (true)
	{
		ch = getch();
		getch();
		//При нажатии Esc
		if (ch == 27)
		{
			printf("\n\n");
			break;
		}
		//При нажатии Enter
		if (ch == 13)
		{
			if (m > 1)
			{
				printf("\n");
				break;
			}
		}
		//При нажатии BackSpace
		if (ch == 8)
		{
			if (m > 1)
			{
				printf("%c", ch);
				printf(" %c", ch);
				//Создаем вспомогательный временный массив
				char *tmptxtptr = new char[m - 1];
				//Копирование элементов основного массива во временный
				for (int i = 0; i < m - 2; i++)
				{
					tmptxtptr[i] = (*ftxtptr)[i];
				}
				//Добавляем в массив знак окончания строки
				tmptxtptr[m - 2] = '\0';
				//Удаляем основной массив и вместо него оставляем временный
				delete[] * ftxtptr;
				*ftxtptr = tmptxtptr;
				m = m - 1;
				continue;
			}
		}
		//При наборе символа
		if ((ch != 13) and (ch != 8) and (ch != 27))
		{
			printf("%c", ch);
			//Создаем вспомогательный временный массив
			char *tmptxtptr = new char[m + 1];
			//Копирование элементов основного массива во временный
			for (int i = 0; i < m - 1; i++)
			{
				tmptxtptr[i] = (*ftxtptr)[i];
			}
			//Добавляем вновь введенный символ
			tmptxtptr[m - 1] = ch;
			tmptxtptr[m] = '\0';
			//Удаляем основной массив и вместо него оставляем временный
			delete[] * ftxtptr;
			*ftxtptr = tmptxtptr;
			m = m++;
			continue;
		}

		printf("\a");

	}
	*fsize = m;
	*fch = ch;

}

void filereader(int rFileType, char **rfilename, Students ** fstud, int * fsize, int * rferror)
{
	printf("Открытие файла и формирование массива данных.");
}


void setdatacon(Students ** fstud, int * fsize, char * fendsimbol)
{
	//Переменные для временного массива строки и символа возврата
	int s = 0;
	char *fstring = NULL;
	char fensim;
	//Переменные для временного массива информации о студентах
	int t = 0;
	Students *tmpstud = NULL;
	int startsize = 0;
	//Переменная повтора
	int retry;

	if (*fstud != NULL)
	{
		t = *fsize;
		startsize = *fsize;
	}
	else
	{
		t = 1;
		*fstud = new Students[1];
	}
	
	

	printf("Введите данные студентов. Для подтверждения ввода нажмите ""Enter"", либо нажмите ""ESC"" для отмены ввода данных.\n");
	do
	{
		//Инициирование и заполнение временного массива
		tmpstud = new Students[t];
		for (int j = 0; j < t-1; j++)
		{
			tmpstud[j] = *fstud[j];
		}

		printf("Введите фамилию %d-го студента:	", *fsize);
		inputstring(&fstring, &s, &fensim);
		//printf("%s", fstring);
		if (fensim == 27)
		{
			if (fstring != NULL)
			{
				delete[] fstring;
			}
			s = 0;
			break;
		}
		else
		{
			if (strlen(fstring) > 20)
			{
				s = 20;
			}
			else
			{
				s = strlen(fstring);
			}
			for (int  i = 0; i < s; i++)
			{
				tmpstud[t-1].fio.surname[i] = fstring[i];
				//printf("%c", (*fstud)[*fsize].fio.surname[i]);
			}
			tmpstud[t-1].fio.surname[s] = '\0';
			delete[] fstring;
			s = 0;
		}

		printf("Введите имя  %d-го студента:	", *fsize);
		inputstring(&fstring, &s, &fensim);
		if (fensim == 27)
		{
			if (fstring != NULL)
			{
				delete[] fstring;
			}
			s = 0;
			break;
		}
		else
		{

			if (strlen(fstring) > 20)
			{
				s = 20;
			}
			else
			{
				s = strlen(fstring);
			}
			for (int i = 0; i < s; i++)
			{
				tmpstud[t-1].fio.name[i] = fstring[i];
			}
			tmpstud[t-1].fio.name[s] = '\0';
			delete[] fstring;
			s = 0;
		}

		printf("Введите отчество  %d-го студента:	", *fsize);
		inputstring(&fstring, &s, &fensim);
		if (fensim == 27)
		{
			if (fstring != NULL)
			{
				delete[] fstring;
			}
			s = 0;
			break;
		}
		else
		{
			if (strlen(fstring) > 20)
			{
				s = 20;
			}
			else
			{
				s = strlen(fstring);
			}
			for (int i = 0; i < s; i++)
			{
				tmpstud[t-1].fio.patronymic[i] = fstring[i];
			}
			tmpstud[t-1].fio.patronymic[s] = '\0';
			delete[] fstring;
			s = 0;
		}

		//Удаляем основной массив и вместо него оставляем временный
		delete[] * fstud;
		*fstud = tmpstud;
		*fsize = t;

		do
		{
			printf("Выберите дальнейшие действия: \n");
			printf("1. Ввести данные следующего студента.\n");
			printf("2. Закончить ввод данных. \n");
			printf("0. Отмена ввода данных. \n");
			scanf("%d", &retry);
			getchar();
			if ((retry != 1) && (retry != 2) && (retry != 0))
			{
				printf("Не верный пункт выбора меню!\n");
			}
		} while ((retry != 0) && (retry != 1) && (retry != 0));
		if (retry == 1)
		{
			t++;
			//break;

		}
		if (retry == 0)
		{
			if (startsize !=0)
			{
				tmpstud = new Students[startsize];
				for (int i = 0; i < startsize; i++)
				{
					tmpstud[i] = *fstud[i];
				}
				delete[] * fstud;
				*fstud = tmpstud;
				
			}
			else
			{
				delete[] * fstud;
				//delete[] tmpstud;

			}

			break;
		}

	} while (retry != 2);


	if (fensim == 27) 
	{
		if (*fstud != 0)
		{
			delete[] * fstud;
		}
				

	}
	

	
}


