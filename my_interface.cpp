
#include "stdafx.h"
#include "my_student.h"
#include "my_stack.h"
#include "my_interface.h"
#include "my_messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning (disable : 4996)

void menu()
{
		printf("[0] - Push student\n[1] - Pop student\n[2] - Print all elements of stack\n[3] - Clear stack\n[4] - Find student\n[5] - Save stack\n[6] - Read stack\n[7] - Finish program\n");
}

void push()
{
	char lastname[128];
	int year, course;
	printf("Enter Lastname:\n");
	scanf_s("%s", lastname, sizeof(lastname));
	printf("Enter Year:\n");
	
	while (scanf_s("%d", &year) <= 0)
	{
		while ((getchar()) != '\n');
		my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
		printf("Enter Year:\n");
	}
	while ((getchar()) != '\n'); 
	
	printf("Enter Course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n");
	
	do
	{
		while (scanf_s("%d", &course) <= 0)
		{
			while ((getchar()) != '\n');
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			printf("Enter Course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n");
		}
		
		while ((getchar()) != '\n');
		
		if (course < 0 || course > 2)
		{
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			printf("Enter Course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n");
		}

	} while (course < 0 || course > 2);
	
	void *pdat = MY_STUDENT_Push(lastname, year, course);
	if (!MY_STACK_Push(pdat))
	{
		my_mess_fun(MY_MESS_PUSH);
	}
}

void pop()
{
	MY_STACK tmp = MY_STACK_Pop();
	MY_STUDENT_Print(tmp.pData);
	MY_STUDENT_Free(tmp.pData);
}

void print()
{
	int i = 0;
	void *tmp = MY_STACK_Get_one(i);
	while (tmp)
	{
		i++;
		MY_STUDENT_Print(tmp);
		tmp = MY_STACK_Get_one(i);
		
	}
	if (i == 0)
		printf("Stack is empty\n");
}


void find()
{
	printf("\nFind: [0] - Lastname, [1] - Year, [2] - Course\n");
	int choice, i = 0;
	do
	{
		scanf_s("%d", &choice);
		while (getchar() != '\n');
		if (choice < 0 || choice > 2)
		{
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			printf("Find: [0] - Lastname, [1] - Year, [2] - Course\n");
		}
	} while (choice < 0 || choice > 2);
	MY_STUDENT searchDat;
	memset(&searchDat, 0, sizeof(MY_STUDENT));
	if (choice == 0)
	{
		char str[128];
		printf("Enter lastname\n");
		scanf_s("%s", str, sizeof(str));
		searchDat.nazwisko = (char *)malloc((strlen(str) + 1) * sizeof(char));
		if (!searchDat.nazwisko)
		{
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(NULL, searchDat.nazwisko, NULL, NULL);
		}
		strcpy_s(searchDat.nazwisko, (strlen(str) + 1) * sizeof(char), str);
		void *pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchLastName, 1);
		if (pDat)
		{
			printf("Found: \n");
			MY_STUDENT_Print(pDat);
			i++;

		}

		while (pDat)
		{
			pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchLastName, 0);
			if (pDat)
			{
				printf("Found: \n");
				MY_STUDENT_Print(pDat);
				i++;
			}
		}
		if (searchDat.nazwisko)
		{
			free(searchDat.nazwisko);
			searchDat.nazwisko = NULL;
		}
	}
	else if (choice == 1)
	{
		printf("Enter Year\n");
		while (scanf_s("%d", &searchDat.rok) <= 0)
		{
			while ((getchar()) != '\n');
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			printf("Enter Year:\n");
		}
		while ((getchar()) != '\n');
		void *pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchYear, 1);
		if (pDat)
		{
			printf("Found: \n");
			MY_STUDENT_Print(pDat);
			i++;

		}

		while (pDat)
		{
			pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchYear, 0);
			if (pDat)
			{
				printf("Found: \n");
				MY_STUDENT_Print(pDat);
				i++;
			}
		}
	}

	else if (choice == 2)
	{
		printf("Enter course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n\n");
		do
		{
			while (scanf_s("%d", &searchDat.kierunek) <= 0)
			{
				while ((getchar()) != '\n');
				my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
				printf("Enter Course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n");
			}
			while ((getchar()) != '\n');
		
			if (searchDat.kierunek < 0 || searchDat.kierunek > 2)
			{
				my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
				printf("Enter Course: [0]INFORMATYKA  [1]MATEMATYKA  [2]FIZYKA\n");
			}

		} while (searchDat.kierunek < 0 || searchDat.kierunek > 2);
		void *pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchCourse, 1);
		if (pDat)
		{
			printf("Found: \n");
			MY_STUDENT_Print(pDat);
			i++;

		}

		while (pDat)
		{
			pDat = MY_STACK_Search(&searchDat, MY_STUDENT_SearchCourse, 0);
			if (pDat)
			{
				printf("Found: \n");
				MY_STUDENT_Print(pDat);
				i++;
			}
		}
	}
	if (i == 0)
		printf("Student doesn't found\n");
}

void clear()
{
	MY_STACK_Free();
	printf("Stack is empty\n\n");
	
}

void save()
{
	//SF Bardziej naturalnie bylo by przeniesc obsluge zapisu-odczytu stosu do stosu, a nie miescic to w interfejsie.
	//Przy zmianie typu danych obsluga zapisu-odczytu pozostaje bez zmian, a dopasowywanie interfejsu do nowych danych jest
	//bardziej proste.
	MY_STACK_Save();

}

void read()
{
	//SF przy podwojnym wywolaniu read() mam dwie kopie danych w jednym stosie.
	MY_STACK_Free();
	MY_STACK_Read();

}
