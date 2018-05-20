// LabWork_1_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h" 
#include <conio.h>//Заголовочный файл объявляет несколько библиотечных функций для работы с «консольным вводом и выводом» программы
#include <stdlib.h>//заголовочный файл стандартной библиотеки языка Си, который содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов и другие.
#include <stdio.h>// заголовочный файл стандартной библиотеки языка Си, содержащий определения макросов, константы и объявления функций и типов, используемых для различных операций стандартного ввода и вывода. 
#include <string.h>//заголовочный файл стандартной библиотеки языка Си, содержащий функции для работы с нуль-терминированными строками и различными функциями работы с памятью.
#include <windows.h>// Windows-конкретный файл заголовков для языка C программирования, который содержит заявления для всех функций в Windows API, все общие макросы, которые используются программистами окон, и все типы данных, используемых различными функциями и подсистем.
#include <crtdbg.h>

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
void sort(Students **fstud, int *fsize); // Сортировка 
void printResult(Students *a, int size); //  вывод данных на экран
void setdatacon(Students **fstud, int *fsize, char *fendsimbol);
void inputnumber(int *fnumptr, char *fch);
void inputnumber(float *fgradeptr, char *fch);
void deletedata(Students **fstud, int *fsize);





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
					/*
					if (stud != NULL)
					{
						delete[] stud;
					}
					*/
					//size = 0;
					//stud = new Students [size];

					setdatacon(&stud, &size, &endsimbol);
					/*if (endsimbol == 27)
					{
						if (stud != NULL)
						{
							delete[] stud;
						}
						size = 0;
					}*/

					//printResult(stud, size);

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
							printf("Введите имя файла: ");
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
				if ( endsimbol == 27)
				{
					break;
				}
			} while (submenu1 != 0);
						
			break;
		
		case 2://Просмотр данных
			if (WasEntered)
			{
				printResult(stud, size);
			}
			else
			{
				printf("Сначала нужно ввести данные!\n");
			}
			break;
		
		case 3://Обработка данных (добавление, удаление, сортировка)
			if (WasEntered)
			{
				do
				{
					submenu2 = fmenu(3);
					switch (submenu2)
					{
					case 1:
						sort(&stud, &size);
						break;
					case 2:
						break;
					case 3:
						deletedata(&stud, &size);
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

		case 4://Сохранение файла
			if (WasEntered)
			{
				Metod = 1;
				submenu2 = fmenu(4);
				//Функция сохранения данных в файл

			}
			else
			{
				printf("Сначала нужно ввести данные!\n\n");
			}
			break;
		case 5://Формирование и сохранение файла отчета
			if (WasEntered)
			{
				FileType = 1;
				//Функция сохранения отчета в файл

			}
			else
			{
				printf("Сначала нужно ввести данные!\n\n");
			}
			break;
		case 0:
			break;
		default:
			printf("Не верный пункт выбора меню!\n");
			break;
		}


	} while (menu != 0);

	if (stud != NULL)
	{
		delete[] stud;
	}
    return 0;
}

// Описание функций

// Функция меню
int fmenu(int n)
{
	if (n == 1)
	{
		printf("\nПрограмма предназначена для хранения и обработки данных студентов.\n");
		printf("1. Ввод данных и добавление записей.\n");
		printf("2. Просмотр данных.\n");
		printf("3. Обработка и корректировка данных. \n");
		printf("4. Сохранение данных.\n");
		printf("5. Формирование файла отчета.\n");
		printf("___________________________\n");
		printf("0. Выход.\n\n");


	}
	else if (n == 2)
	{
		printf("\nВвод данных и добавление записей. Определите метод ввода данных:\n");
		printf("1. Ввод данных с клавиатуры\n");
		printf("2. Ввод данных из файла.\n");
		printf("_________________________________\n");
		printf("0. Возврат в предыдущее меню.\n\n");
	}
	else if (n == 3)
	{
		printf("\nВыберете действие:\n");
		printf("1. Сортировка записей.\n");
		printf("2. Корректировка записи.\n");
		//printf("3. Добавление новой записи.\n");
		printf("3. Удаление записи.\n");
		printf("_________________________________\n");
		printf("0. Возврат в предыдущее меню.\n\n");
	}
	else if (n == 4)
	{
		printf("\nВыберите тип файла:\n");
		printf("1. Бинарный.\n");
		printf("2. Текстовый.\n");
		printf("______________________________\n");
		printf("0. Возврат в предыдущее меню.\n\n");
	}
	else if (n == 5)
	{
		printf("\nВведите поля для сортировки:\n");
		printf("1. ФИО \n");
		printf("2. Номер зачетной книжки \n");
		printf("3. Год рождения \n");
		printf("4. Средний балл \n");
		printf("______________________________");
		printf("0. Возврат в предыдущее меню.\n\n");
	}
	else if (n == 6)
	{
		printf("\nВыберете порядок сортировки:\n");
		printf("1. По возрастанию.\n");
		printf("2. По убыванию.\n");
		printf("______________________________");
		printf("0. Возврат в предыдущее меню.\n\n");
	}
	int m;
	
	scanf("%d", &m);
	//fflush(stdin);
	scanf("%*[^\n]");
	getchar();

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


void sort(Students **fstud, int *fsize)
{
	int choise = 0;
	int index = 0;
	Students min;

	
	do
	{
		printf("\nВыберете параметр для сортировки.\n");
		printf("1. По фамилии.\n");
		printf("2. По имени. \n");
		printf("3. По отчеству. \n");
		printf("4. По дате рождения. \n");
		printf("5. По группе. \n");
		printf("6. По среднему баллу. \n");

		printf("0. Отмена ввода данных. \n");
		scanf("%d", &choise);
		scanf("%*[^\n]");
		getchar();
		if ((choise < 0) or (choise > 6)) 
		{
			printf("Не верный выбор пункта меню!\n");
		}
	} while ((choise < 0) or (choise > 6));

	switch (choise)
	{
	case 1:

		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				//(*fC)++;
				for (int k = 0; k < 20; k++)
				{
					if ((*fstud)[index].fio.surname[k] >(*fstud)[j].fio.surname[k]) //Править здесь!
					{
						index = j;
					}
				}
				
			}
			if (index != i)
			{
				min  = (* fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по фамилии выполнена!\n");
		break;
	case 2:
		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				//(*fC)++;
				for (int k = 0; k < 20; k++)
				{
					if ((*fstud)[index].fio.name[k] >(*fstud)[j].fio.name[k]) //Править здесь!
					{
						index = j;
					}
				}

			}
			if (index != i)
			{
				min = (*fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по имени выполнена!\n");
		break;
	case 3:
		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				//(*fC)++;
				for (int k = 0; k < 20; k++)
				{
					if ((*fstud)[index].fio.patronymic[k] >(*fstud)[j].fio.patronymic[k]) //Править здесь!
					{
						index = j;
					}
				}

			}
			if (index != i)
			{
				min = (*fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по отчеству выполнена!\n");
		break;
	case 4:

		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				if ((*fstud)[index].birthday.year > (*fstud)[j].birthday.year) //Править здесь!
				{
					index = j;
				}
				//Если год одинаков - сравниваем месяц
				if ((*fstud)[index].birthday.year == (*fstud)[j].birthday.year) //Править здесь!
				{
					if ((*fstud)[index].birthday.month > (*fstud)[j].birthday.month) //Править здесь!
					{
						index = j;
					}
					//Если месяц одинаков - сравниваем день
					if ((*fstud)[index].birthday.month == (*fstud)[j].birthday.month) //Править здесь!
					{
						if ((*fstud)[index].birthday.day > (*fstud)[j].birthday.day) //Править здесь!
						{
							index = j;
						}
					}
				}

			}
			if (index != i)
			{
				min = (*fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по дате рождения выполнена!\n");

		break;
	case 5:
		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				//(*fC)++;
				for (int k = 0; k < 11; k++)
				{
					if ((*fstud)[index].group[k] >(*fstud)[j].group[k]) 
					{
						index = j;
					}
				}

			}
			if (index != i)
			{
				min = (*fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по группе выполнена!\n");
		break;
	case 6:
		for (int i = 0; i < *fsize; i++)
		{
			index = i;
			for (int j = i + 1; j < *fsize; j++)
			{
				
					if ((*fstud)[index].grade >(*fstud)[j].grade)
					{
						index = j;
					}
				

			}
			if (index != i)
			{
				min = (*fstud)[index]; //(*fM)++;
				(*fstud)[index] = (*fstud)[i]; //(*fM)++;
				(*fstud)[i] = min; //(*fM)++;
			}
		}
		printf("Сортировка по среднему баллу выполнена!\n");
		break;
	case 0:
		break;
	}
	



}

void printResult(Students * a, int fsize)
{
	printf("______________________________________________________________________________________________________________\n");
	printf("| №   |    Фамилия           |        Имя           |      Отчество        |   Дата р.  |    Группа   | Балл |\n");
	printf("______________________________________________________________________________________________________________\n");
	

	for (int i = 0; i < fsize; i++)
	{
		
		printf("| %03d ", i + 1);
		printf("| %-20s ", a[i].fio.surname);
		printf("| %-20s ", a[i].fio.name);
		printf("| %-20s ", a[i].fio.patronymic);
		printf("| %02d/%02d/%04d ", a[i].birthday.day, a[i].birthday.month, a[i].birthday.year);
		printf("| %-11s ", a[i].group);
		printf("| %.2f |\n", a[i].grade);
	}
	printf("______________________________________________________________________________________________________________\n\n");
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
	//Временные  переменные для ввода чисел
	int tmpnumber = 0;
	float gradenumber = 0; //Переменная 

	//if (*fstud != NULL)
	//{
		t = *fsize + 1;
		startsize = *fsize;
	//	printf("t=%d", t);
	//	getchar();
	//}
	//else
	//{
	//	t = 1;
	//	*fstud = new Students[1];
	//}
	
	

	printf("\nВведите данные студентов. Для подтверждения ввода нажмите ""Enter"", либо нажмите ""ESC"" для отмены ввода данных.\n");
	do
	{
		do
		{
			//Инициирование и заполнение временного массива
			tmpstud = new Students[t];
			for (int j = 0; j < t - 1; j++)
			{
				tmpstud[j] = (*fstud)[j];
			}

			printf("Введите фамилию %d-го студента:		", t);
			inputstring(&fstring, &s, &fensim);
			//printf("%s", fstring);
			if (fensim == 27)
			{
				if (fstring != NULL)
				{
					delete[] fstring;
					fstring = NULL;
				}
				if (*fstud != NULL)
				{

				}
				s = 0;
				//t--;
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
					tmpstud[t - 1].fio.surname[i] = fstring[i];
					//printf("%c", (*fstud)[*fsize].fio.surname[i]);
				}
				tmpstud[t - 1].fio.surname[s] = '\0';
				delete[] fstring;
				fstring = NULL;
				s = 0;
			}

			printf("Введите имя  %d-го студента:		", t);
			inputstring(&fstring, &s, &fensim);
			if (fensim == 27)
			{
				if (fstring != NULL)
				{
					delete[] fstring;
					fstring = NULL;
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
					tmpstud[t - 1].fio.name[i] = fstring[i];
				}
				tmpstud[t - 1].fio.name[s] = '\0';
				delete[] fstring;
				fstring = NULL;
				s = 0;
			}

			printf("Введите отчество  %d-го студента:	", t);
			inputstring(&fstring, &s, &fensim);
			if (fensim == 27)
			{
				if (fstring != NULL)
				{
					delete[] fstring;
					fstring = NULL;
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
					tmpstud[t - 1].fio.patronymic[i] = fstring[i];
				}
				tmpstud[t - 1].fio.patronymic[s] = '\0';
				delete[] fstring;
				fstring = NULL;
				s = 0;
			}

			
			do
			{
				printf("Введите число рождения  %d-го студента:	", t);
				inputnumber(&tmpnumber, &fensim);
				if (fensim == 27)
				{
					break;
				}
				else
				{
					if ((tmpnumber > 0) and (tmpnumber < 32))
					{
						tmpstud[t - 1].birthday.day = tmpnumber;
					}
					else
					{
						printf("Не верный формат даты! Повторите ввод!\n");
					}
				}
			} while ((tmpnumber < 1) or (tmpnumber > 31));
			if (fensim == 27)
			{
				break;
			}
			 
			do
			{
				printf("Введите месяц рождения  %d-го студента:	", t);
				inputnumber(&tmpnumber, &fensim);
				if (fensim == 27)
				{
					break;
				}
				else
				{
					if ((tmpnumber > 0) and (tmpnumber < 13))
					{
						tmpstud[t - 1].birthday.month = tmpnumber;
					}
					else
					{
						printf("Не верный формат даты! Повторите ввод!\n");
					}
				}
			} while ((tmpnumber < 1) or (tmpnumber > 13));
			if (fensim == 27)
			{
				break;
			}

			do
			{
				printf("Введите год рождения  %d-го студента:	", t);
				inputnumber(&tmpnumber, &fensim);
				if (fensim == 27)
				{
					break;
				}
				else
				{
					if ((tmpnumber > 1900) and (tmpnumber < 2010))
					{
						tmpstud[t - 1].birthday.year = tmpnumber;
					}
					else
					{
						printf("Не верный формат даты! Повторите ввод!\n");
					}
				}
			} while ((tmpnumber < 1900) or (tmpnumber > 2010));
			
			if (fensim == 27)
			{
				break;
			}

			printf("Введите группу  %d-го студента:		", t);
			inputstring(&fstring, &s, &fensim);
			if (fensim == 27)
			{
				if (fstring != NULL)
				{
					delete[] fstring;
					fstring = NULL;
				}
				s = 0;
				break;
			}
			else
			{
				if (strlen(fstring) > 11)
				{
					s = 11;
				}
				else
				{
					s = strlen(fstring);
				}
				for (int i = 0; i < s; i++)
				{
					tmpstud[t - 1].group[i] = fstring[i];
				}
				tmpstud[t - 1].group[s] = '\0';
				delete[] fstring;
				fstring = NULL;
				s = 0;
			}

			do
			{
				printf("Введите средний балл %d-го студента:	", t);
				inputnumber(&gradenumber, &fensim);
				if (fensim == 27)
				{
					break;
				}
				else
				{
					if ((gradenumber > 0) and (gradenumber <= 5))
					{
						tmpstud[t - 1].grade = gradenumber;
					}
					else
					{
						printf("Не верный формат даты! Повторите ввод!\n");
					}
				}
			} while ((gradenumber < 0) or (gradenumber > 5));

			if (fensim == 27)
			{
				break;
			}

			/*
			//Удаляем основной массив и вместо него оставляем временный
			delete[] * fstud;
			*fstud = tmpstud;
			*fsize = t;
			tmpstud = NULL;
			//t = 0;
			*/
		} while (false);

		if (fensim == 27)
		{
			t--;
			delete[] tmpstud;
			if (t != 0)
			{
				tmpstud = *fstud;
			}
			else
			{
				tmpstud = NULL;
			}
		}
		else
		{
			//Удаляем основной массив и вместо него оставляем временный
			delete[] * fstud;
			*fstud = tmpstud;
			*fsize = t;
			tmpstud = NULL;
			//t = 0;
		}

		do
		{
			printf("\nВыберите дальнейшие действия: \n");
			printf("1. Ввести данные следующего студента.\n");
			printf("2. Закончить ввод данных. \n");
			printf("0. Отмена ввода данных. \n");
			scanf("%d", &retry);
			scanf("%*[^\n]");
			getchar();
			if ((retry != 1) && (retry != 2) && (retry != 0))
			{
				printf("Не верный выбор пункта меню!\n");
			}
		} while ((retry != 1) && (retry != 2) && (retry != 0));
		
		
		
		if (retry == 1)
		{
			t++;
			continue;

		}
		if (retry == 0)
		{
			if (startsize !=0)
			{
				*fsize = startsize;
				tmpstud = new Students[startsize];
				for (int i = 0; i < startsize; i++)
				{
					tmpstud[i] = (*fstud)[i];
				}
				delete[] * fstud;
				*fstud = tmpstud;
				
			}
			else
			{
				delete[] * fstud;
				*fsize = 0;
				//delete[] tmpstud;

			}
			*fendsimbol = 27;
			break;
		}

		*fendsimbol = 27;

	} while (retry != 2);


	/*
	if (fensim == 27) 
	{
		if (tmpstud != NULL)
		{
			delete[] tmpstud;
			tmpstud = NULL;
			t = 0;
		}
		if (*fstud != NULL)
		{
			if (startsize != 0)
			{
				tmpstud = new Students[startsize];
				for (int i = 0; i < startsize; i++)
				{
					tmpstud[i] = (*fstud)[i];
				}
				delete[] * fstud;
				*fstud = tmpstud;
				*fsize = startsize;
				tmpstud = NULL;
				t = 0;

			}
			else
			{
				delete[] * fstud;
				*fsize = 0;
				*fstud = NULL;
			}
		}
				

	}
	*/
	

	
}

void inputnumber(int *fnumptr,  char *fch)
{
	char ch = 0;
	int m = 0;
	char *fcharptr = NULL;
	//Инициализация массива данных	
	fcharptr = new  char[1];
	fcharptr[0] = '\0';
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
					tmptxtptr[i] = fcharptr[i];
				}
				//Добавляем в массив знак окончания строки
				tmptxtptr[m - 2] = '\0';
				//Удаляем основной массив и вместо него оставляем временный
				delete[] fcharptr;
				fcharptr = tmptxtptr;
				m = m - 1;
				continue;
			}
		}
		//При наборе символа
		if ((ch > 47) and (ch < 58))
		{
			printf("%c", ch);
			//Создаем вспомогательный временный массив
			char *tmptxtptr = new char[m + 1];
			//Копирование элементов основного массива во временный
			for (int i = 0; i < m - 1; i++)
			{
				tmptxtptr[i] = fcharptr[i];
			}
			//Добавляем вновь введенный символ
			tmptxtptr[m - 1] = ch;
			tmptxtptr[m] = '\0';
			//Удаляем основной массив и вместо него оставляем временный
			delete[] fcharptr;
			fcharptr = tmptxtptr;
			m = m++;
			continue;
		}

		printf("\a");

	}
	//*fsize = m;
	*fch = ch;
	*fnumptr = atoi(fcharptr);
	if (fcharptr != NULL)
	{
		delete[] fcharptr;
		fcharptr = NULL;
	}
}

void inputnumber(float *fgradeptr, char *fch)
{
	char ch = 0;
	int m = 0;
	char *fcharptr = NULL;
	//Инициализация массива данных	
	fcharptr = new  char[1];
	fcharptr[0] = '\0';
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
					tmptxtptr[i] = fcharptr[i];
				}
				//Добавляем в массив знак окончания строки
				tmptxtptr[m - 2] = '\0';
				//Удаляем основной массив и вместо него оставляем временный
				delete[] fcharptr;
				fcharptr = tmptxtptr;
				m = m - 1;
				continue;
			}
		}
		//При наборе символа
		if (((ch > 47) and (ch < 58)) or (ch == 46))
		{
			printf("%c", ch);
			//Создаем вспомогательный временный массив
			char *tmptxtptr = new char[m + 1];
			//Копирование элементов основного массива во временный
			for (int i = 0; i < m - 1; i++)
			{
				tmptxtptr[i] = fcharptr[i];
			}
			//Добавляем вновь введенный символ
			tmptxtptr[m - 1] = ch;
			tmptxtptr[m] = '\0';
			//Удаляем основной массив и вместо него оставляем временный
			delete[] fcharptr;
			fcharptr = tmptxtptr;
			m = m++;
			continue;
		}

		printf("\a");

	}
	//*fsize = m;
	*fch = ch;
	*fgradeptr = atof(fcharptr);
	if (fcharptr != NULL)
	{
		delete[] fcharptr;
		fcharptr = NULL;
	}
}

void deletedata(Students ** fstud, int * fsize)
{
	//Переменная символа окончания ввода
	char fensim;
	//Переменные для временного массива информации о студентах
	//int t = 0;
	Students *tmpstud = NULL;
	//Временные  переменные для ввода чисел
	int tmpnumber = 0;
	
	do
	{
		printf("\n * fsize = %d\n", * fsize);
		printf("\nВведите номер записи для удаления и нажмите Enter или нажмите Esc для отмены:	");
		inputnumber(&tmpnumber, &fensim);
		if (fensim == 27)
		{
			break;
		}
		else
		{
			if ((tmpnumber > 0) and (tmpnumber < (*fsize) + 1))
			{
				tmpstud = new Students[*fsize];
				for (int i = 0; i < tmpnumber-1; i++)
				{
					tmpstud[i] = (*fstud)[i];
				}
				
				for (int i = tmpnumber-1; i < * fsize; i++)
				{
					tmpstud[i] = (*fstud)[i+1];
				}

				delete[] * fstud;
				*fstud = tmpstud;
				(*fsize)--;
				printf("\n * fsize = %d\n", *fsize);
				break;
			}
			else
			{
				printf("Указан не верный номер записи! Повторите ввод!\n");
			}
		}
	} while ((tmpnumber < 1) or (tmpnumber > (* fsize)));
}
