#include "stdafx.h"
#include "my_stack.h"
#include "my_messages.h"
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable : 4996)


static MY_STACK *first = NULL;
FreeData ptr_free_dat;
SaveData ptr_save_dat;
ReadData ptr_read_dat;

void MY_STACK_Init(FreeData pFreeDat, SaveData pSaveDat, ReadData pReadDat)
{
	first = NULL;
	ptr_free_dat = pFreeDat;
	ptr_save_dat = pSaveDat;
	ptr_read_dat = pReadDat;

}

void MY_STACK_Free()
{
	MY_STACK *p = first, *ptmp = NULL;
	while (p)
	{
		(ptr_free_dat)(p->pData);
		ptmp = p;
		p = p->next;
		free(ptmp);
	}
	first = NULL;
}

MY_STACK *MY_STACK_Push(void *pdat)
{
	MY_STACK *current = (MY_STACK *)malloc(sizeof(MY_STACK));
	if (!current)
	{
		//SF tu jest blad
		////SF tu jest blad!!!
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_error(NULL, NULL, NULL, NULL);
			
	}
	current->pData = pdat;
	
	if (!first)
		current->next = NULL;
	else
		current->next = first;
	first = current;

	return first;
}

MY_STACK MY_STACK_Pop()
{
	MY_STACK rv;
	if (!first)
	{
		rv.pData = NULL;
		rv.next = NULL;
		printf("\nStack is empty\n\n");
	}
	else
	{
		MY_STACK *tmp = first;
		rv.pData = first->pData;
		rv.next = NULL;
		first = tmp->next;
		free(tmp);
	}
	return rv;
}

void *MY_STACK_Search(void *pSearchDat, CompData ptr_comp_fun, int FirstEntry)
{
	static MY_STACK *p;
	MY_STACK *ptmp = NULL;
	if (FirstEntry)
		p = first;
	while (p)
	{
		if (!(*ptr_comp_fun)(p->pData, pSearchDat))
			p = p->next;
		else
		{
			ptmp = p;
			p = p->next;
			return ptmp->pData;
		}
	}
	return NULL;
}

int MY_STACK_Count() 
{
	MY_STACK *p = first;
	unsigned int i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return i;
}

void *MY_STACK_Get_one(int i)
{
	MY_STACK *p = first;
	
	for(int j = 0; j < i; j++)
	{
		p = p->next;
	}
	if (p != NULL)
		return p->pData;
	else
		return NULL;

}


void MY_STACK_Save()
{
	FILE * pf = fopen("dane.bin", "wb");
	size_t it = 0;
	if (!pf)
	{
		my_mess_fun(MY_MESS_FILE_NOT_OPENED_WARN);
	}
	else
	{
		void *tmp;
		unsigned int no_elements = MY_STACK_Count();
		__int64 file_positon = 0;
		__int64 *file_desc = (__int64 *)malloc((no_elements + 1) * sizeof(__int64));
		if (!file_desc)
		{
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(NULL, NULL, file_desc, pf);

		}

		if (fwrite(&no_elements, sizeof(unsigned int), 1, pf) != 1)
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_error(NULL, NULL, file_desc, pf);

		_fseeki64(pf, (no_elements + 1) * sizeof(__int64), SEEK_CUR);
		tmp = MY_STACK_Get_one(0);
		for (it = 1; it <= no_elements && tmp != NULL; it++)
		{
			file_desc[it - 1] = ftell(pf);
			(ptr_save_dat)(tmp, pf);
			tmp = MY_STACK_Get_one(it);
		}
		file_desc[no_elements] = ftell(pf);

		_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
		if (fwrite(file_desc, sizeof(__int64), no_elements + 1, pf) != (no_elements + 1))
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_error(NULL, NULL, file_desc, pf);
		if (file_desc)
			free(file_desc);
		file_desc = NULL;
	}
	if (pf)
		fclose(pf);
	pf = NULL;
	printf("\nWrite %d elements of stack to file \"dane.bin\"\n\n", it - 1);

}

void MY_STACK_Read()
{

	FILE *pf = fopen("dane.bin", "rb");
	int it = 0;
	if (!pf)
	{
		my_mess_fun(MY_MESS_FILE_NOT_CREATED_ERROR);
	}
	else
	{
		void *tmp = NULL;
		__int64 *file_desc = NULL;
		unsigned int no_elements = 0;
		fread(&no_elements, sizeof(unsigned int), 1, pf);
		file_desc = (__int64 *)malloc((no_elements + 1) * sizeof(__int64));
		if (!file_desc)
		{
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_error(NULL, NULL, file_desc, pf);
		}
		if (fread(file_desc, sizeof(file_desc[0]), no_elements + 1, pf) != (no_elements + 1))
			if (my_mess_fun(MY_MESS_READ_FROM_FILE) == MY_DECISION_BREAK)
				my_mess_error(NULL, NULL, file_desc, pf);

		for (it = 0; it < no_elements; it++)
		{
			
			unsigned int no_item = no_elements - it - 1;
			_fseeki64(pf, file_desc[no_item], SEEK_SET);
			tmp = (ptr_read_dat)(tmp, pf, file_desc);
			tmp = MY_STACK_Push(tmp);
			
		}
		if (file_desc)
			free(file_desc);
		file_desc = NULL;
	}
	if (pf)
		fclose(pf);
	pf = NULL;
	printf("\nRead %d elements of stack from file \"dane.bin\"\n\n", it);

}