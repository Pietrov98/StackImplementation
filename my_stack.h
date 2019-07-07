#ifndef MY_STACK__H
#define MY_STACK__H

struct MY_STACK
{
	void *pData;
	MY_STACK *next;
};

typedef void(*FreeData)(void *pdat);
typedef int (CompData)(void * pcurData, void *pSearchData);
typedef void(*SaveData)(void *pSavedat, FILE *pf);
typedef void* (*ReadData)(void *pReaddat, FILE *pf, _int64 *file_desc);


void MY_STACK_Init(FreeData pFreeDat, SaveData pSaveDat, ReadData Readdat);
void MY_STACK_Free();
MY_STACK *MY_STACK_Push(void *pdat);
MY_STACK MY_STACK_Pop();
void *MY_STACK_Search(void *pSearchDat, CompData ptr_comp_fun, int FirstEntry);
int MY_STACK_Count();
//SF  brak implementacji tej funkcji
//AP usun¹³em t¹ funkcjê
void *MY_STACK_Get_one(int i);
void MY_STACK_Save();
void MY_STACK_Read();
#endif