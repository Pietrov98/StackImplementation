#include "stdafx.h"
#include "string.h"
#include "my_student.h"
#include "my_messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#pragma warning (disable : 4996)



void *MY_STUDENT_Init(char *lastname, int year, int course)
{
	MY_STUDENT *pdat = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!pdat)
	{
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(pdat, NULL, NULL, NULL);
	}
	else
	{
		pdat->nazwisko = (char *)malloc((strlen(lastname) + 1) * sizeof(char));
		if (!pdat->nazwisko)
		{
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(NULL, pdat->nazwisko, NULL, NULL);
		}
		strcpy(pdat->nazwisko, lastname);
		pdat->length_nazwisko = strlen(pdat->nazwisko) + 1;
		pdat->rok = year;

		switch (course)
		{
		case INFORMATYKA: pdat->kierunek = INFORMATYKA;
			break;
		case MATEMATYKA: pdat->kierunek = MATEMATYKA;
			break;
		case FIZYKA: pdat->kierunek = FIZYKA;
			break;
		default:
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			break;

		}
	
	}
	return (void *)(pdat);
}

void MY_STUDENT_Free(void *ptr)
{
	MY_STUDENT *pDat = (MY_STUDENT *)ptr;
	if (pDat)
	{
		free(pDat->nazwisko);
		pDat->nazwisko = NULL;
		free(pDat);
	}
}

void *MY_STUDENT_Push(char *lastname, int year, int course)
{
	return MY_STUDENT_Init(lastname, year, course);
}

void MY_STUDENT_Print(void *ptr)
{
	MY_STUDENT *p = (MY_STUDENT *)ptr;
	if (p)
	{
		printf("\nLastname: %s\n", p->nazwisko);
		printf("Year    : %d\n", p->rok);
		switch (p->kierunek)
		{
		case INFORMATYKA: printf("Course  : INFORMATYKA\n\n");
			break;
		case MATEMATYKA: printf("Course  : MATEMATYKA\n\n");
			break;
		case FIZYKA: printf("Course  : FIZYKA\n\n");
			break;
		default:
			my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
			break;
		}

	}
}

int MY_STUDENT_SearchLastName(void *pCurData, void *pSearchData)
{
	MY_STUDENT *pcur = (MY_STUDENT *)pCurData;
	MY_STUDENT *psearch = (MY_STUDENT *)pSearchData;
	////SF wprowadzilem trzy elementy do stosu z nazwiskami
	//aaa   bbb  aaa. Zapisalem na dysk. Zamykam aplikacje, otwieram ponownie, wczytuje dane z pliku.
	//Przy poszukiwaniu studenta z nazwiskiem aaa aplikacja zawisa na GP.
	if (strcmp(pcur->nazwisko, psearch->nazwisko) == 0)
		return 1;
	return 0;
}

int MY_STUDENT_SearchYear(void *pCurData, void *pSearchData)
{
	MY_STUDENT *pcur = (MY_STUDENT *)pCurData;
	MY_STUDENT *psearch = (MY_STUDENT *)pSearchData;
	if (pcur->rok == psearch->rok)
		return 1;
	return 0;
}

int MY_STUDENT_SearchCourse(void *pCurData, void *pSearchData) 
{
	MY_STUDENT *pcur = (MY_STUDENT *)pCurData;
	MY_STUDENT *psearch = (MY_STUDENT *)pSearchData;
	if (pcur->kierunek == psearch->kierunek)
		return 1;
	return 0;
}

void MY_STUDENT_Save(void *ptr, FILE *pf)
{
	if (pf)
	{
		MY_STUDENT *psave = (MY_STUDENT *)ptr;
		if(fwrite(psave, sizeof(MY_STUDENT), 1, pf) != 1)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(psave, NULL, NULL, pf);
		if(fwrite(psave->nazwisko, size_t(psave->length_nazwisko), 1, pf) != 1)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(psave, psave->nazwisko, NULL, pf);
	}
}

void *MY_STUDENT_Read(void *ptr, FILE *pf, _int64 *file_desc)
{
	MY_STUDENT *pread = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!pread)
	{
		//SF Tu jest blad
		////SF Tu jest blad!!!
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(pread, NULL, file_desc, pf);
	}
	if (fread(pread, sizeof(MY_STUDENT), 1, pf) < 1)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(pread, NULL, file_desc, pf);

	pread->nazwisko = (char*)malloc(pread->length_nazwisko * sizeof(char));

	if (!pread->nazwisko)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(pread, pread->nazwisko, file_desc, pf);

	if (fread(pread->nazwisko, pread->length_nazwisko, 1, pf) != 1)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(pread, NULL, file_desc, pf);

	return pread;
}

